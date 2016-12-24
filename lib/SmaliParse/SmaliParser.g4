//===- SmaliParser.g4 - ART-LEX -------------------------------*- ANTLR4 -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file define Smali Parser with ANTLR4.
//
//===----------------------------------------------------------------------===//
parser grammar SmaliParser;

options {
    tokenVocab = SmaliLexer;
}


// These are all supported parser sections:

// Parser file header. Appears at the top in all parser related files. Use e.g. for copyrights.
@parser::header {/* parser/listener/visitor header section */
    #include "LiteralTools.h"
}

// Appears before any #include in h + cpp files.
@parser::preinclude {/* parser precinclude section */}

// Follows directly after the standard #includes in h + cpp files.
@parser::postinclude {
/* parser postinclude section */
}

// Directly preceeds the parser class declaration in the h file (e.g. for additional types etc.).
@parser::context {/* parser context section */}

// Appears in the private part of the parser in the h file.
// The function bodies could also appear in the definitions section, but I want to maximize
// Java compatibility, so we can also create a Java parser from this grammar.
// Still, some tweaking is necessary after the Java file generation (e.g. bool -> boolean).
@parser::members {
/* public parser declarations/members section */

}

// Appears in the public part of the parser in the h file.
@parser::declarations {/* private parser declarations section */
//    bool allowOdex;
}

// Appears in line with the other class member definitions in the cpp file.
@parser::definitions {/* parser definitions section */}

// Additionally there are similar sections for (base)listener and (base)visitor files.
@parser::listenerpreinclude {/* listener preinclude section */}
@parser::listenerpostinclude {/* listener postinclude section */}
@parser::listenerdeclarations {/* listener public declarations/members section */}
@parser::listenermembers {/* listener private declarations/members section */}
@parser::listenerdefinitions {/* listener definitions section */}

@parser::baselistenerpreinclude {/* base listener preinclude section */}
@parser::baselistenerpostinclude {/* base listener postinclude section */}
@parser::baselistenerdeclarations {/* base listener public declarations/members section */}
@parser::baselistenermembers {/* base listener private declarations/members section */}
@parser::baselistenerdefinitions {/* base listener definitions section */}

@parser::visitorpreinclude {/* visitor preinclude section */}
@parser::visitorpostinclude {/* visitor postinclude section */}
@parser::visitordeclarations {/* visitor public declarations/members section */}
@parser::visitormembers {/* visitor private declarations/members section */}
@parser::visitordefinitions {/* visitor definitions section */}

@parser::basevisitorpreinclude {/* base visitor preinclude section */}
@parser::basevisitorpostinclude {/* base visitor postinclude section */}
@parser::basevisitordeclarations {/* base visitor public declarations/members section */}
@parser::basevisitormembers {/* base visitor private declarations/members section */}
@parser::basevisitordefinitions {/* base visitor definitions section */}


smali_file
  locals [bool hasClassSpec, bool hasSuperSpec, bool hasSourceSpec, bool isValid]
  @init
  { $hasClassSpec = $hasSuperSpec = $hasSourceSpec = false;
    $isValid = true;
  }
  :
  ( {!$hasClassSpec}? class_spec {$hasClassSpec = true;}
  | {!$hasSuperSpec}? super_spec {$hasSuperSpec = true;}
  | implements_spec
  | {!$hasSourceSpec}? source_spec {$hasSourceSpec = true;}
  | method
  | field
  | annotation
  )+
  EOF
  {
    if (!$hasClassSpec) {
        $isValid = false;
    }

    if (!$hasSuperSpec) {
      if ($class_spec.className == "Ljava/lang/Object;") {
        $isValid = false;
      }
    }
  }
  ;

class_spec returns[std::string className]
  : CLASS_DIRECTIVE access_list CLASS_DESCRIPTOR {$className = $CLASS_DESCRIPTOR.text;};

super_spec
  : SUPER_DIRECTIVE CLASS_DESCRIPTOR;

implements_spec
  : IMPLEMENTS_DIRECTIVE CLASS_DESCRIPTOR;

source_spec
  : SOURCE_DIRECTIVE STRING_LITERAL;

access_list
  : ACCESS_SPEC*;


