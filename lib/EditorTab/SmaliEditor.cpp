//===- SmaliEditor.cpp - ART-GUI Editor Tab ----------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
#include "SmaliEditor.h"

#include <utils/Configuration.h>
#include "SmaliLexer.h"

#include <sstream>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>

using namespace Analysis;

QMap<int, QString> SmaliEditor::mHintMap;

SmaliEditor::SmaliEditor (QWidget *parent):Editor (parent)
{
    mHintEdit = new QPlainTextEdit(this);
//    mHintEdit->setReadOnly (true);

    connect(mFileEdit, SIGNAL(cursorPositionChanged()),
            this, SLOT(editCursorChanged()));

    setHintMap();
    loadFromConfig();
}

SmaliEditor::~SmaliEditor ()
{
    saveToConfig();
}

void SmaliEditor::setTextLayout ()
{
    QLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins (0,0,0,0);
    mVSplitter = new QSplitter(Qt::Orientation::Vertical, this);
    mFileEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Ignored);
    mHintEdit->setSizePolicy (QSizePolicy::Preferred,QSizePolicy::Ignored);
    mVSplitter->addWidget (mFileEdit);
    mVSplitter->addWidget (mHintEdit);
    layout->addWidget (mVSplitter);
    layout->addWidget (mFindWidget);
    setLayout (layout);

    mVSplitter->setSizes (mVSplitterSize);
}

void SmaliEditor::loadFromConfig ()
{
    Editor::loadFromConfig ();
    Configuration *config = Config();

    mVSplitterSize << config->getUint ("SmaliEditor", "TopSplitterHeight")
              << config->getUint ("SmaliEditor", "BotSplitterHeight");
}

void SmaliEditor::saveToConfig ()
{
    Editor::saveToConfig ();
    Configuration *config = Config();

    mVSplitterSize = mVSplitter->sizes ();
    config->setUint ("SmaliEditor", "TopSplitterHeight", mVSplitterSize[0]);
    config->setUint ("SmaliEditor", "BotSplitterHeight", mVSplitterSize[1]);

}

void SmaliEditor::editCursorChanged ()
{
    QTextBlock tb = mFileEdit->textCursor ().block ();
    std::string blockText = tb.text ().toStdString ();
    std::istringstream is(blockText);
    SmaliLexer lexer;
    lexer.switch_streams (&is,nullptr);
    auto token = lexer.get_next_token ();
    auto type = token.token ();
    auto it = mHintMap.find (type);
    if(it != mHintMap.end ()) {
        mHintEdit->setPlainText (it.value ());
    } else {
        mHintEdit->setPlainText ("");
    }
}

