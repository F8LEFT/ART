//===- SmaliEditor.cpp - ART-GUI Editor Tab --------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//


#include "SmaliOpInformation.h"
#include "SmaliLexer.h"


#include <QTextBlock>

SmaliOpInformation::SmaliOpInformation(QPlainTextEdit *parent):
    QLineEdit(parent),
    m_edit(parent)
{
    Q_ASSERT(parent != Q_NULLPTR && "should not be null");
    connect(parent, &QPlainTextEdit::cursorPositionChanged, this, &SmaliOpInformation::cursorChanged);
}

void SmaliOpInformation::cursorChanged() {
    QTextBlock tb = m_edit->textCursor ().block ();
    std::string blockText = tb.text ().toStdString ();
    antlr4::ANTLRInputStream input(blockText);
    SmaliLexer lexer(&input);
    auto token = lexer.nextToken();
    if(token->getType() > SmaliLexer::TYPE_LIST_EOF)
        return;


    setText(getOpInformation(QString::fromStdString(token->getText())));
}

QString SmaliOpInformation::getOpInformation(QString token) {
    static QMap<QString, QString> mHintMap;
    if(mHintMap.isEmpty()) {
        mHintMap[".class"] = tr(".class flag className : Define a class.");
        mHintMap[".super"] = tr(".super className : Define super class.");
        mHintMap[".source"] = tr (".source \"source name\" : Define source file name");
        mHintMap[".field"] = tr (".field flag fieldName:fieldType : Define a field.");
        mHintMap[".method"] = tr (".method flag methodName(argtype)returntype : Define a method.");
        mHintMap[".end method"] = tr (".end method : Method define end");


//    mHintMap[SmaliParser::token::TOKEN_OP_BEGIN] = "op - begin";
        mHintMap["nop"] = tr ("nop : No operation");
        mHintMap["move"] = tr ("move vx,vy : Moves the content of vy into vx. Both registers must be in the first 256 register range.");
        mHintMap["move/from16"] = tr ("move/from16 vx,vy : Moves the content of vy into vx. vy may be in the 64k register range while vx is one of the first 256 registers.");
        mHintMap["move/16"] = tr ("move/16 vx,vy : Moves the content of vy into vx. vy may be in the 64k register range while vx is one of the first 256 registers.");
        mHintMap["move-wide"] = tr ("move-wide vx,vy : Moves a long/double value from vy to vx. vy may be in the 64k register range while wx is one of the first 256 registers.");
        mHintMap["move-wide/from16"] = tr ("move-wide/from16 vx,vy : Moves a long/double value from vy to vx. vy may be in the 64k register range while wx is one of the first 256 registers.");
        mHintMap["move-wide/16"] = tr ("move-wide/16 vx,vy : Moves a long/double value from vy to vx. vy may be in the 64k register range while wx is one of the first 256 registers.");
        mHintMap["move-object"] = tr ("move-object vx,vy : Moves the object reference from vy to vx.");
        mHintMap["move-object/from16"] = tr ("move-object/from16 vx,vy : Moves the object reference from vy to vx, vy can address 64k registers and vx can address 256 registers.");
        mHintMap["move-object/16"] = tr ("move-object/16 vx,vy : Moves the object reference from vy to vx, vy can address 64k registers and vx can address 256 registers.");
        mHintMap["move-result"] = tr ("move-result vx : Move the result value of the previous method invocation into vx.");
        mHintMap["move-result-wide"] = tr ("move-result-wide vx : Move the long/double result value of the previous method invocation into vx,vx+1.");
        mHintMap["move-result-object"] = tr ("move-result-object vx : Move the result object reference of the previous method invocation into vx.");
        mHintMap["move-exception"] = tr ("move-exception vx : Move the exception object reference thrown during a method invocation into vx.");
        mHintMap["return-void"] = tr ("return-void : Return without a return value");
        mHintMap["return"] = tr ("return vx : Return with vx return value");
        mHintMap["return-wide"] = tr ("return-wide vx : Return with double/long result in vx,vx+1.");
        mHintMap["return-object"] = tr ("return-object vx : Return with vx object reference value.");
        mHintMap["const/4"] = tr ("const/4 vx,lit4 : Puts the 4 bit constant into vx");
        mHintMap["const/16"] = tr ("const/16 vx,lit16 : Puts the 16 bit constant into vx");
        mHintMap["const"] = tr ("const vx, lit32 : Puts the integer constant into vx");
        mHintMap["const/high16"] = tr ("const/high16 v0, lit16 : Puts the 16 bit constant into the topmost bits of the register. Used to initialize float values.");
        mHintMap["const-wide/16"] = tr ("const-wide/16 vx, lit16 : Puts the integer constant into vx and vx+1 registers, expanding the integer constant into a long constant..");
        mHintMap["const-wide/32"] = tr ("const-wide/32 vx, lit32 : Puts the 32 bit constant into vx and vx+1 registers, expanding the integer constant into a long constant.");
        mHintMap["const-wide"] = tr ("const-wide vx, lit64 : Puts the 64 bit constant into vx and vx+1 registers.");
        mHintMap["const-wide/high16"] = tr ("const-wide/high16 vx,lit16 : Puts the 16 bit constant into the highest 16 bit of vx and vx+1 registers. Used to initialize double values.");
        mHintMap["const-string"] = tr ("const-string vx,string_id : Puts reference to a string constant identified by string_id into vx.");
        mHintMap["const-string-jumbo"] = tr ("const-string-jumbo vx,string_id : Puts reference to a string constant identified by string_id into vx.");
        mHintMap["const-class"] = tr ("const-class vx,type_id : Moves the class object of a class identified by type_id (e.g. Object.class) into vx.");
        mHintMap["monitor-enter"] = tr ("monitor-enter vx : Obtains the monitor of the object referenced by vx.");
        mHintMap["monitor-exit"] = tr ("monitor-exit : Releases the monitor of the object referenced by vx.");
        mHintMap["check-cast"] = tr ("check-cast vx, type_id : Checks whether the object reference in vx can be cast to an instance of a class referenced by type_id. Throws ClassCastException if the cast is not possible, continues execution otherwise.");
        mHintMap["instance-of"] = tr ("instance-of vx,vy,type_id : Checks whether vy is instance of a class identified by type_id. Sets vx non-zero if it is, 0 otherwise.");
        mHintMap["array-length"] = tr ("array-length vx,vy : Calculates the number of elements of the array referenced by vy and puts the length value into vx.");
        mHintMap["new-instance"] = tr ("new-instance vx,type : Instantiates an object type and puts the reference of the newly created instance into vx.");
        mHintMap["new-array"] = tr ("new-array vx,vy,type_id : Generates a new array of type_id type and vy element size and puts the reference to the array into vx.");
        mHintMap["filled-new-array"] = tr ("filled-new-array {parameters},type_id : Generates a new array of type_id and fills it with the parameters5. Reference to the newly generated array can be obtained by a move-result-object instruction, immediately following the filled-new-array instruction.");
        mHintMap["filled-new-array-range"] = tr ("filled-new-array-range {vx..vy},type_id : Generates a new array of type_id and fills it with a range of parameters. Reference to the newly generated array can be obtained by a move-result-object instruction, immediately following the filled-new-array instruction.");
        mHintMap["fill-array-data"] = tr ("fill-array-data vx,array_data_offset : Fills the array referenced by vx with the static data. The location of the static data is the sum of  the position of the current instruction and the offset");
        mHintMap["throw"] = tr ("throw vx : Throws an exception object. The reference of the exception object is in vx.");
        mHintMap["goto"] = tr ("goto target : Unconditional jump by short offset.");
        mHintMap["goto/16"] = tr ("goto/16 target : Unconditional jump by 16 bit offset.");
        mHintMap["goto/32"] = tr ("goto/32 target");
        mHintMap["packed-switch"] = tr ("packed-switch vx,table : Implements a switch statement where the case constants are close to each other. The instruction uses an index table. vx indexes into this table to find the offset of the instruction for a particular case. If vx falls out of the index table, the execution continues on the next instruction (default case).");
        mHintMap["sparse-switch"] = tr ("sparse-switch vx,table : Implements a switch statement with sparse case table. The instruction uses a lookup table with case constants and offsets for each case constant. If there is no match in the table, execution continues on the next instruction (default case).");
        mHintMap["cmpl-float"] = tr ("cmpl-float : Compares the float values in vy and vz and sets the integer value in vx accordingly3");
        mHintMap["cmpg-float"] = tr ("cmpg-float vx, vy, vz : Compares the float values in vy and vz and sets the integer value in vx accordingly3.");
        mHintMap["cmpl-double"] = tr ("cmpl-double vx,vy,vz : Compares the double values in vy and vz2 and sets the integer value in vx accordingly3.");
        mHintMap["cmpg-double"] = tr ("cmpg-double vx, vy, vz : Compares the double values in vy and vz2 and sets the integer value in vx accordingly3.");
        mHintMap["cmp-long"] = tr ("cmp-long vx, vy, vz : Compares the long values in vy and vz and sets the integer value in vx accordingly3.");
        mHintMap["if-eq"] = tr ("if-eq vx,vy,target : Jumps to target if vx==vy2. vx and vy are integer values.");
        mHintMap["if-ne"] = tr ("if-ne vx,vy,target : Jumps to target if vx!=vy2. vx and vy are integer values.");
        mHintMap["if-lt"] = tr ("if-lt vx,vy,target : Jumps to target is vx<vy2. vx and vy are integer values.");
        mHintMap["if-ge"] = tr ("if-ge vx, vy,target : Jumps to target if vx>=vy2. vx and vy are integer values.");
        mHintMap["if-gt"] = tr ("if-gt vx,vy,target : Jumps to target if vx>vy2. vx and vy are integer values.");
        mHintMap["if-le"] = tr ("if-le vx,vy,target : Jumps to target if vx<=vy2. vx and vy are integer values.");
        mHintMap["if-eqz"] = tr ("if-eqz vx,target : Jumps to target if vx==02. vx is an integer value.");
        mHintMap["if-nez"] = tr ("if-nez vx,target : Checks vx and jumps if vx is nonzero2.");
        mHintMap["if-ltz"] = tr ("if-ltz vx,target : Checks vx and jumps if vx<02.");
        mHintMap["if-gez"] = tr ("if-gez vx,target : Checks vx and jumps if vx>=02.");
        mHintMap["if-gtz"] = tr ("if-gtz vx,target : Checks vx and jumps if vx>02.");
        mHintMap["if-lez"] = tr ("if-lez vx,target : Checks vx and jumps if vx<=02.");
        mHintMap["unused_3E"] = tr ("unused_3E");
        mHintMap["unused_3F"] = tr ("unused_3F");
        mHintMap["unused_40"] = tr ("unused_40");
        mHintMap["unused_41"] = tr ("unused_41");
        mHintMap["unused_42"] = tr ("unused_42");
        mHintMap["unused_43"] = tr ("unused_43");
        mHintMap["aget"] = tr ("aget vx,vy,vz : Gets an integer value of an object reference array into vx. The array is referenced by vy and is indexed by vz.");
        mHintMap["aget-wide"] = tr ("aget-wide vx,vy,vz : Gets a long/double value of long/double array into vx,vx+1. The array is referenced by vy and is indexed by vz.");
        mHintMap["aget-object"] = tr ("aget-object vx,vy,vz : Gets an object reference value of an object reference array into vx. The array is referenced by vy and is indexed by vz.");
        mHintMap["aget-boolean"] = tr ("aget-boolean vx,vy,vz : Gets a boolean value of a boolean array into vx. The array is referenced by vy and is indexed by vz.");
        mHintMap["aget-byte"] = tr ("aget-byte vx,vy,vz : Gets a byte value of a byte array into vx. The array is referenced by vy and is indexed by vz.");
        mHintMap["aget-char"] = tr ("aget-char vx, vy,vz : Gets a char value  of a character array into vx. The element is indexed by vz, the array object is referenced by vy");
        mHintMap["aget-short"] = tr ("aget-short vx,vy,vz : Gets a short value  of a short array into vx. The element is indexed by vz, the array object is referenced by vy.");
        mHintMap["aput"] = tr ("aput vx,vy,vz : Puts the integer value in vx into an element of an integer array. The element is indexed by vz, the array object is referenced by vy.");
        mHintMap["aput-wide"] = tr ("aput-wide vx,vy,vz : Puts the double/long value in vx,vx+1 into a double/long array. The array is referenced by vy, the element is indexed by vz.");
        mHintMap["aput-object"] = tr ("aput-object vx,vy,vz : Puts the object reference value in vx into an element of an object reference array. The element is indexed by vz, the array object is referenced by vy.");
        mHintMap["aput-boolean"] = tr ("aput-boolean vx,vy,vz : Puts the boolean value in vx into an element of a boolean array. The element is indexed by vz, the array object is referenced by vy.");
        mHintMap["aput-byte"] = tr ("aput-byte vx,vy,vz : Puts the byte value in vx into an element of a byte array. The element is indexed by vz, the array object is referenced by vy.");
        mHintMap["aput-char"] = tr ("aput-char vx,vy,vz : Puts the char value in vx into an element of a character array. The element is indexed by vz, the array object is referenced by vy.");
        mHintMap["aput-short"] = tr ("aput-short vx,vy,vz : Puts the short value in vx into an element of a short array. The element is indexed by vz, the array object is referenced by vy.");
        mHintMap["iget"] = tr ("iget vx, vy, field_id : Reads an instance field into vx. The instance is referenced by vy.");
        mHintMap["iget-wide"] = tr ("iget-wide vx,vy,field_id : Reads an instance field into vx1. The instance is referenced by vy.");
        mHintMap["iget-object"] = tr ("iget-object vx,vy,field_id : Reads an object reference instance field into vx. The instance is referenced by vy.");
        mHintMap["iget-boolean"] = tr ("iget-boolean vx,vy,field_id : Reads a boolean instance field into vx. The instance is referenced by vy.");
        mHintMap["iget-byte"] = tr ("iget-byte vx,vy,field_id : Reads a byte instance field into vx. The instance is referenced by vy.");
        mHintMap["iget-char"] = tr ("iget-char vx,vy,field_id : Reads a char instance field into vx. The instance is referenced by vy.");
        mHintMap["iget-short"] = tr ("iget-short vx,vy,field_id : Reads a short instance field into vx. The instance is referenced by vy.");
        mHintMap["iput"] = tr ("iput vx,vy, field_id : Puts vx into an instance field. The instance is referenced by vy.");
        mHintMap["iput-wide"] = tr ("iput-wide vx,vy, field_id : Puts the wide value located in vx and vx+1 registers into an instance field. The instance is referenced by vy.");
        mHintMap["iput-object"] = tr ("iput-object vx,vy,field_id : Puts the object reference in vx into an instance field. The instance is referenced by vy.");
        mHintMap["iput-boolean"] = tr ("iput-boolean vx,vy, field_id : Puts the boolean value located in vx into an instance field. The instance is referenced by vy.");
        mHintMap["iput-byte"] = tr ("iput-byte vx,vy,field_id : Puts the byte value located in vx into an instance field. The instance is referenced by vy.");
        mHintMap["iput-char"] = tr ("iput-char vx,vy,field_id : Puts the char value located in vx into an instance field. The instance is referenced by vy.");
        mHintMap["iput-short"] = tr ("iput-short vx,vy,field_id : Puts the short value located in vx into an instance field. The instance is referenced by vy.");
        mHintMap["sget"] = tr ("sget vx,field_id : Reads the integer field identified by the field_id into vx.");
        mHintMap["sget-wide"] = tr ("sget-wide vx, field_id : Reads the static field identified by the field_id into vx and vx+1 registers.");
        mHintMap["sget-object"] = tr ("sget-object vx,field_id : Reads the object reference field identified by the field_id into vx.");
        mHintMap["sget-boolean"] = tr ("sget-boolean vx,field_id : Reads the boolean static field identified by the field_id into vx.");
        mHintMap["sget-byte"] = tr ("sget-byte vx,field_id : Reads the byte static field identified by the field_id into vx.");
        mHintMap["sget-char"] = tr ("sget-char vx,field_id : Reads the char static field identified by the field_id into vx.");
        mHintMap["sget-short"] = tr ("sget-short vx,field_id : Reads the short static field identified by the field_id into vx.");
        mHintMap["sput"] = tr ("sput vx, field_id : Puts vx into a static field.");
        mHintMap["sput-wide"] = tr ("sput-wide vx, field_id : Puts vx and vx+1 into a static field.");
        mHintMap["sput-object"] = tr ("sput-object vx,field_id : Puts object reference in vx into a static field.");
        mHintMap["sput-boolean"] = tr ("sput-boolean vx,field_id : Puts boolean value in vx into a static field.");
        mHintMap["sput-byte"] = tr ("sput-byte vx,field_id : Puts byte value in vx into a static field.");
        mHintMap["sput-char"] = tr ("sput-char vx,field_id : Puts char value in vx into a static field.");
        mHintMap["sput-short"] = tr ("sput-short vx,field_id : Puts short value in vx into a static field.");
        mHintMap["invoke-virtual"] = tr ("invoke-virtual { parameters }, methodtocall : Invokes a virtual method with parameters.");
        mHintMap["invoke-super"] = tr ("invoke-super {parameter},methodtocall : Invokes the virtual method of the immediate parent class.");
        mHintMap["invoke-direct"] = tr ("invoke-direct { parameters }, methodtocall : Invokes a method with parameters without the virtual method resolution.");
        mHintMap["invoke-static"] = tr ("invoke-static {parameters}, methodtocall : Invokes a static method with parameters.");
        mHintMap["invoke-interface"] = tr ("invoke-interface {parameters},methodtocall : Invokes an interface method.");
        mHintMap["unused_73"] = tr ("unused_73");
        mHintMap["invoke-virtual/range"] = tr ("invoke-virtual/range {vx..vy},methodtocall : Invokes virtual method with a range of registers. The instruction specifies the first register and the number of registers to be passed to the method.");
        mHintMap["invoke-super/range"] = tr ("invoke-super/range : Invokes  the virtual method of the immediate parent class. The instruction specifies the first register and the number of registers to be passed to the method.");
        mHintMap["invoke-direct/range"] = tr ("invoke-direct/range {vx..vy},methodtocall : Invokes direct method with a range of registers. The instruction specifies the first register and the number of registers to be passed to the method.");
        mHintMap["invoke-static/range"] = tr ("invoke-static/range {vx..vy},methodtocall : Invokes static method with a range of registers. The instruction specifies the first register and the number of registers to be passed to the method.");
        mHintMap["invoke-interface-range"] = tr ("invoke-interface-range : Invokes an interface method with a range of registers. The instruction specifies the first register and the number of registers to be passed to the method.");
        mHintMap["unused_79"] = tr ("unused_79");
        mHintMap["unused_7A"] = tr ("unused_7A");
        mHintMap["neg-int"] = tr ("neg-int vx,vy : Calculates vx=-vy.");
        mHintMap["not-int"] = tr ("not-int vx,vy");
        mHintMap["neg-long"] = tr ("neg-long vx,vy : Calculates vx,vx+1=-(vy,vy+1)");
        mHintMap["not-long"] = tr ("not-long vx,vy");
        mHintMap["neg-float"] = tr ("neg-float vx,vy : Calculates vx=-vy");
        mHintMap["neg-double"] = tr ("neg-double vx,vy : Calculates vx,vx+1=-(vy,vy+1)");
        mHintMap["int-to-long"] = tr ("int-to-long vx, vy : Converts the integer in vy into a long in vx,vx+1.");
        mHintMap["int-to-float"] = tr ("int-to-float vx, vy : Converts the integer in vx into a float in vx.");
        mHintMap["int-to-double"] = tr ("int-to-double vx, vy : Converts the integer in vy into the double in vx,vx+1.");
        mHintMap["long-to-int"] = tr ("long-to-int vx,vy : Converts the long value in vy,vy+1 into an integer in vx.");
        mHintMap["long-to-float"] = tr ("long-to-float vx, vy : Converts the long value in vy,vy+1 into a float in vx.");
        mHintMap["long-to-double"] = tr ("long-to-double vx, vy : Converts the long value in vy,vy+1 into a double value in vx,vx+1.");
        mHintMap["float-to-int"] = tr ("float-to-int vx, vy : Converts the float value in vy into an integer value in vx.");
        mHintMap["float-to-long"] = tr ("float-to-long vx,vy : Converts the float value in vy into a long value in vx.");
        mHintMap["float-to-double"] = tr ("float-to-double vx, vy : Converts the float value in vy into a double value in vx,vx+1.");
        mHintMap["double-to-int"] = tr ("double-to-int vx, vy : Converts the double value in vy,vy+1 into an integer value in vx.");
        mHintMap["double-to-long"] = tr ("double-to-long vx, vy : Converts the double value in vy,vy+1 into a long value in vx,vx+1.");
        mHintMap["double-to-float"] = tr ("double-to-float vx, vy : Converts the double value in vy,vy+1 into a float value in vx.");
        mHintMap["int-to-byte"] = tr ("int-to-byte vx,vy : Converts the int value in vy to a byte value and stores it in vx.");
        mHintMap["int-to-char"] = tr ("int-to-char vx,vy : Converts the int value in vy to a char value and stores it in vx.");
        mHintMap["int-to-short"] = tr ("int-to-short vx,vy : Converts the int value in vy to a short value and stores it in vx.");
        mHintMap["add-int"] = tr ("add-int vx,vy,vz : Calculates vy+vz and puts the result into vx.");
        mHintMap["sub-int"] = tr ("sub-int vx,vy,vz : Calculates vy-vz and puts the result into vx.");
        mHintMap["mul-int"] = tr ("mul-int vx, vy, vz : Multiplies vz with wy and puts the result int vx.");
        mHintMap["div-int"] = tr ("div-int vx,vy,vz : Divides vy with vz and puts the result into vx.");
        mHintMap["rem-int"] = tr ("rem-int vx,vy,vz : Calculates vy % vz and puts the result into vx.");
        mHintMap["and-int"] = tr ("and-int vx, vy, vz : Calculates vy AND vz and puts the result into vx.");
        mHintMap["or-int"] = tr ("or-int vx, vy, vz : Calculates vy OR vz and puts the result into vx.");
        mHintMap["xor-int"] = tr ("xor-int vx, vy, vz : Calculates vy XOR vz and puts the result into vx.");
        mHintMap["shl-int"] = tr ("shl-int vx, vy, vz : Shift vy left by the positions specified by vz and store the result into vx.");
        mHintMap["shr-int"] = tr ("shr-int vx, vy, vz : Shift vy right by the positions specified by vz and store the result into vx.");
        mHintMap["ushr-int"] = tr ("ushr-int vx, vy, vz : Unsigned shift right (>>>) vy by the positions specified by vz and store the result into vx.");
        mHintMap["add-long"] = tr ("add-long vx, vy, vz : Adds vy to vz and puts the result into vx1.");
        mHintMap["sub-long"] = tr ("sub-long vx,vy,vz : Calculates vy-vz and puts the result into vx1.");
        mHintMap["mul-long"] = tr ("mul-long vx,vy,vz : Calculates vy*vz and puts the result into vx1.");
        mHintMap["div-long"] = tr ("div-long vx, vy, vz : Calculates vy/vz and puts the result into vx1.");
        mHintMap["rem-long"] = tr ("rem-long vx,vy,vz : Calculates vy % vz and puts the result into vx1.");
        mHintMap["and-long"] = tr ("and-long vx, vy, vz : Calculates the vy AND vz and puts the result into vx1.");
        mHintMap["or-long"] = tr ("or-long vx, vy, vz : Calculates the vy OR vz and puts the result into vx1.");
        mHintMap["xor-long"] = tr ("xor-long vx, vy, vz : Calculates the vy XOR vz and puts the result into vx1.");
        mHintMap["shl-long"] = tr ("shl-long vx, vy, vz : Shifts left vy by vz positions and stores the result in vx1.");
        mHintMap["shr-long"] = tr ("shr-long vx,vy,vz : Shifts right vy by vz positions and stores the result in vx1.");
        mHintMap["ushr-long"] = tr ("ushr-long vx, vy, vz : Unsigned shifts right vy by vz positions and stores the result in vx1.");
        mHintMap["add-float"] = tr ("add-float vx,vy,vz : Adds vy to vz and puts the result into vx.");
        mHintMap["sub-float"] = tr ("sub-float vx,vy,vz : Calculates vy-vz and puts the result into vx.");
        mHintMap["mul-float"] = tr ("mul-float vx, vy, vz : Multiplies vy with vz and puts the result into vx.");
        mHintMap["div-float"] = tr ("div-float vx, vy, vz : Calculates vy/vz and puts the result into vx.");
        mHintMap["rem-float"] = tr ("rem-float vx,vy,vz : Calculates vy % vz and puts the result into vx.");
        mHintMap["add-double"] = tr ("add-double vx,vy,vz : Adds vy to vz and puts the result into vx1.");
        mHintMap["sub-double"] = tr ("sub-double vx,vy,vz : Calculates vy-vz and puts the result into vx1.");
        mHintMap["mul-double"] = tr ("mul-double vx, vy, vz : Multiplies vy with vz and puts the result into vx1.");
        mHintMap["div-double"] = tr ("div-double vx, vy, vz : Calculates vy/vz and puts the result into vx1.");
        mHintMap["rem-double"] = tr ("rem-double vx,vy,vz : Calculates vy % vz and puts the result into vx1.");
        mHintMap["add-int/2addr"] = tr ("add-int/2addr vx,vy : Adds vy to vx.");
        mHintMap["sub-int/2addr"] = tr ("sub-int/2addr vx,vy : Calculates vx-vy and puts the result into vx.");
        mHintMap["mul-int/2addr"] = tr ("mul-int/2addr vx,vy : Multiplies vx with vy.");
        mHintMap["div-int/2addr"] = tr ("div-int/2addr vx,vy : Divides vx with vy and puts the result into vx.");
        mHintMap["rem-int/2addr"] = tr ("rem-int/2addr vx,vy : Calculates vx % vy and puts the result into vx");
        mHintMap["and-int/2addr"] = tr ("and-int/2addr vx, vy : Calculates vx AND vy and puts the result into vx.");
        mHintMap["or-int/2addr"] = tr ("or-int/2addr vx, vy : Calculates vx OR vy and puts the result into vx.");
        mHintMap["xor-int/2addr"] = tr ("xor-int/2addr vx, vy : Calculates vx XOR vy and puts the result into vx.");
        mHintMap["shl-int/2addr"] = tr ("shl-int/2addr vx, vy : Shifts vx left by vy positions.");
        mHintMap["shr-int/2addr"] = tr ("shr-int/2addr vx, vy : Shifts vx right by vy positions.");
        mHintMap["ushr-int/2addr"] = tr ("ushr-int/2addr vx, vy : Unsigned shift right (>>>) vx by the positions specified by vy.");
        mHintMap["add-long/2addr"] = tr ("add-long/2addr vx,vy : Adds vy to vx1.");
        mHintMap["sub-long/2addr"] = tr ("sub-long/2addr vx,vy : Calculates vx-vy and puts the result into vx1.");
        mHintMap["mul-long/2addr"] = tr ("mul-long/2addr vx,vy : Calculates vx*vy and puts the result into vx1.");
        mHintMap["div-long/2addr"] = tr ("div-long/2addr vx, vy : Calculates vx/vy and puts the result into vx1.");
        mHintMap["rem-long/2addr"] = tr ("rem-long/2addr vx,vy : Calculates vx % vy and puts the result into vx1.");
        mHintMap["and-long/2addr"] = tr ("and-long/2addr vx, vy : Calculates vx AND vy and puts the result into vx1.");
        mHintMap["or-long/2addr"] = tr ("or-long/2addr vx, vy : Calculates vx OR vy and puts the result into vx1.");
        mHintMap["xor-long/2addr"] = tr ("xor-long/2addr vx, vy : Calculates vx XOR vy and puts the result into vx1.");
        mHintMap["shl-long/2addr"] = tr ("shl-long/2addr vx, vy : Shifts left the value in vx,vx+1 by the positions specified by vy and stores the result in vx,vx+1.");
        mHintMap["shr-long/2addr"] = tr ("shr-long/2addr vx, vy : Shifts right the value in vx,vx+1 by the positions specified by vy and stores the result in vx,vx+1.");
        mHintMap["ushr-long/2addr"] = tr ("ushr-long/2addr vx, vy : Unsigned shifts right the value in vx,vx+1 by the positions specified by vy and stores the result in vx,vx+1.");
        mHintMap["add-float/2addr"] = tr ("add-float/2addr vx,vy : Adds vy to vx.");
        mHintMap["sub-float/2addr"] = tr ("sub-float/2addr vx,vy : Calculates vx-vy and stores the result in vx.");
        mHintMap["mul-float/2addr"] = tr ("mul-float/2addr vx, vy : Multiplies vx with vy.");
        mHintMap["div-float/2addr"] = tr ("div-float/2addr vx, vy : Calculates vx/vy and puts the result into vx.");
        mHintMap["rem-float/2addr"] = tr ("rem-float/2addr vx,vy : Calculates vx/vy and puts the result into vx.");
        mHintMap["add-double/2addr"] = tr ("add-double/2addr vx, vy : Adds vy to vx1.");
        mHintMap["sub-double/2addr"] = tr ("sub-double/2addr vx, vy : Calculates vx-vy and puts the result into vx1.");
        mHintMap["mul-double/2addr"] = tr ("mul-double/2addr vx, vy : Multiplies vx with vy1.");
        mHintMap["div-double/2addr"] = tr ("div-double/2addr vx, vy : Calculates vx/vy and puts the result into vx1.");
        mHintMap["rem-double/2addr"] = tr ("rem-double/2addr vx,vy : Calculates vx % vy and puts the result into vx1.");
        mHintMap["add-int/lit16"] = tr ("add-int/lit16 vx,vy,lit16 : Adds vy to lit16 and stores the result into vx.");
        mHintMap["sub-int/lit16"] = tr ("sub-int/lit16 vx,vy,lit16 : Calculates vy - lit16 and stores the result into vx.");
        mHintMap["mul-int/lit16"] = tr ("mul-int/lit16 vx,vy,lit16 : Calculates vy * lit16 and stores the result into vx.");
        mHintMap["div-int/lit16"] = tr ("div-int/lit16 vx,vy,lit16 : Calculates vy / lit16 and stores the result into vx.");
        mHintMap["rem-int/lit16"] = tr ("rem-int/lit16 vx,vy,lit16 : Calculates vy % lit16 and stores the result into vx.");
        mHintMap["and-int/lit16"] = tr ("and-int/lit16 vx,vy,lit16 : Calculates vy AND lit16 and stores the result into vx.");
        mHintMap["or-int/lit16"] = tr ("or-int/lit16 vx,vy,lit16 : Calculates vy OR lit16 and stores the result into vx.");
        mHintMap["xor-int/lit16"] = tr ("xor-int/lit16 vx,vy,lit16 : Calculates vy XOR lit16 and stores the result into vx.");
        mHintMap["add-int/lit8"] = tr ("add-int/lit8 vx,vy,lit8 : Adds vy to lit8 and stores the result into vx.");
        mHintMap["sub-int/lit8"] = tr ("sub-int/lit8 vx,vy,lit8 : Calculates vy-lit8 and stores the result into vx.");
        mHintMap["mul-int/lit8"] = tr ("mul-int/lit8 vx,vy,lit8 : Multiplies vy with lit8 8-bit literal constant and puts the result into vx.");
        mHintMap["div-int/lit8"] = tr ("div-int/lit8 vx,vy,lit8 : Calculates vy/lit8 and stores the result into vx.");
        mHintMap["rem-int/lit8"] = tr ("rem-int/lit8 vx,vy,lit8 : Calculates vy % lit8 and stores the result into vx.");
        mHintMap["and-int/lit8"] = tr ("and-int/lit8 vx,vy,lit8 : Calculates vy AND lit8 and stores the result into vx.");
        mHintMap["or-int/lit8"] = tr ("or-int/lit8 vx, vy, lit8 : Calculates vy OR lit8 and puts the result into vx.");
        mHintMap["xor-int/lit8"] = tr ("xor-int/lit8 vx, vy, lit8 : Calculates vy XOR lit8 and puts the result into vx.");
        mHintMap["shl-int/lit8"] = tr ("shl-int/lit8 vx, vy, lit8 : Shift v0 left by the bit positions specified by the literal constant and put the result into vx.");
        mHintMap["shr-int/lit8"] = tr ("shr-int/lit8 vx, vy, lit8 : Shift v0 right by the bit positions specified by the literal constant and put the result into vx.");
        mHintMap["ushr-int/lit8"] = tr ("ushr-int/lit8 vx, vy, lit8 : Unsigned right shift of v0 (>>>) by the bit positions specified by the literal constant and put the result into vx.");
        mHintMap["iget-volatile"] = tr ("iget-volatile");
        mHintMap["iput-volatile"] = tr ("iput-volatile");
        mHintMap["sget-volatile"] = tr ("sget-volatile");
        mHintMap["sput-volatile"] = tr ("sput-volatile");
        mHintMap["iget-object-volatile"] = tr ("iget-object-volatile");
        mHintMap["iget-wide-volatile"] = tr ("iget-wide-volatile");
        mHintMap["iput-wide-volatile"] = tr ("iput-wide-volatile");
        mHintMap["sget-wide-volatile"] = tr ("sget-wide-volatile");
        mHintMap["sput-wide-volatile"] = tr ("sput-wide-volatile");
        mHintMap["breakpoint"] = tr ("breakpoint");
        mHintMap["throw-verification-error"] = tr ("throw-verification-error");
        mHintMap["execute-inline"] = tr ("execute-inline {parameters},inline ID : Executes the inline method identified by inline ID6.");
        mHintMap["execute-inline/range"] = tr ("execute-inline/range");
        mHintMap["invoke-object-init/range"] = tr ("invoke-object-init/range");
        mHintMap["return-void-barrier"] = tr ("return-void-barrier");
        mHintMap["iget-quick"] = tr ("iget-quick vx,vy,offset : Gets the value stored at offset in vy instance's data area to vx6.");
        mHintMap["iget-wide-quick"] = tr ("iget-wide-quick vx,vy,offset : Gets the object reference value stored at offset in vy instance's data area to vx,vx+16.");
        mHintMap["iget-object-quick"] = tr ("iget-object-quick vx,vy,offset : Gets the object reference value stored at offset in vy instance's data area to vx6.");
        mHintMap["iput-quick"] = tr ("iput-quick vx,vy,offset : Puts the value stored in vx to offset in vy instance's data area6.");
        mHintMap["iput-wide-quick"] = tr ("iput-wide-quick vx,vy,offset : Puts the value stored in vx,vx+1 to offset in vy instance's data area6.");
        mHintMap["iput-object-quick"] = tr ("iput-object-quick vx,vy,offset : Puts the object reference value stored in vx to offset in vy instance's data area to vx6.");
        mHintMap["invoke-virtual-quick"] = tr ("invoke-virtual-quick {parameters},vtable offset : Invokes a virtual method using the vtable of the target object6.");
        mHintMap["invoke-virtual-quick/range"] = tr ("invoke-virtual-quick/range {parameter range},vtable offset  : Invokes a virtual method using the vtable of the target object6");
        mHintMap["invoke-super-quick"] = tr ("invoke-super-quick {parameters},vtable offset : Invokes a virtual method in the target object's immediate parent class using the vtable of that parent class6.");
        mHintMap["invoke-super-quick/range"] = tr ("invoke-super-quick/range {register range},vtable offset : Invokes a virtual method in the target object's immediate parent class using the vtable of that parent class6.");
        mHintMap["iput-object-volatile"] = tr ("iput-object-volatile");
        mHintMap["sget-object-volatile"] = tr ("sget-object-volatile");
        mHintMap["sput-object-volatile"] = tr ("sput-object-volatile");
        mHintMap["unused-ff"] = tr ("unused-ff");
        mHintMap[".catch"] = tr (".catch type {fromLabel .. tolabel} :target : catch exception type between fromLabel and tolabel. If exception occureded, jump to target");
        mHintMap[".catchll"] = tr (".catchll {fromLabel .. tolabel} :target : catch exception type between fromLabel and tolabel. If exception occureded, jump to target");
    }
    auto it = mHintMap.find (token);
    if(it != mHintMap.end ()) {
        return it.value();
    } else {
        return "";
    }
}