/*When there are annotations immediately after a field definition, we don't know whether they are field annotations
or class annotations until we determine if there is an .end field directive. In either case, we still "consume" and parse
the annotations. If it turns out that they are field annotations, we include them in the I_FIELD AST. Otherwise, we
add them to the $classAnnotations list*/
field
  : FIELD_DIRECTIVE access_list member_name COLON nonvoid_type_descriptor (EQUAL literal)?
    ( ({getInputStream()->LA(1) == ANNOTATION_DIRECTIVE}? annotation)*
      ( END_FIELD_DIRECTIVE
      | /*epsilon*/
      )
    );

method
  : METHOD_DIRECTIVE access_list member_name method_prototype statements_and_directives
    END_METHOD_DIRECTIVE;

statements_and_directives
  locals [
     bool hasRegistersDirective
  ]
  : {
      $hasRegistersDirective = false;
    }
    ( ordered_method_item
    | registers_directive
    | catch_directive
    | catchall_directive
    | parameter_directive
    | annotation
    )*
    ;

/* Method items whose order/location is important */
ordered_method_item
  : label
  | instruction
  | debug_directive;

registers_directive
  : (
      directive=REGISTERS_DIRECTIVE regCount=integral_literal
    | directive=LOCALS_DIRECTIVE regCount2=integral_literal
    )
    {
        // TODO check register local, only accept one.
    };

//param_list_or_id
//  : PARAM_LIST_OR_ID_PRIMITIVE_TYPE+;


/*identifiers are much more general than most languages. Any of the below can either be
the indicated type OR an identifier, depending on the context*/
simple_name
  : SIMPLE_NAME
  | ACCESS_SPEC
  | VERIFICATION_ERROR_TYPE
  | POSITIVE_INTEGER_LITERAL
  | NEGATIVE_INTEGER_LITERAL
  | FLOAT_LITERAL_OR_ID
  | DOUBLE_LITERAL_OR_ID
  | BOOL_LITERAL
  | NULL_LITERAL
  | REGISTER
//  | param_list_or_id -> { adaptor.create(SIMPLE_NAME, $param_list_or_id.text) }
  | PRIMITIVE_TYPE
  | VOID_TYPE
  | ANNOTATION_VISIBILITY
  | INSTRUCTION_FORMAT10t
  | INSTRUCTION_FORMAT10x
  | INSTRUCTION_FORMAT10x_ODEX
  | INSTRUCTION_FORMAT11x
  | INSTRUCTION_FORMAT12x_OR_ID
  | INSTRUCTION_FORMAT21c_FIELD
  | INSTRUCTION_FORMAT21c_FIELD_ODEX
  | INSTRUCTION_FORMAT21c_STRING
  | INSTRUCTION_FORMAT21c_TYPE
  | INSTRUCTION_FORMAT21t
  | INSTRUCTION_FORMAT22c_FIELD
  | INSTRUCTION_FORMAT22c_FIELD_ODEX
  | INSTRUCTION_FORMAT22c_TYPE
  | INSTRUCTION_FORMAT22cs_FIELD
  | INSTRUCTION_FORMAT22s_OR_ID
  | INSTRUCTION_FORMAT22t
  | INSTRUCTION_FORMAT23x
  | INSTRUCTION_FORMAT31i_OR_ID
  | INSTRUCTION_FORMAT31t
  | INSTRUCTION_FORMAT35c_METHOD
  | INSTRUCTION_FORMAT35c_METHOD_ODEX
  | INSTRUCTION_FORMAT35c_TYPE
  | INSTRUCTION_FORMAT35mi_METHOD
  | INSTRUCTION_FORMAT35ms_METHOD
  | INSTRUCTION_FORMAT45cc_METHOD
  | INSTRUCTION_FORMAT4rcc_METHOD
  | INSTRUCTION_FORMAT51l;

member_name
  : simple_name
  | MEMBER_NAME;

method_prototype
  : OPEN_PAREN param_list CLOSE_PAREN type_descriptor;

//param_list_or_id_primitive_type
//  : PARAM_LIST_OR_ID_PRIMITIVE_TYPE ;

param_list
  : nonvoid_type_descriptor*
//  | param_list_or_id_primitive_type+
  ;

array_descriptor
  : ARRAY_TYPE_PREFIX (PRIMITIVE_TYPE | CLASS_DESCRIPTOR);

type_descriptor
  : VOID_TYPE
  | PRIMITIVE_TYPE
  | CLASS_DESCRIPTOR
  | array_descriptor;