void SmaliEditor::setHintMap ()
{
    static bool init = false;
    if(init)
        return;
    init = true;
    mHintMap[SmaliParser::token::TOKEN_CLASS_DIRECTIVE] = tr(".class flag className : Define a class.");
    mHintMap[SmaliParser::token::TOKEN_SUPER_DIRECTIVE] = tr(".super className : Define super class.");
    mHintMap[SmaliParser::token::TOKEN_SOURCE_DIRECTIVE] = tr (".source \"source name\" : Define source file name");
    mHintMap[SmaliParser::token::TOKEN_FIELD_DIRECTIVE] = tr (".field flag fieldName:fieldType : Define a field.");
    mHintMap[SmaliParser::token::TOKEN_METHOD_DIRECTIVE] = tr (".method flag methodName(argtype)returntype : Define a method.");
    mHintMap[SmaliParser::token::TOKEN_END_METHOD_DIRECTIVE] = tr (".end method : Method define end");


//    mHintMap[SmaliParser::token::TOKEN_OP_BEGIN] = "op - begin";
    mHintMap[SmaliParser::token::TOKEN_OP_NOP] = tr ("nop : No operation");
    mHintMap[SmaliParser::token::TOKEN_OP_MOVE] = tr ("move vx,vy : Moves the content of vy into vx. Both registers must be in the first 256 register range.");
    mHintMap[SmaliParser::token::TOKEN_OP_MOVE_FROM16] = tr ("move/from16 vx,vy : Moves the content of vy into vx. vy may be in the 64k register range while vx is one of the first 256 registers.");
    mHintMap[SmaliParser::token::TOKEN_OP_MOVE_16] = tr ("move/16");
    mHintMap[SmaliParser::token::TOKEN_OP_MOVE_WIDE] = tr ("move-wide");
    mHintMap[SmaliParser::token::TOKEN_OP_MOVE_WIDE_FROM16] = tr ("move-wide/from16 vx,vy : Moves a long/double value from vy to vx. vy may be in the 64k register range while wx is one of the first 256 registers.");
    mHintMap[SmaliParser::token::TOKEN_OP_MOVE_WIDE_16] = tr ("move-wide/16");
    mHintMap[SmaliParser::token::TOKEN_OP_MOVE_OBJECT] = tr ("move-object vx,vy : Moves the object reference from vy to vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_MOVE_OBJECT_FROM16] = tr ("move-object/from16 vx,vy : Moves the object reference from vy to vx, vy can address 64k registers and vx can address 256 registers.");
    mHintMap[SmaliParser::token::TOKEN_OP_MOVE_OBJECT_16] = tr ("move-object/16");
    mHintMap[SmaliParser::token::TOKEN_OP_MOVE_RESULT] = tr ("move-result vx : Move the result value of the previous method invocation into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_MOVE_RESULT_WIDE] = tr ("move-result-wide vx : Move the long/double result value of the previous method invocation into vx,vx+1.");
    mHintMap[SmaliParser::token::TOKEN_OP_MOVE_RESULT_OBJECT] = tr ("move-result-object vx : Move the result object reference of the previous method invocation into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_MOVE_EXCEPTION] = tr ("move-exception vx : Move the exception object reference thrown during a method invocation into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_RETURN_VOID] = tr ("return-void : Return without a return value");
    mHintMap[SmaliParser::token::TOKEN_OP_RETURN] = tr ("return vx : Return with vx return value");
    mHintMap[SmaliParser::token::TOKEN_OP_RETURN_WIDE] = tr ("return-wide vx : Return with double/long result in vx,vx+1.");
    mHintMap[SmaliParser::token::TOKEN_OP_RETURN_OBJECT] = tr ("return-object vx : Return with vx object reference value.");
    mHintMap[SmaliParser::token::TOKEN_OP_CONST_4] = tr ("const/4 vx,lit4 : Puts the 4 bit constant into vx");
    mHintMap[SmaliParser::token::TOKEN_OP_CONST_16] = tr ("const/16 vx,lit16 : Puts the 16 bit constant into vx");
    mHintMap[SmaliParser::token::TOKEN_OP_CONST] = tr ("const vx, lit32 : Puts the integer constant into vx");
    mHintMap[SmaliParser::token::TOKEN_OP_CONST_HIGH16] = tr ("const/high16 v0, lit16 : Puts the 16 bit constant into the topmost bits of the register. Used to initialize float values.");
    mHintMap[SmaliParser::token::TOKEN_OP_CONST_WIDE_16] = tr ("const-wide/16 vx, lit16 : Puts the integer constant into vx and vx+1 registers, expanding the integer constant into a long constant..");
    mHintMap[SmaliParser::token::TOKEN_OP_CONST_WIDE_32] = tr ("const-wide/32 vx, lit32 : Puts the 32 bit constant into vx and vx+1 registers, expanding the integer constant into a long constant.");
    mHintMap[SmaliParser::token::TOKEN_OP_CONST_WIDE] = tr ("const-wide vx, lit64 : Puts the 64 bit constant into vx and vx+1 registers.");
    mHintMap[SmaliParser::token::TOKEN_OP_CONST_WIDE_HIGH16] = tr ("const-wide/high16 vx,lit16 : Puts the 16 bit constant into the highest 16 bit of vx and vx+1 registers. Used to initialize double values.");
    mHintMap[SmaliParser::token::TOKEN_OP_CONST_STRING] = tr ("const-string vx,string_id : Puts reference to a string constant identified by string_id into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_CONST_STRING_JUMBO] = tr ("const-string-jumbo");
    mHintMap[SmaliParser::token::TOKEN_OP_CONST_CLASS] = tr ("const-class vx,type_id : Moves the class object of a class identified by type_id (e.g. Object.class) into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_MONITOR_ENTER] = tr ("monitor-enter vx : Obtains the monitor of the object referenced by vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_MONITOR_EXIT] = tr ("monitor-exit : Releases the monitor of the object referenced by vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_CHECK_CAST] = tr ("check-cast vx, type_id : Checks whether the object reference in vx can be cast to an instance of a class referenced by type_id. Throws ClassCastException if the cast is not possible, continues execution otherwise.");
    mHintMap[SmaliParser::token::TOKEN_OP_INSTANCE_OF] = tr ("instance-of vx,vy,type_id : Checks whether vy is instance of a class identified by type_id. Sets vx non-zero if it is, 0 otherwise.");
    mHintMap[SmaliParser::token::TOKEN_OP_ARRAY_LENGTH] = tr ("array-length vx,vy : Calculates the number of elements of the array referenced by vy and puts the length value into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_NEW_INSTANCE] = tr ("new-instance vx,type : Instantiates an object type and puts the reference of the newly created instance into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_NEW_ARRAY] = tr ("new-array vx,vy,type_id : Generates a new array of type_id type and vy element size and puts the reference to the array into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_FILLED_NEW_ARRAY] = tr ("filled-new-array {parameters},type_id : Generates a new array of type_id and fills it with the parameters5. Reference to the newly generated array can be obtained by a move-result-object instruction, immediately following the filled-new-array instruction.");
    mHintMap[SmaliParser::token::TOKEN_OP_FILLED_NEW_ARRAY_RANGE] = tr ("filled-new-array-range {vx..vy},type_id : Generates a new array of type_id and fills it with a range of parameters. Reference to the newly generated array can be obtained by a move-result-object instruction, immediately following the filled-new-array instruction.");
    mHintMap[SmaliParser::token::TOKEN_OP_FILL_ARRAY_DATA] = tr ("fill-array-data vx,array_data_offset : Fills the array referenced by vx with the static data. The location of the static data is the sum of  the position of the current instruction and the offset");
    mHintMap[SmaliParser::token::TOKEN_OP_THROW] = tr ("throw vx : Throws an exception object. The reference of the exception object is in vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_GOTO] = tr ("goto target : Unconditional jump by short offset.");
    mHintMap[SmaliParser::token::TOKEN_OP_GOTO_16] = tr ("goto/16 target : Unconditional jump by 16 bit offset.");
    mHintMap[SmaliParser::token::TOKEN_OP_GOTO_32] = tr ("goto/32 target");
    mHintMap[SmaliParser::token::TOKEN_OP_PACKED_SWITCH] = tr ("packed-switch vx,table : Implements a switch statement where the case constants are close to each other. The instruction uses an index table. vx indexes into this table to find the offset of the instruction for a particular case. If vx falls out of the index table, the execution continues on the next instruction (default case).");
    mHintMap[SmaliParser::token::TOKEN_OP_SPARSE_SWITCH] = tr ("sparse-switch vx,table : Implements a switch statement with sparse case table. The instruction uses a lookup table with case constants and offsets for each case constant. If there is no match in the table, execution continues on the next instruction (default case).");
    mHintMap[SmaliParser::token::TOKEN_OP_CMPL_FLOAT] = tr ("cmpl-float : Compares the float values in vy and vz and sets the integer value in vx accordingly3");
    mHintMap[SmaliParser::token::TOKEN_OP_CMPG_FLOAT] = tr ("cmpg-float vx, vy, vz : Compares the float values in vy and vz and sets the integer value in vx accordingly3.");
    mHintMap[SmaliParser::token::TOKEN_OP_CMPL_DOUBLE] = tr ("cmpl-double vx,vy,vz : Compares the double values in vy and vz2 and sets the integer value in vx accordingly3.");
    mHintMap[SmaliParser::token::TOKEN_OP_CMPG_DOUBLE] = tr ("cmpg-double vx, vy, vz : Compares the double values in vy and vz2 and sets the integer value in vx accordingly3.");
    mHintMap[SmaliParser::token::TOKEN_OP_CMP_LONG] = tr ("cmp-long vx, vy, vz : Compares the long values in vy and vz and sets the integer value in vx accordingly3.");
    mHintMap[SmaliParser::token::TOKEN_OP_IF_EQ] = tr ("if-eq vx,vy,target : Jumps to target if vx==vy2. vx and vy are integer values.");
    mHintMap[SmaliParser::token::TOKEN_OP_IF_NE] = tr ("if-ne vx,vy,target : Jumps to target if vx!=vy2. vx and vy are integer values.");
    mHintMap[SmaliParser::token::TOKEN_OP_IF_LT] = tr ("if-lt vx,vy,target : Jumps to target is vx<vy2. vx and vy are integer values.");
    mHintMap[SmaliParser::token::TOKEN_OP_IF_GE] = tr ("if-ge vx, vy,target : Jumps to target if vx>=vy2. vx and vy are integer values.");
    mHintMap[SmaliParser::token::TOKEN_OP_IF_GT] = tr ("if-gt vx,vy,target : Jumps to target if vx>vy2. vx and vy are integer values.");
    mHintMap[SmaliParser::token::TOKEN_OP_IF_LE] = tr ("if-le vx,vy,target : Jumps to target if vx<=vy2. vx and vy are integer values.");
    mHintMap[SmaliParser::token::TOKEN_OP_IF_EQZ] = tr ("if-eqz vx,target : Jumps to target if vx==02. vx is an integer value.");
    mHintMap[SmaliParser::token::TOKEN_OP_IF_NEZ] = tr ("if-nez vx,target : Checks vx and jumps if vx is nonzero2.");
    mHintMap[SmaliParser::token::TOKEN_OP_IF_LTZ] = tr ("if-ltz vx,target : Checks vx and jumps if vx<02.");
    mHintMap[SmaliParser::token::TOKEN_OP_IF_GEZ] = tr ("if-gez vx,target : Checks vx and jumps if vx>=02.");
    mHintMap[SmaliParser::token::TOKEN_OP_IF_GTZ] = tr ("if-gtz vx,target : Checks vx and jumps if vx>02.");
    mHintMap[SmaliParser::token::TOKEN_OP_IF_LEZ] = tr ("if-lez vx,target : Checks vx and jumps if vx<=02.");
    mHintMap[SmaliParser::token::TOKEN_OP_UNUSED_3E] = tr ("unused_3E");
    mHintMap[SmaliParser::token::TOKEN_OP_UNUSED_3F] = tr ("unused_3F");
    mHintMap[SmaliParser::token::TOKEN_OP_UNUSED_40] = tr ("unused_40");
    mHintMap[SmaliParser::token::TOKEN_OP_UNUSED_41] = tr ("unused_41");
    mHintMap[SmaliParser::token::TOKEN_OP_UNUSED_42] = tr ("unused_42");
    mHintMap[SmaliParser::token::TOKEN_OP_UNUSED_43] = tr ("unused_43");
    mHintMap[SmaliParser::token::TOKEN_OP_AGET] = tr ("aget vx,vy,vz : Gets an integer value of an object reference array into vx. The array is referenced by vy and is indexed by vz.");
    mHintMap[SmaliParser::token::TOKEN_OP_AGET_WIDE] = tr ("aget-wide vx,vy,vz : Gets a long/double value of long/double array into vx,vx+1. The array is referenced by vy and is indexed by vz.");
    mHintMap[SmaliParser::token::TOKEN_OP_AGET_OBJECT] = tr ("aget-object vx,vy,vz : Gets an object reference value of an object reference array into vx. The array is referenced by vy and is indexed by vz.");
    mHintMap[SmaliParser::token::TOKEN_OP_AGET_BOOLEAN] = tr ("aget-boolean vx,vy,vz : Gets a boolean value of a boolean array into vx. The array is referenced by vy and is indexed by vz.");
    mHintMap[SmaliParser::token::TOKEN_OP_AGET_BYTE] = tr ("aget-byte vx,vy,vz : Gets a byte value of a byte array into vx. The array is referenced by vy and is indexed by vz.");
    mHintMap[SmaliParser::token::TOKEN_OP_AGET_CHAR] = tr ("aget-char vx, vy,vz : Gets a char value  of a character array into vx. The element is indexed by vz, the array object is referenced by vy");
    mHintMap[SmaliParser::token::TOKEN_OP_AGET_SHORT] = tr ("aget-short vx,vy,vz : Gets a short value  of a short array into vx. The element is indexed by vz, the array object is referenced by vy.");
    mHintMap[SmaliParser::token::TOKEN_OP_APUT] = tr ("aput vx,vy,vz : Puts the integer value in vx into an element of an integer array. The element is indexed by vz, the array object is referenced by vy.");
    mHintMap[SmaliParser::token::TOKEN_OP_APUT_WIDE] = tr ("aput-wide vx,vy,vz : Puts the double/long value in vx,vx+1 into a double/long array. The array is referenced by vy, the element is indexed by vz.");
    mHintMap[SmaliParser::token::TOKEN_OP_APUT_OBJECT] = tr ("aput-object vx,vy,vz : Puts the object reference value in vx into an element of an object reference array. The element is indexed by vz, the array object is referenced by vy.");
    mHintMap[SmaliParser::token::TOKEN_OP_APUT_BOOLEAN] = tr ("aput-boolean vx,vy,vz : Puts the boolean value in vx into an element of a boolean array. The element is indexed by vz, the array object is referenced by vy.");
    mHintMap[SmaliParser::token::TOKEN_OP_APUT_BYTE] = tr ("aput-byte vx,vy,vz : Puts the byte value in vx into an element of a byte array. The element is indexed by vz, the array object is referenced by vy.");
    mHintMap[SmaliParser::token::TOKEN_OP_APUT_CHAR] = tr ("aput-char vx,vy,vz : Puts the char value in vx into an element of a character array. The element is indexed by vz, the array object is referenced by vy.");
    mHintMap[SmaliParser::token::TOKEN_OP_APUT_SHORT] = tr ("aput-short vx,vy,vz : Puts the short value in vx into an element of a short array. The element is indexed by vz, the array object is referenced by vy.");
    mHintMap[SmaliParser::token::TOKEN_OP_IGET] = tr ("iget vx, vy, field_id : Reads an instance field into vx. The instance is referenced by vy.");
    mHintMap[SmaliParser::token::TOKEN_OP_IGET_WIDE] = tr ("iget-wide vx,vy,field_id : Reads an instance field into vx1. The instance is referenced by vy.");
    mHintMap[SmaliParser::token::TOKEN_OP_IGET_OBJECT] = tr ("iget-object vx,vy,field_id : Reads an object reference instance field into vx. The instance is referenced by vy.");
    mHintMap[SmaliParser::token::TOKEN_OP_IGET_BOOLEAN] = tr ("iget-boolean vx,vy,field_id : Reads a boolean instance field into vx. The instance is referenced by vy.");
    mHintMap[SmaliParser::token::TOKEN_OP_IGET_BYTE] = tr ("iget-byte vx,vy,field_id : Reads a byte instance field into vx. The instance is referenced by vy.");
    mHintMap[SmaliParser::token::TOKEN_OP_IGET_CHAR] = tr ("iget-char vx,vy,field_id : Reads a char instance field into vx. The instance is referenced by vy.");
    mHintMap[SmaliParser::token::TOKEN_OP_IGET_SHORT] = tr ("iget-short vx,vy,field_id : Reads a short instance field into vx. The instance is referenced by vy.");
    mHintMap[SmaliParser::token::TOKEN_OP_IPUT] = tr ("iput vx,vy, field_id : Puts vx into an instance field. The instance is referenced by vy.");
    mHintMap[SmaliParser::token::TOKEN_OP_IPUT_WIDE] = tr ("iput-wide vx,vy, field_id : Puts the wide value located in vx and vx+1 registers into an instance field. The instance is referenced by vy.");
    mHintMap[SmaliParser::token::TOKEN_OP_IPUT_OBJECT] = tr ("iput-object vx,vy,field_id : Puts the object reference in vx into an instance field. The instance is referenced by vy.");
    mHintMap[SmaliParser::token::TOKEN_OP_IPUT_BOOLEAN] = tr ("iput-boolean vx,vy, field_id : Puts the boolean value located in vx into an instance field. The instance is referenced by vy.");
    mHintMap[SmaliParser::token::TOKEN_OP_IPUT_BYTE] = tr ("iput-byte vx,vy,field_id : Puts the byte value located in vx into an instance field. The instance is referenced by vy.");
    mHintMap[SmaliParser::token::TOKEN_OP_IPUT_CHAR] = tr ("iput-char vx,vy,field_id : Puts the char value located in vx into an instance field. The instance is referenced by vy.");
    mHintMap[SmaliParser::token::TOKEN_OP_IPUT_SHORT] = tr ("iput-short vx,vy,field_id : Puts the short value located in vx into an instance field. The instance is referenced by vy.");
    mHintMap[SmaliParser::token::TOKEN_OP_SGET] = tr ("sget vx,field_id : Reads the integer field identified by the field_id into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_SGET_WIDE] = tr ("sget-wide vx, field_id : Reads the static field identified by the field_id into vx and vx+1 registers.");
    mHintMap[SmaliParser::token::TOKEN_OP_SGET_OBJECT] = tr ("sget-object vx,field_id : Reads the object reference field identified by the field_id into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_SGET_BOOLEAN] = tr ("sget-boolean vx,field_id : Reads the boolean static field identified by the field_id into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_SGET_BYTE] = tr ("sget-byte vx,field_id : Reads the byte static field identified by the field_id into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_SGET_CHAR] = tr ("sget-char vx,field_id : Reads the char static field identified by the field_id into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_SGET_SHORT] = tr ("sget-short vx,field_id : Reads the short static field identified by the field_id into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_SPUT] = tr ("sput vx, field_id : Puts vx into a static field.");
    mHintMap[SmaliParser::token::TOKEN_OP_SPUT_WIDE] = tr ("sput-wide vx, field_id : Puts vx and vx+1 into a static field.");
    mHintMap[SmaliParser::token::TOKEN_OP_SPUT_OBJECT] = tr ("sput-object vx,field_id : Puts object reference in vx into a static field.");
    mHintMap[SmaliParser::token::TOKEN_OP_SPUT_BOOLEAN] = tr ("sput-boolean vx,field_id : Puts boolean value in vx into a static field.");
    mHintMap[SmaliParser::token::TOKEN_OP_SPUT_BYTE] = tr ("sput-byte vx,field_id : Puts byte value in vx into a static field.");
    mHintMap[SmaliParser::token::TOKEN_OP_SPUT_CHAR] = tr ("sput-char vx,field_id : Puts char value in vx into a static field.");
    mHintMap[SmaliParser::token::TOKEN_OP_SPUT_SHORT] = tr ("sput-short vx,field_id : Puts short value in vx into a static field.");
    mHintMap[SmaliParser::token::TOKEN_OP_INVOKE_VIRTUAL] = tr ("invoke-virtual { parameters }, methodtocall : Invokes a virtual method with parameters.");
    mHintMap[SmaliParser::token::TOKEN_OP_INVOKE_SUPER] = tr ("invoke-super {parameter},methodtocall : Invokes the virtual method of the immediate parent class.");
    mHintMap[SmaliParser::token::TOKEN_OP_INVOKE_DIRECT] = tr ("invoke-direct { parameters }, methodtocall : Invokes a method with parameters without the virtual method resolution.");
    mHintMap[SmaliParser::token::TOKEN_OP_INVOKE_STATIC] = tr ("invoke-static {parameters}, methodtocall : Invokes a static method with parameters.");
    mHintMap[SmaliParser::token::TOKEN_OP_INVOKE_INTERFACE] = tr ("invoke-interface {parameters},methodtocall : Invokes an interface method.");
    mHintMap[SmaliParser::token::TOKEN_OP_UNUSED_73] = tr ("unused_73");
    mHintMap[SmaliParser::token::TOKEN_OP_INVOKE_VIRTUAL_RANGE] = tr ("invoke-virtual/range {vx..vy},methodtocall : Invokes virtual method with a range of registers. The instruction specifies the first register and the number of registers to be passed to the method.");
    mHintMap[SmaliParser::token::TOKEN_OP_INVOKE_SUPER_RANGE] = tr ("invoke-super/range : Invokes  the virtual method of the immediate parent class. The instruction specifies the first register and the number of registers to be passed to the method.");
    mHintMap[SmaliParser::token::TOKEN_OP_INVOKE_DIRECT_RANGE] = tr ("invoke-direct/range {vx..vy},methodtocall : Invokes direct method with a range of registers. The instruction specifies the first register and the number of registers to be passed to the method.");
    mHintMap[SmaliParser::token::TOKEN_OP_INVOKE_STATIC_RANGE] = tr ("invoke-static/range {vx..vy},methodtocall : Invokes static method with a range of registers. The instruction specifies the first register and the number of registers to be passed to the method.");
    mHintMap[SmaliParser::token::TOKEN_OP_INVOKE_INTERFACE_RANGE] = tr ("invoke-interface-range : Invokes an interface method with a range of registers. The instruction specifies the first register and the number of registers to be passed to the method.");
    mHintMap[SmaliParser::token::TOKEN_OP_UNUSED_79] = tr ("unused_79");
    mHintMap[SmaliParser::token::TOKEN_OP_UNUSED_7A] = tr ("unused_7A");
    mHintMap[SmaliParser::token::TOKEN_OP_NEG_INT] = tr ("neg-int vx,vy : Calculates vx=-vy.");
    mHintMap[SmaliParser::token::TOKEN_OP_NOT_INT] = tr ("not-int vx,vy");
    mHintMap[SmaliParser::token::TOKEN_OP_NEG_LONG] = tr ("neg-long vx,vy : Calculates vx,vx+1=-(vy,vy+1)");
    mHintMap[SmaliParser::token::TOKEN_OP_NOT_LONG] = tr ("not-long vx,vy");
    mHintMap[SmaliParser::token::TOKEN_OP_NEG_FLOAT] = tr ("neg-float vx,vy : Calculates vx=-vy");
    mHintMap[SmaliParser::token::TOKEN_OP_NEG_DOUBLE] = tr ("neg-double vx,vy : Calculates vx,vx+1=-(vy,vy+1)");
    mHintMap[SmaliParser::token::TOKEN_OP_INT_TO_LONG] = tr ("int-to-long vx, vy : Converts the integer in vy into a long in vx,vx+1.");
    mHintMap[SmaliParser::token::TOKEN_OP_INT_TO_FLOAT] = tr ("int-to-float vx, vy : Converts the integer in vx into a float in vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_INT_TO_DOUBLE] = tr ("int-to-double vx, vy : Converts the integer in vy into the double in vx,vx+1.");
    mHintMap[SmaliParser::token::TOKEN_OP_LONG_TO_INT] = tr ("long-to-int vx,vy : Converts the long value in vy,vy+1 into an integer in vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_LONG_TO_FLOAT] = tr ("long-to-float vx, vy : Converts the long value in vy,vy+1 into a float in vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_LONG_TO_DOUBLE] = tr ("long-to-double vx, vy : Converts the long value in vy,vy+1 into a double value in vx,vx+1.");
    mHintMap[SmaliParser::token::TOKEN_OP_FLOAT_TO_INT] = tr ("float-to-int vx, vy : Converts the float value in vy into an integer value in vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_FLOAT_TO_LONG] = tr ("float-to-long vx,vy : Converts the float value in vy into a long value in vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_FLOAT_TO_DOUBLE] = tr ("float-to-double vx, vy : Converts the float value in vy into a double value in vx,vx+1.");
    mHintMap[SmaliParser::token::TOKEN_OP_DOUBLE_TO_INT] = tr ("double-to-int vx, vy : Converts the double value in vy,vy+1 into an integer value in vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_DOUBLE_TO_LONG] = tr ("double-to-long vx, vy : Converts the double value in vy,vy+1 into a long value in vx,vx+1.");
    mHintMap[SmaliParser::token::TOKEN_OP_DOUBLE_TO_FLOAT] = tr ("double-to-float vx, vy : Converts the double value in vy,vy+1 into a float value in vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_INT_TO_BYTE] = tr ("int-to-byte vx,vy : Converts the int value in vy to a byte value and stores it in vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_INT_TO_CHAR] = tr ("int-to-char vx,vy : Converts the int value in vy to a char value and stores it in vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_INT_TO_SHORT] = tr ("int-to-short vx,vy : Converts the int value in vy to a short value and stores it in vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_ADD_INT] = tr ("add-int vx,vy,vz : Calculates vy+vz and puts the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_SUB_INT] = tr ("sub-int vx,vy,vz : Calculates vy-vz and puts the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_MUL_INT] = tr ("mul-int vx, vy, vz : Multiplies vz with wy and puts the result int vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_DIV_INT] = tr ("div-int vx,vy,vz : Divides vy with vz and puts the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_REM_INT] = tr ("rem-int vx,vy,vz : Calculates vy % vz and puts the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_AND_INT] = tr ("and-int vx, vy, vz : Calculates vy AND vz and puts the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_OR_INT] = tr ("or-int vx, vy, vz : Calculates vy OR vz and puts the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_XOR_INT] = tr ("xor-int vx, vy, vz : Calculates vy XOR vz and puts the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_SHL_INT] = tr ("shl-int vx, vy, vz : Shift vy left by the positions specified by vz and store the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_SHR_INT] = tr ("shr-int vx, vy, vz : Shift vy right by the positions specified by vz and store the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_USHR_INT] = tr ("ushr-int vx, vy, vz : Unsigned shift right (>>>) vy by the positions specified by vz and store the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_ADD_LONG] = tr ("add-long vx, vy, vz : Adds vy to vz and puts the result into vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_SUB_LONG] = tr ("sub-long vx,vy,vz : Calculates vy-vz and puts the result into vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_MUL_LONG] = tr ("mul-long vx,vy,vz : Calculates vy*vz and puts the result into vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_DIV_LONG] = tr ("div-long vx, vy, vz : Calculates vy/vz and puts the result into vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_REM_LONG] = tr ("rem-long vx,vy,vz : Calculates vy % vz and puts the result into vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_AND_LONG] = tr ("and-long vx, vy, vz : Calculates the vy AND vz and puts the result into vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_OR_LONG] = tr ("or-long vx, vy, vz : Calculates the vy OR vz and puts the result into vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_XOR_LONG] = tr ("xor-long vx, vy, vz : Calculates the vy XOR vz and puts the result into vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_SHL_LONG] = tr ("shl-long vx, vy, vz : Shifts left vy by vz positions and stores the result in vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_SHR_LONG] = tr ("shr-long vx,vy,vz : Shifts right vy by vz positions and stores the result in vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_USHR_LONG] = tr ("ushr-long vx, vy, vz : Unsigned shifts right vy by vz positions and stores the result in vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_ADD_FLOAT] = tr ("add-float vx,vy,vz : Adds vy to vz and puts the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_SUB_FLOAT] = tr ("sub-float vx,vy,vz : Calculates vy-vz and puts the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_MUL_FLOAT] = tr ("mul-float vx, vy, vz : Multiplies vy with vz and puts the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_DIV_FLOAT] = tr ("div-float vx, vy, vz : Calculates vy/vz and puts the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_REM_FLOAT] = tr ("rem-float vx,vy,vz : Calculates vy % vz and puts the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_ADD_DOUBLE] = tr ("add-double vx,vy,vz : Adds vy to vz and puts the result into vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_SUB_DOUBLE] = tr ("sub-double vx,vy,vz : Calculates vy-vz and puts the result into vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_MUL_DOUBLE] = tr ("mul-double vx, vy, vz : Multiplies vy with vz and puts the result into vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_DIV_DOUBLE] = tr ("div-double vx, vy, vz : Calculates vy/vz and puts the result into vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_REM_DOUBLE] = tr ("rem-double vx,vy,vz : Calculates vy % vz and puts the result into vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_ADD_INT_2ADDR] = tr ("add-int/2addr vx,vy : Adds vy to vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_SUB_INT_2ADDR] = tr ("sub-int/2addr vx,vy : Calculates vx-vy and puts the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_MUL_INT_2ADDR] = tr ("mul-int/2addr vx,vy : Multiplies vx with vy.");
    mHintMap[SmaliParser::token::TOKEN_OP_DIV_INT_2ADDR] = tr ("div-int/2addr vx,vy : Divides vx with vy and puts the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_REM_INT_2ADDR] = tr ("rem-int/2addr vx,vy : Calculates vx % vy and puts the result into vx");
    mHintMap[SmaliParser::token::TOKEN_OP_AND_INT_2ADDR] = tr ("and-int/2addr vx, vy : Calculates vx AND vy and puts the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_OR_INT_2ADDR] = tr ("or-int/2addr vx, vy : Calculates vx OR vy and puts the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_XOR_INT_2ADDR] = tr ("xor-int/2addr vx, vy : Calculates vx XOR vy and puts the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_SHL_INT_2ADDR] = tr ("shl-int/2addr vx, vy : Shifts vx left by vy positions.");
    mHintMap[SmaliParser::token::TOKEN_OP_SHR_INT_2ADDR] = tr ("shr-int/2addr vx, vy : Shifts vx right by vy positions.");
    mHintMap[SmaliParser::token::TOKEN_OP_USHR_INT_2ADDR] = tr ("ushr-int/2addr vx, vy : Unsigned shift right (>>>) vx by the positions specified by vy.");
    mHintMap[SmaliParser::token::TOKEN_OP_ADD_LONG_2ADDR] = tr ("add-long/2addr vx,vy : Adds vy to vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_SUB_LONG_2ADDR] = tr ("sub-long/2addr vx,vy : Calculates vx-vy and puts the result into vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_MUL_LONG_2ADDR] = tr ("mul-long/2addr vx,vy : Calculates vx*vy and puts the result into vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_DIV_LONG_2ADDR] = tr ("div-long/2addr vx, vy : Calculates vx/vy and puts the result into vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_REM_LONG_2ADDR] = tr ("rem-long/2addr vx,vy : Calculates vx % vy and puts the result into vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_AND_LONG_2ADDR] = tr ("and-long/2addr vx, vy : Calculates vx AND vy and puts the result into vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_OR_LONG_2ADDR] = tr ("or-long/2addr vx, vy : Calculates vx OR vy and puts the result into vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_XOR_LONG_2ADDR] = tr ("xor-long/2addr vx, vy : Calculates vx XOR vy and puts the result into vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_SHL_LONG_2ADDR] = tr ("shl-long/2addr vx, vy : Shifts left the value in vx,vx+1 by the positions specified by vy and stores the result in vx,vx+1.");
    mHintMap[SmaliParser::token::TOKEN_OP_SHR_LONG_2ADDR] = tr ("shr-long/2addr vx, vy : Shifts right the value in vx,vx+1 by the positions specified by vy and stores the result in vx,vx+1.");
    mHintMap[SmaliParser::token::TOKEN_OP_USHR_LONG_2ADDR] = tr ("ushr-long/2addr vx, vy : Unsigned shifts right the value in vx,vx+1 by the positions specified by vy and stores the result in vx,vx+1.");
    mHintMap[SmaliParser::token::TOKEN_OP_ADD_FLOAT_2ADDR] = tr ("add-float/2addr vx,vy : Adds vy to vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_SUB_FLOAT_2ADDR] = tr ("sub-float/2addr vx,vy : Calculates vx-vy and stores the result in vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_MUL_FLOAT_2ADDR] = tr ("mul-float/2addr vx, vy : Multiplies vx with vy.");
    mHintMap[SmaliParser::token::TOKEN_OP_DIV_FLOAT_2ADDR] = tr ("div-float/2addr vx, vy : Calculates vx/vy and puts the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_REM_FLOAT_2ADDR] = tr ("rem-float/2addr vx,vy : Calculates vx/vy and puts the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_ADD_DOUBLE_2ADDR] = tr ("add-double/2addr vx, vy : Adds vy to vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_SUB_DOUBLE_2ADDR] = tr ("sub-double/2addr vx, vy : Calculates vx-vy and puts the result into vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_MUL_DOUBLE_2ADDR] = tr ("mul-double/2addr vx, vy : Multiplies vx with vy1.");
    mHintMap[SmaliParser::token::TOKEN_OP_DIV_DOUBLE_2ADDR] = tr ("div-double/2addr vx, vy : Calculates vx/vy and puts the result into vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_REM_DOUBLE_2ADDR] = tr ("rem-double/2addr vx,vy : Calculates vx % vy and puts the result into vx1.");
    mHintMap[SmaliParser::token::TOKEN_OP_ADD_INT_LIT16] = tr ("add-int/lit16 vx,vy,lit16 : Adds vy to lit16 and stores the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_RSUB_INT] = tr ("sub-int/lit16 vx,vy,lit16 : Calculates vy - lit16 and stores the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_MUL_INT_LIT16] = tr ("mul-int/lit16 vx,vy,lit16 : Calculates vy * lit16 and stores the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_DIV_INT_LIT16] = tr ("div-int/lit16 vx,vy,lit16 : Calculates vy / lit16 and stores the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_REM_INT_LIT16] = tr ("rem-int/lit16 vx,vy,lit16 : Calculates vy % lit16 and stores the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_AND_INT_LIT16] = tr ("and-int/lit16 vx,vy,lit16 : Calculates vy AND lit16 and stores the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_OR_INT_LIT16] = tr ("or-int/lit16 vx,vy,lit16 : Calculates vy OR lit16 and stores the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_XOR_INT_LIT16] = tr ("xor-int/lit16 vx,vy,lit16 : Calculates vy XOR lit16 and stores the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_ADD_INT_LIT8] = tr ("add-int/lit8 vx,vy,lit8 : Adds vy to lit8 and stores the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_RSUB_INT_LIT8] = tr ("sub-int/lit8 vx,vy,lit8 : Calculates vy-lit8 and stores the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_MUL_INT_LIT8] = tr ("mul-int/lit8 vx,vy,lit8 : Multiplies vy with lit8 8-bit literal constant and puts the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_DIV_INT_LIT8] = tr ("div-int/lit8 vx,vy,lit8 : Calculates vy/lit8 and stores the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_REM_INT_LIT8] = tr ("rem-int/lit8 vx,vy,lit8 : Calculates vy % lit8 and stores the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_AND_INT_LIT8] = tr ("and-int/lit8 vx,vy,lit8 : Calculates vy AND lit8 and stores the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_OR_INT_LIT8] = tr ("or-int/lit8 vx, vy, lit8 : Calculates vy OR lit8 and puts the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_XOR_INT_LIT8] = tr ("xor-int/lit8 vx, vy, lit8 : Calculates vy XOR lit8 and puts the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_SHL_INT_LIT8] = tr ("shl-int/lit8 vx, vy, lit8 : Shift v0 left by the bit positions specified by the literal constant and put the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_SHR_INT_LIT8] = tr ("shr-int/lit8 vx, vy, lit8 : Shift v0 right by the bit positions specified by the literal constant and put the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_USHR_INT_LIT8] = tr ("ushr-int/lit8 vx, vy, lit8 : Unsigned right shift of v0 (>>>) by the bit positions specified by the literal constant and put the result into vx.");
    mHintMap[SmaliParser::token::TOKEN_OP_IGET_VOLATILE] = tr ("iget-volatile");
    mHintMap[SmaliParser::token::TOKEN_OP_IPUT_VOLATILE] = tr ("iput-volatile");
    mHintMap[SmaliParser::token::TOKEN_OP_SGET_VOLATILE] = tr ("sget-volatile");
    mHintMap[SmaliParser::token::TOKEN_OP_SPUT_VOLATILE] = tr ("sput-volatile");
    mHintMap[SmaliParser::token::TOKEN_OP_IGET_OBJECT_VOLATILE] = tr ("iget-object-volatile");
    mHintMap[SmaliParser::token::TOKEN_OP_IGET_WIDE_VOLATILE] = tr ("iget-wide-volatile");
    mHintMap[SmaliParser::token::TOKEN_OP_IPUT_WIDE_VOLATILE] = tr ("iput-wide-volatile");
    mHintMap[SmaliParser::token::TOKEN_OP_SGET_WIDE_VOLATILE] = tr ("sget-wide-volatile");
    mHintMap[SmaliParser::token::TOKEN_OP_SPUT_WIDE_VOLATILE] = tr ("sput-wide-volatile");
    mHintMap[SmaliParser::token::TOKEN_OP_BREAKPOINT] = tr ("breakpoint");
    mHintMap[SmaliParser::token::TOKEN_OP_THROW_VERIFICATION_ERROR] = tr ("throw-verification-error");
    mHintMap[SmaliParser::token::TOKEN_OP_EXECUTE_INLINE] = tr ("execute-inline {parameters},inline ID : Executes the inline method identified by inline ID6.");
    mHintMap[SmaliParser::token::TOKEN_OP_EXECUTE_INLINE_RANGE] = tr ("execute-inline/range");
    mHintMap[SmaliParser::token::TOKEN_OP_INVOKE_OBJECT_INIT_RANGE] = tr ("invoke-object-init/range");
    mHintMap[SmaliParser::token::TOKEN_OP_RETURN_VOID_BARRIER] = tr ("return-void-barrier");
    mHintMap[SmaliParser::token::TOKEN_OP_IGET_QUICK] = tr ("iget-quick vx,vy,offset : Gets the value stored at offset in vy instance's data area to vx6.");
    mHintMap[SmaliParser::token::TOKEN_OP_IGET_WIDE_QUICK] = tr ("iget-wide-quick vx,vy,offset : Gets the object reference value stored at offset in vy instance's data area to vx,vx+16.");
    mHintMap[SmaliParser::token::TOKEN_OP_IGET_OBJECT_QUICK] = tr ("iget-object-quick vx,vy,offset : Gets the object reference value stored at offset in vy instance's data area to vx6.");
    mHintMap[SmaliParser::token::TOKEN_OP_IPUT_QUICK] = tr ("iput-quick vx,vy,offset : Puts the value stored in vx to offset in vy instance's data area6.");
    mHintMap[SmaliParser::token::TOKEN_OP_IPUT_WIDE_QUICK] = tr ("iput-wide-quick vx,vy,offset : Puts the value stored in vx,vx+1 to offset in vy instance's data area6.");
    mHintMap[SmaliParser::token::TOKEN_OP_IPUT_OBJECT_QUICK] = tr ("iput-object-quick vx,vy,offset : Puts the object reference value stored in vx to offset in vy instance's data area to vx6.");
    mHintMap[SmaliParser::token::TOKEN_OP_INVOKE_VIRTUAL_QUICK] = tr ("invoke-virtual-quick {parameters},vtable offset : Invokes a virtual method using the vtable of the target object6.");
    mHintMap[SmaliParser::token::TOKEN_OP_INVOKE_VIRTUAL_QUICK_RANGE] = tr ("invoke-virtual-quick/range {parameter range},vtable offset  : Invokes a virtual method using the vtable of the target object6");
    mHintMap[SmaliParser::token::TOKEN_OP_INVOKE_SUPER_QUICK] = tr ("invoke-super-quick {parameters},vtable offset : Invokes a virtual method in the target object's immediate parent class using the vtable of that parent class6.");
    mHintMap[SmaliParser::token::TOKEN_OP_INVOKE_SUPER_QUICK_RANGE] = tr ("invoke-super-quick/range {register range},vtable offset : Invokes a virtual method in the target object's immediate parent class using the vtable of that parent class6.");
    mHintMap[SmaliParser::token::TOKEN_OP_IPUT_OBJECT_VOLATILE] = tr ("iput-object-volatile");
    mHintMap[SmaliParser::token::TOKEN_OP_SGET_OBJECT_VOLATILE] = tr ("sget-object-volatile");
    mHintMap[SmaliParser::token::TOKEN_OP_SPUT_OBJECT_VOLATILE] = tr ("sput-object-volatile");
    mHintMap[SmaliParser::token::TOKEN_OP_UNUSED_FF] = tr ("unused-ff");
    mHintMap[SmaliParser::token::TOKEN_CATCH_DIRECTIVE] = tr (".catch type {fromLabel .. tolabel} :target : catch exception type between fromLabel and tolabel. If exception occureded, jump to target");
    mHintMap[SmaliParser::token::TOKEN_CATCHALL_DIRECTIVE] = tr (".catchll {fromLabel .. tolabel} :target : catch exception type between fromLabel and tolabel. If exception occureded, jump to target");

//    mHintMap[SmaliParser::token::TOKEN_OP_END] = "op - end";
}