nonvoid_type_descriptor
  : PRIMITIVE_TYPE
  | CLASS_DESCRIPTOR
  | array_descriptor;

reference_type_descriptor
  : CLASS_DESCRIPTOR
  | array_descriptor;

integer_literal
  : POSITIVE_INTEGER_LITERAL
  | NEGATIVE_INTEGER_LITERAL;

float_literal
  : FLOAT_LITERAL_OR_ID
  | FLOAT_LITERAL;

double_literal
  : DOUBLE_LITERAL_OR_ID
  | DOUBLE_LITERAL;

literal
  : LONG_LITERAL
  | integer_literal
  | SHORT_LITERAL
  | BYTE_LITERAL
  | float_literal
  | double_literal
  | CHAR_LITERAL
  | STRING_LITERAL
  | BOOL_LITERAL
  | NULL_LITERAL
  | array_literal
  | subannotation
  | type_field_method_literal
  | enum_literal;

parsed_integer_literal returns[int value]
  : integer_literal { $value = LiteralTools::parseInt($integer_literal.text); };

integral_literal
  : LONG_LITERAL
  | integer_literal
  | SHORT_LITERAL
  | CHAR_LITERAL
  | BYTE_LITERAL;

fixed_32bit_literal
  : LONG_LITERAL
  | integer_literal
  | SHORT_LITERAL
  | BYTE_LITERAL
  | float_literal
  | CHAR_LITERAL
  | BOOL_LITERAL;

fixed_literal
  : integer_literal
  | LONG_LITERAL
  | SHORT_LITERAL
  | BYTE_LITERAL
  | float_literal
  | double_literal
  | CHAR_LITERAL
  | BOOL_LITERAL;

array_literal
  : OPEN_BRACE (literal (COMMA literal)* | ) CLOSE_BRACE;

annotation_element
  : simple_name EQUAL literal;

annotation
  : ANNOTATION_DIRECTIVE ANNOTATION_VISIBILITY CLASS_DESCRIPTOR
    annotation_element* END_ANNOTATION_DIRECTIVE;

subannotation
  : SUBANNOTATION_DIRECTIVE CLASS_DESCRIPTOR annotation_element* END_SUBANNOTATION_DIRECTIVE;

// TODO: how does dalvik handle a primitive or array type, or a non-enum type?
enum_literal
  : ENUM_DIRECTIVE field_reference;

type_field_method_literal
  : reference_type_descriptor
  | ( (reference_type_descriptor ARROW)?
      ( member_name COLON nonvoid_type_descriptor
      | member_name method_prototype
      )
    )
  | PRIMITIVE_TYPE
  | VOID_TYPE;

method_reference
  : (reference_type_descriptor ARROW)? member_name method_prototype;

field_reference
  : (reference_type_descriptor ARROW)? member_name COLON nonvoid_type_descriptor;

label
  : COLON simple_name;

label_ref
  : COLON simple_name;

register_list
  : REGISTER (COMMA REGISTER)*
  | ;

register_range
  : (startreg=REGISTER (DOTDOT endreg=REGISTER)?)?;

verification_error_reference
  : CLASS_DESCRIPTOR | field_reference | method_reference;

catch_directive
  : CATCH_DIRECTIVE nonvoid_type_descriptor OPEN_BRACE from=label_ref DOTDOT to=label_ref CLOSE_BRACE goal=label_ref;

catchall_directive
  : CATCHALL_DIRECTIVE OPEN_BRACE from=label_ref DOTDOT to=label_ref CLOSE_BRACE goal=label_ref;

/*When there are annotations immediately after a parameter definition, we don't know whether they are parameter annotations
or method annotations until we determine if there is an .end parameter directive. In either case, we still "consume" and parse
the annotations. If it turns out that they are parameter annotations, we include them in the I_PARAMETER AST. Otherwise, we
add them to the $statements_and_directives::methodAnnotations list*/
parameter_directive
  : PARAMETER_DIRECTIVE REGISTER (COMMA STRING_LITERAL)?
    ({getInputStream()->LA(1) == ANNOTATION_DIRECTIVE}? annotation)*

    ( END_PARAMETER_DIRECTIVE
    | /*epsilon*/
    );

debug_directive
  : line_directive
  | local_directive
  | end_local_directive
  | restart_local_directive
  | prologue_directive
  | epilogue_directive
  | source_directive;

line_directive
  : LINE_DIRECTIVE integral_literal;

local_directive
  : LOCAL_DIRECTIVE REGISTER (COMMA (NULL_LITERAL | name=STRING_LITERAL) COLON (VOID_TYPE | nonvoid_type_descriptor)
                              (COMMA signature=STRING_LITERAL)? )?;

end_local_directive
  : END_LOCAL_DIRECTIVE REGISTER;

restart_local_directive
  : RESTART_LOCAL_DIRECTIVE REGISTER;

prologue_directive
  : PROLOGUE_DIRECTIVE;

epilogue_directive
  : EPILOGUE_DIRECTIVE;

source_directive
  : SOURCE_DIRECTIVE STRING_LITERAL?;

instruction_format12x
  : INSTRUCTION_FORMAT12x
  | INSTRUCTION_FORMAT12x_OR_ID;

instruction_format22s
  : INSTRUCTION_FORMAT22s
  | INSTRUCTION_FORMAT22s_OR_ID;

instruction_format31i
  : INSTRUCTION_FORMAT31i
  | INSTRUCTION_FORMAT31i_OR_ID;



instruction
  : insn_format10t
  | insn_format10x
  | insn_format10x_odex
  | insn_format11n
  | insn_format11x
  | insn_format12x
  | insn_format20bc
  | insn_format20t
  | insn_format21c_field
  | insn_format21c_field_odex
  | insn_format21c_string
  | insn_format21c_type
  | insn_format21ih
  | insn_format21lh
  | insn_format21s
  | insn_format21t
  | insn_format22b
  | insn_format22c_field
  | insn_format22c_field_odex
  | insn_format22c_type
  | insn_format22cs_field
  | insn_format22s
  | insn_format22t
  | insn_format22x
  | insn_format23x
  | insn_format30t
  | insn_format31c
  | insn_format31i
  | insn_format31t
  | insn_format32x
  | insn_format35c_method
  | insn_format35c_type
  | insn_format35c_method_odex
  | insn_format35mi_method
  | insn_format35ms_method
  | insn_format3rc_method
  | insn_format3rc_method_odex
  | insn_format3rc_type
  | insn_format3rmi_method
  | insn_format3rms_method
  | insn_format45cc_method
  | insn_format4rcc_method
  | insn_format51l
  | insn_array_data_directive
  | insn_packed_switch_directive
  | insn_sparse_switch_directive;

insn_format10t
  : //e.g. goto endloop:
    //e.g. goto +3
    INSTRUCTION_FORMAT10t label_ref;

insn_format10x
  : //e.g. return-void
    INSTRUCTION_FORMAT10x;

insn_format10x_odex
  : //e.g. return-void-barrier
    INSTRUCTION_FORMAT10x_ODEX
    {
    // TODO Odex not valid apk
    };

insn_format11n
  : //e.g. const/4 v0, 5
    INSTRUCTION_FORMAT11n REGISTER COMMA integral_literal;

insn_format11x
  : //e.g. move-result-object v1
    INSTRUCTION_FORMAT11x REGISTER;

insn_format12x
  : //e.g. move v1 v2
    instruction_format12x REGISTER COMMA REGISTER;

insn_format20bc
  : //e.g. throw-verification-error generic-error, Lsome/class;
    INSTRUCTION_FORMAT20bc VERIFICATION_ERROR_TYPE COMMA verification_error_reference
    {
//      if (!allowOdex || opcodes.getOpcodeByName($INSTRUCTION_FORMAT20bc.text) == null || apiLevel >= 14) {
//          TODO odex file
//      }
    };

insn_format20t
  : //e.g. goto/16 endloop:
    INSTRUCTION_FORMAT20t label_ref;

insn_format21c_field
  : //e.g. sget-object v0, java/lang/System/out LJava/io/PrintStream;
    INSTRUCTION_FORMAT21c_FIELD REGISTER COMMA field_reference;

insn_format21c_field_odex
  : //e.g. sget-object-volatile v0, java/lang/System/out LJava/io/PrintStream;
    INSTRUCTION_FORMAT21c_FIELD_ODEX REGISTER COMMA field_reference
    {
//      if (!allowOdex || opcodes.getOpcodeByName($INSTRUCTION_FORMAT21c_FIELD_ODEX.text) == null || apiLevel >= 14) {
//          TODO odex file
//      }
    };

insn_format21c_string
  : //e.g. const-string v1, "Hello World!"
    INSTRUCTION_FORMAT21c_STRING REGISTER COMMA STRING_LITERAL;

insn_format21c_type
  : //e.g. const-class v2, Lorg/jf/HelloWorld2/HelloWorld2;
    INSTRUCTION_FORMAT21c_TYPE REGISTER COMMA nonvoid_type_descriptor;

insn_format21ih
  : //e.g. const/high16 v1, 1234
    INSTRUCTION_FORMAT21ih REGISTER COMMA fixed_32bit_literal;

insn_format21lh
  : //e.g. const-wide/high16 v1, 1234
    INSTRUCTION_FORMAT21lh REGISTER COMMA fixed_32bit_literal;

insn_format21s
  : //e.g. const/16 v1, 1234
    INSTRUCTION_FORMAT21s REGISTER COMMA integral_literal;

insn_format21t
  : //e.g. if-eqz v0, endloop:
    INSTRUCTION_FORMAT21t REGISTER COMMA label_ref;

insn_format22b
  : //e.g. add-int v0, v1, 123
    INSTRUCTION_FORMAT22b REGISTER COMMA REGISTER COMMA integral_literal;

insn_format22c_field
  : //e.g. iput-object v1, v0 org/jf/HelloWorld2/HelloWorld2.helloWorld Ljava/lang/String;
    INSTRUCTION_FORMAT22c_FIELD REGISTER COMMA REGISTER COMMA field_reference;

insn_format22c_field_odex
  : //e.g. iput-object-volatile v1, v0 org/jf/HelloWorld2/HelloWorld2.helloWorld Ljava/lang/String;
    INSTRUCTION_FORMAT22c_FIELD_ODEX REGISTER COMMA REGISTER COMMA field_reference
    {
//      if (!allowOdex || opcodes.getOpcodeByName($INSTRUCTION_FORMAT22c_FIELD_ODEX.text) == null || apiLevel >= 14) {
// TODO not valid apk
//      }
    };

insn_format22c_type
  : //e.g. instance-of v0, v1, Ljava/lang/String;
    INSTRUCTION_FORMAT22c_TYPE REGISTER COMMA REGISTER COMMA nonvoid_type_descriptor;

insn_format22cs_field
  : //e.g. iget-quick v0, v1, field@0xc
    INSTRUCTION_FORMAT22cs_FIELD REGISTER COMMA REGISTER COMMA FIELD_INDEX
    {
// TODO odex
    };

insn_format22s
  : //e.g. add-int/lit16 v0, v1, 12345
    instruction_format22s REGISTER COMMA REGISTER COMMA integral_literal;

insn_format22t
  : //e.g. if-eq v0, v1, endloop:
    INSTRUCTION_FORMAT22t REGISTER COMMA REGISTER COMMA label_ref;

insn_format22x
  : //e.g. move/from16 v1, v1234
    INSTRUCTION_FORMAT22x REGISTER COMMA REGISTER;

insn_format23x
  : //e.g. add-int v1, v2, v3
    INSTRUCTION_FORMAT23x REGISTER COMMA REGISTER COMMA REGISTER;

insn_format30t
  : //e.g. goto/32 endloop:
    INSTRUCTION_FORMAT30t label_ref;

insn_format31c
  : //e.g. const-string/jumbo v1 "Hello World!"
    INSTRUCTION_FORMAT31c REGISTER COMMA STRING_LITERAL;

insn_format31i
  : //e.g. const v0, 123456
    instruction_format31i REGISTER COMMA fixed_32bit_literal;

insn_format31t
  : //e.g. fill-array-data v0, ArrayData:
    INSTRUCTION_FORMAT31t REGISTER COMMA label_ref;

insn_format32x
  : //e.g. move/16 v4567, v1234
    INSTRUCTION_FORMAT32x REGISTER COMMA REGISTER;

insn_format35c_method
  : //e.g. invoke-virtual {v0,v1} java/io/PrintStream/print(Ljava/lang/Stream;)V
    INSTRUCTION_FORMAT35c_METHOD OPEN_BRACE register_list CLOSE_BRACE COMMA method_reference;

insn_format35c_type
  : //e.g. filled-new-array {v0,v1}, I
    INSTRUCTION_FORMAT35c_TYPE OPEN_BRACE register_list CLOSE_BRACE COMMA nonvoid_type_descriptor;

insn_format35c_method_odex
  : //e.g. invoke-direct {p0}, Ljava/lang/Object;-><init>()V
    INSTRUCTION_FORMAT35c_METHOD_ODEX OPEN_BRACE register_list CLOSE_BRACE COMMA method_reference
    {
// TODO odex instruction
    };

insn_format35mi_method
  : //e.g. execute-inline {v0, v1}, inline@0x4
    INSTRUCTION_FORMAT35mi_METHOD OPEN_BRACE register_list CLOSE_BRACE COMMA INLINE_INDEX
    {
// TODO odex instruction
    };

insn_format35ms_method
  : //e.g. invoke-virtual-quick {v0, v1}, vtable@0x4
    INSTRUCTION_FORMAT35ms_METHOD OPEN_BRACE register_list CLOSE_BRACE COMMA VTABLE_INDEX
    {
// TODO odex instruction
    };

insn_format3rc_method
  : //e.g. invoke-virtual/range {v25..v26}, java/lang/StringBuilder/append(Ljava/lang/String;)Ljava/lang/StringBuilder;
    INSTRUCTION_FORMAT3rc_METHOD OPEN_BRACE register_range CLOSE_BRACE COMMA method_reference;

insn_format3rc_method_odex
  : //e.g. invoke-object-init/range {p0}, Ljava/lang/Object;-><init>()V
    INSTRUCTION_FORMAT3rc_METHOD_ODEX OPEN_BRACE register_list CLOSE_BRACE COMMA method_reference
    {
// TODO odex instruction
    };

insn_format3rc_type
  : //e.g. filled-new-array/range {v0..v6}, I
    INSTRUCTION_FORMAT3rc_TYPE OPEN_BRACE register_range CLOSE_BRACE COMMA nonvoid_type_descriptor;

insn_format3rmi_method
  : //e.g. execute-inline/range {v0 .. v10}, inline@0x14
    INSTRUCTION_FORMAT3rmi_METHOD OPEN_BRACE register_range CLOSE_BRACE COMMA INLINE_INDEX
    {
// TODO odex instruction
    };

insn_format3rms_method
  : //e.g. invoke-virtual-quick/range {v0 .. v10}, vtable@0x14
    INSTRUCTION_FORMAT3rms_METHOD OPEN_BRACE register_range CLOSE_BRACE COMMA VTABLE_INDEX
    {
// TODO odex instruction
    };

insn_format45cc_method
  : //e.g. invoke-polymorphic {v0..v1}, java/lang/invoke/MethodHandle;->invoke([Ljava/lang/Object;)Ljava/lang/Object;, (I)J
    INSTRUCTION_FORMAT45cc_METHOD OPEN_BRACE register_list CLOSE_BRACE COMMA method_reference COMMA method_prototype;

insn_format4rcc_method
  : //e.g. invoke-polymorphic/range {v0,v1}, java/lang/invoke/MethodHandle;->invoke([Ljava/lang/Object;)Ljava/lang/Object;, (I)J
    INSTRUCTION_FORMAT4rcc_METHOD OPEN_BRACE register_range CLOSE_BRACE COMMA method_reference COMMA method_prototype;

insn_format51l
  : //e.g. const-wide v0, 5000000000L
    INSTRUCTION_FORMAT51l REGISTER COMMA fixed_literal;

insn_array_data_directive
  : ARRAY_DATA_DIRECTIVE
    parsed_integer_literal
    {
        int elementWidth = $parsed_integer_literal.value;
        if (elementWidth != 4 && elementWidth != 8 && elementWidth != 1 && elementWidth != 2) {
// TODO array length not valid
        }
    }
    fixed_literal* END_ARRAY_DATA_DIRECTIVE;

insn_packed_switch_directive
    :   PACKED_SWITCH_DIRECTIVE
    fixed_32bit_literal
    label_ref*
    END_PACKED_SWITCH_DIRECTIVE;

insn_sparse_switch_directive
  :   SPARSE_SWITCH_DIRECTIVE
    (fixed_32bit_literal ARROW label_ref)*
    END_SPARSE_SWITCH_DIRECTIVE;
