// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

/**
 ** \file SmaliParser.hpp
 ** Define the  Analysis ::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

#ifndef YY_YY_SMALIPARSER_HPP_INCLUDED
# define YY_YY_SMALIPARSER_HPP_INCLUDED
// //                    "%code requires" blocks.
#line 11 "SmaliParser.yy" // lalr1.cc:377

//===- Parser.yy - ART-Parser ---------------------------------*- bison -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// The file defines a Parser for smali language. Please use
// bison -o SmaliParser.cpp SmaliParser.yy
// to generate parser source file
// or
// bison -v -o SmaliParser.cpp SmaliParser.yy
// to debug.
//===----------------------------------------------------------------------===//
    #include <iostream>
    #include <string>
    #include <vector>
    #include <stdint.h>
    #include "Ops/Ops.h"

    namespace Analysis {
        class SmaliLexer;
        class Interpreter;
    }

#line 73 "SmaliParser.hpp" // lalr1.cc:377

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>
# include "stack.hh"
# include "location.hh"
#include <typeinfo>
#ifndef YYASSERT
# include <cassert>
# define YYASSERT assert
#endif


#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

#line 9 "SmaliParser.yy" // lalr1.cc:377
namespace  Analysis  {
#line 150 "SmaliParser.hpp" // lalr1.cc:377



  /// A char[S] buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current state.
  template <size_t S>
  struct variant
  {
    /// Type of *this.
    typedef variant<S> self_type;

    /// Empty construction.
    variant ()
      : yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    variant (const T& t)
      : yytypeid_ (&typeid (T))
    {
      YYASSERT (sizeof (T) <= S);
      new (yyas_<T> ()) T (t);
    }

    /// Destruction, allowed only if empty.
    ~variant ()
    {
      YYASSERT (!yytypeid_);
    }

    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    build ()
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T;
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    build (const T& t)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as ()
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Swap the content with \a other, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsability.
    /// Swapping between built and (possibly) non-built is done with
    /// variant::move ().
    template <typename T>
    void
    swap (self_type& other)
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == *other.yytypeid_);
      std::swap (as<T> (), other.as<T> ());
    }

    /// Move the content of \a other to this.
    ///
    /// Destroys \a other.
    template <typename T>
    void
    move (self_type& other)
    {
      build<T> ();
      swap<T> (other);
      other.destroy<T> ();
    }

    /// Copy the content of \a other to this.
    template <typename T>
    void
    copy (const self_type& other)
    {
      build<T> (other.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
    /// Prohibit blind copies.
    self_type& operator=(const self_type&);
    variant (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ ()
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[S];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };


  /// A Bison parser.
  class  SmaliParser 
  {
  public:
#ifndef YYSTYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // "true|false"
      // "flag"
      // "v(p)x"
      char dummy1[sizeof(int)];

      // "lex error"
      // "Integer"
      // "- Integer"
      // "- Integer L"
      // "- Integer S"
      // "- Integer T"
      // "FloatOrID F"
      // "FloatOrID D"
      // "Float F"
      // "Float D"
      // "ZBSCIJFDLIT"
      // "ZBSCIJFD"
      // "Lxxx;"
      // "[["
      // "simple name"
      // "member name"
      // "string"
      // "char"
      // "build runtime system"
      // "ver type error"
      // "inline@0x"
      // "vtable@0x"
      // "field@0x"
      // "#xxx"
      char dummy2[sizeof(std::string)];
};

    /// Symbol semantic values.
    typedef variant<sizeof(union_type)> semantic_type;
#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m);
      location_type location;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        TOKEN_END = 0,
        TOKEN_EOL = 258,
        TOKEN_ERROR = 259,
        TOKEN_KEYWORD_BEGIN = 260,
        TOKEN_CLASS_DIRECTIVE = 261,
        TOKEN_SUPER_DIRECTIVE = 262,
        TOKEN_IMPLEMENTS_DIRECTIVE = 263,
        TOKEN_SOURCE_DIRECTIVE = 264,
        TOKEN_FIELD_DIRECTIVE = 265,
        TOKEN_END_FIELD_DIRECTIVE = 266,
        TOKEN_SUBANNOTATION_DIRECTIVE = 267,
        TOKEN_END_SUBANNOTATION_DIRECTIVE = 268,
        TOKEN_ANNOTATION_DIRECTIVE = 269,
        TOKEN_END_ANNOTATION_DIRECTIVE = 270,
        TOKEN_ENUM_DIRECTIVE = 271,
        TOKEN_METHOD_DIRECTIVE = 272,
        TOKEN_END_METHOD_DIRECTIVE = 273,
        TOKEN_REGISTERS_DIRECTIVE = 274,
        TOKEN_LOCALS_DIRECTIVE = 275,
        TOKEN_ARRAY_DATA_DIRECTIVE = 276,
        TOKEN_END_ARRAY_DATA_DIRECTIVE = 277,
        TOKEN_PACKED_SWITCH_DIRECTIVE = 278,
        TOKEN_END_PACKED_SWITCH_DIRECTIVE = 279,
        TOKEN_SPARSE_SWITCH_DIRECTIVE = 280,
        TOKEN_END_SPARSE_SWITCH_DIRECTIVE = 281,
        TOKEN_CATCH_DIRECTIVE = 282,
        TOKEN_CATCHALL_DIRECTIVE = 283,
        TOKEN_LINE_DIRECTIVE = 284,
        TOKEN_PARAMETER_DIRECTIVE = 285,
        TOKEN_END_PARAMETER_DIRECTIVE = 286,
        TOKEN_LOCAL_DIRECTIVE = 287,
        TOKEN_END_LOCAL_DIRECTIVE = 288,
        TOKEN_RESTART_LOCAL_DIRECTIVE = 289,
        TOKEN_PROLOGUE_DIRECTIVE = 290,
        TOKEN_EPILOGUE_DIRECTIVE = 291,
        TOKEN_KEYWORD_END = 292,
        TOKEN_NUMBER_BEGIN = 293,
        TOKEN_POSITIVE_INTEGER_LITERAL = 294,
        TOKEN_NEGATIVE_INTEGER_LITERAL = 295,
        TOKEN_LONG_LITERAL = 296,
        TOKEN_SHORT_LITERAL = 297,
        TOKEN_BYTE_LITERAL = 298,
        TOKEN_FLOAT_LITERAL_OR_ID = 299,
        TOKEN_DOUBLE_LITERAL_OR_ID = 300,
        TOKEN_FLOAT_LITERAL = 301,
        TOKEN_DOUBLE_LITERAL = 302,
        TOKEN_BOOL_LITERAL = 303,
        TOKEN_NULL_LITERAL = 304,
        TOKEN_NUMBER_END = 305,
        TOKEN_FLAG = 306,
        TOKEN_REGISTER = 307,
        TOKEN_PARAM_LIST_OR_ID_PRIMITIVE_TYPE = 308,
        TOKEN_PRIMITIVE_TYPE = 309,
        TOKEN_CLASS_DESCRIPTOR = 310,
        TOKEN_ARRAY_TYPE_PREFIX = 311,
        TOKEN_VOID_TYPE = 312,
        TOKEN_SIMPLE_NAME = 313,
        TOKEN_MEMBER_NAME = 314,
        TOKEN_STRING_LITERAL = 315,
        TOKEN_CHAR_LITERAL = 316,
        TOKEN_ANNOTATION_VISIBILITY = 317,
        TOKEN_VERIFICATION_ERROR_TYPE = 318,
        TOKEN_INLINE_INDEX = 319,
        TOKEN_VTABLE_INDEX = 320,
        TOKEN_FIELD_OFFSET = 321,
        TOKEN_LINE_COMMENT = 322,
        TOKEN_OP_BEGIN = 323,
        TOKEN_OP_NOP = 324,
        TOKEN_OP_MOVE = 325,
        TOKEN_OP_MOVE_FROM16 = 326,
        TOKEN_OP_MOVE_16 = 327,
        TOKEN_OP_MOVE_WIDE = 328,
        TOKEN_OP_MOVE_WIDE_FROM16 = 329,
        TOKEN_OP_MOVE_WIDE_16 = 330,
        TOKEN_OP_MOVE_OBJECT = 331,
        TOKEN_OP_MOVE_OBJECT_FROM16 = 332,
        TOKEN_OP_MOVE_OBJECT_16 = 333,
        TOKEN_OP_MOVE_RESULT = 334,
        TOKEN_OP_MOVE_RESULT_WIDE = 335,
        TOKEN_OP_MOVE_RESULT_OBJECT = 336,
        TOKEN_OP_MOVE_EXCEPTION = 337,
        TOKEN_OP_RETURN_VOID = 338,
        TOKEN_OP_RETURN = 339,
        TOKEN_OP_RETURN_WIDE = 340,
        TOKEN_OP_RETURN_OBJECT = 341,
        TOKEN_OP_CONST_4 = 342,
        TOKEN_OP_CONST_16 = 343,
        TOKEN_OP_CONST = 344,
        TOKEN_OP_CONST_HIGH16 = 345,
        TOKEN_OP_CONST_WIDE_16 = 346,
        TOKEN_OP_CONST_WIDE_32 = 347,
        TOKEN_OP_CONST_WIDE = 348,
        TOKEN_OP_CONST_WIDE_HIGH16 = 349,
        TOKEN_OP_CONST_STRING = 350,
        TOKEN_OP_CONST_STRING_JUMBO = 351,
        TOKEN_OP_CONST_CLASS = 352,
        TOKEN_OP_MONITOR_ENTER = 353,
        TOKEN_OP_MONITOR_EXIT = 354,
        TOKEN_OP_CHECK_CAST = 355,
        TOKEN_OP_INSTANCE_OF = 356,
        TOKEN_OP_ARRAY_LENGTH = 357,
        TOKEN_OP_NEW_INSTANCE = 358,
        TOKEN_OP_NEW_ARRAY = 359,
        TOKEN_OP_FILLED_NEW_ARRAY = 360,
        TOKEN_OP_FILLED_NEW_ARRAY_RANGE = 361,
        TOKEN_OP_FILL_ARRAY_DATA = 362,
        TOKEN_OP_THROW = 363,
        TOKEN_OP_GOTO = 364,
        TOKEN_OP_GOTO_16 = 365,
        TOKEN_OP_GOTO_32 = 366,
        TOKEN_OP_PACKED_SWITCH = 367,
        TOKEN_OP_SPARSE_SWITCH = 368,
        TOKEN_OP_CMPL_FLOAT = 369,
        TOKEN_OP_CMPG_FLOAT = 370,
        TOKEN_OP_CMPL_DOUBLE = 371,
        TOKEN_OP_CMPG_DOUBLE = 372,
        TOKEN_OP_CMP_LONG = 373,
        TOKEN_OP_IF_EQ = 374,
        TOKEN_OP_IF_NE = 375,
        TOKEN_OP_IF_LT = 376,
        TOKEN_OP_IF_GE = 377,
        TOKEN_OP_IF_GT = 378,
        TOKEN_OP_IF_LE = 379,
        TOKEN_OP_IF_EQZ = 380,
        TOKEN_OP_IF_NEZ = 381,
        TOKEN_OP_IF_LTZ = 382,
        TOKEN_OP_IF_GEZ = 383,
        TOKEN_OP_IF_GTZ = 384,
        TOKEN_OP_IF_LEZ = 385,
        TOKEN_OP_UNUSED_3E = 386,
        TOKEN_OP_UNUSED_3F = 387,
        TOKEN_OP_UNUSED_40 = 388,
        TOKEN_OP_UNUSED_41 = 389,
        TOKEN_OP_UNUSED_42 = 390,
        TOKEN_OP_UNUSED_43 = 391,
        TOKEN_OP_AGET = 392,
        TOKEN_OP_AGET_WIDE = 393,
        TOKEN_OP_AGET_OBJECT = 394,
        TOKEN_OP_AGET_BOOLEAN = 395,
        TOKEN_OP_AGET_BYTE = 396,
        TOKEN_OP_AGET_CHAR = 397,
        TOKEN_OP_AGET_SHORT = 398,
        TOKEN_OP_APUT = 399,
        TOKEN_OP_APUT_WIDE = 400,
        TOKEN_OP_APUT_OBJECT = 401,
        TOKEN_OP_APUT_BOOLEAN = 402,
        TOKEN_OP_APUT_BYTE = 403,
        TOKEN_OP_APUT_CHAR = 404,
        TOKEN_OP_APUT_SHORT = 405,
        TOKEN_OP_IGET = 406,
        TOKEN_OP_IGET_WIDE = 407,
        TOKEN_OP_IGET_OBJECT = 408,
        TOKEN_OP_IGET_BOOLEAN = 409,
        TOKEN_OP_IGET_BYTE = 410,
        TOKEN_OP_IGET_CHAR = 411,
        TOKEN_OP_IGET_SHORT = 412,
        TOKEN_OP_IPUT = 413,
        TOKEN_OP_IPUT_WIDE = 414,
        TOKEN_OP_IPUT_OBJECT = 415,
        TOKEN_OP_IPUT_BOOLEAN = 416,
        TOKEN_OP_IPUT_BYTE = 417,
        TOKEN_OP_IPUT_CHAR = 418,
        TOKEN_OP_IPUT_SHORT = 419,
        TOKEN_OP_SGET = 420,
        TOKEN_OP_SGET_WIDE = 421,
        TOKEN_OP_SGET_OBJECT = 422,
        TOKEN_OP_SGET_BOOLEAN = 423,
        TOKEN_OP_SGET_BYTE = 424,
        TOKEN_OP_SGET_CHAR = 425,
        TOKEN_OP_SGET_SHORT = 426,
        TOKEN_OP_SPUT = 427,
        TOKEN_OP_SPUT_WIDE = 428,
        TOKEN_OP_SPUT_OBJECT = 429,
        TOKEN_OP_SPUT_BOOLEAN = 430,
        TOKEN_OP_SPUT_BYTE = 431,
        TOKEN_OP_SPUT_CHAR = 432,
        TOKEN_OP_SPUT_SHORT = 433,
        TOKEN_OP_INVOKE_VIRTUAL = 434,
        TOKEN_OP_INVOKE_SUPER = 435,
        TOKEN_OP_INVOKE_DIRECT = 436,
        TOKEN_OP_INVOKE_STATIC = 437,
        TOKEN_OP_INVOKE_INTERFACE = 438,
        TOKEN_OP_UNUSED_73 = 439,
        TOKEN_OP_INVOKE_VIRTUAL_RANGE = 440,
        TOKEN_OP_INVOKE_SUPER_RANGE = 441,
        TOKEN_OP_INVOKE_DIRECT_RANGE = 442,
        TOKEN_OP_INVOKE_STATIC_RANGE = 443,
        TOKEN_OP_INVOKE_INTERFACE_RANGE = 444,
        TOKEN_OP_UNUSED_79 = 445,
        TOKEN_OP_UNUSED_7A = 446,
        TOKEN_OP_NEG_INT = 447,
        TOKEN_OP_NOT_INT = 448,
        TOKEN_OP_NEG_LONG = 449,
        TOKEN_OP_NOT_LONG = 450,
        TOKEN_OP_NEG_FLOAT = 451,
        TOKEN_OP_NEG_DOUBLE = 452,
        TOKEN_OP_INT_TO_LONG = 453,
        TOKEN_OP_INT_TO_FLOAT = 454,
        TOKEN_OP_INT_TO_DOUBLE = 455,
        TOKEN_OP_LONG_TO_INT = 456,
        TOKEN_OP_LONG_TO_FLOAT = 457,
        TOKEN_OP_LONG_TO_DOUBLE = 458,
        TOKEN_OP_FLOAT_TO_INT = 459,
        TOKEN_OP_FLOAT_TO_LONG = 460,
        TOKEN_OP_FLOAT_TO_DOUBLE = 461,
        TOKEN_OP_DOUBLE_TO_INT = 462,
        TOKEN_OP_DOUBLE_TO_LONG = 463,
        TOKEN_OP_DOUBLE_TO_FLOAT = 464,
        TOKEN_OP_INT_TO_BYTE = 465,
        TOKEN_OP_INT_TO_CHAR = 466,
        TOKEN_OP_INT_TO_SHORT = 467,
        TOKEN_OP_ADD_INT = 468,
        TOKEN_OP_SUB_INT = 469,
        TOKEN_OP_MUL_INT = 470,
        TOKEN_OP_DIV_INT = 471,
        TOKEN_OP_REM_INT = 472,
        TOKEN_OP_AND_INT = 473,
        TOKEN_OP_OR_INT = 474,
        TOKEN_OP_XOR_INT = 475,
        TOKEN_OP_SHL_INT = 476,
        TOKEN_OP_SHR_INT = 477,
        TOKEN_OP_USHR_INT = 478,
        TOKEN_OP_ADD_LONG = 479,
        TOKEN_OP_SUB_LONG = 480,
        TOKEN_OP_MUL_LONG = 481,
        TOKEN_OP_DIV_LONG = 482,
        TOKEN_OP_REM_LONG = 483,
        TOKEN_OP_AND_LONG = 484,
        TOKEN_OP_OR_LONG = 485,
        TOKEN_OP_XOR_LONG = 486,
        TOKEN_OP_SHL_LONG = 487,
        TOKEN_OP_SHR_LONG = 488,
        TOKEN_OP_USHR_LONG = 489,
        TOKEN_OP_ADD_FLOAT = 490,
        TOKEN_OP_SUB_FLOAT = 491,
        TOKEN_OP_MUL_FLOAT = 492,
        TOKEN_OP_DIV_FLOAT = 493,
        TOKEN_OP_REM_FLOAT = 494,
        TOKEN_OP_ADD_DOUBLE = 495,
        TOKEN_OP_SUB_DOUBLE = 496,
        TOKEN_OP_MUL_DOUBLE = 497,
        TOKEN_OP_DIV_DOUBLE = 498,
        TOKEN_OP_REM_DOUBLE = 499,
        TOKEN_OP_ADD_INT_2ADDR = 500,
        TOKEN_OP_SUB_INT_2ADDR = 501,
        TOKEN_OP_MUL_INT_2ADDR = 502,
        TOKEN_OP_DIV_INT_2ADDR = 503,
        TOKEN_OP_REM_INT_2ADDR = 504,
        TOKEN_OP_AND_INT_2ADDR = 505,
        TOKEN_OP_OR_INT_2ADDR = 506,
        TOKEN_OP_XOR_INT_2ADDR = 507,
        TOKEN_OP_SHL_INT_2ADDR = 508,
        TOKEN_OP_SHR_INT_2ADDR = 509,
        TOKEN_OP_USHR_INT_2ADDR = 510,
        TOKEN_OP_ADD_LONG_2ADDR = 511,
        TOKEN_OP_SUB_LONG_2ADDR = 512,
        TOKEN_OP_MUL_LONG_2ADDR = 513,
        TOKEN_OP_DIV_LONG_2ADDR = 514,
        TOKEN_OP_REM_LONG_2ADDR = 515,
        TOKEN_OP_AND_LONG_2ADDR = 516,
        TOKEN_OP_OR_LONG_2ADDR = 517,
        TOKEN_OP_XOR_LONG_2ADDR = 518,
        TOKEN_OP_SHL_LONG_2ADDR = 519,
        TOKEN_OP_SHR_LONG_2ADDR = 520,
        TOKEN_OP_USHR_LONG_2ADDR = 521,
        TOKEN_OP_ADD_FLOAT_2ADDR = 522,
        TOKEN_OP_SUB_FLOAT_2ADDR = 523,
        TOKEN_OP_MUL_FLOAT_2ADDR = 524,
        TOKEN_OP_DIV_FLOAT_2ADDR = 525,
        TOKEN_OP_REM_FLOAT_2ADDR = 526,
        TOKEN_OP_ADD_DOUBLE_2ADDR = 527,
        TOKEN_OP_SUB_DOUBLE_2ADDR = 528,
        TOKEN_OP_MUL_DOUBLE_2ADDR = 529,
        TOKEN_OP_DIV_DOUBLE_2ADDR = 530,
        TOKEN_OP_REM_DOUBLE_2ADDR = 531,
        TOKEN_OP_ADD_INT_LIT16 = 532,
        TOKEN_OP_RSUB_INT = 533,
        TOKEN_OP_MUL_INT_LIT16 = 534,
        TOKEN_OP_DIV_INT_LIT16 = 535,
        TOKEN_OP_REM_INT_LIT16 = 536,
        TOKEN_OP_AND_INT_LIT16 = 537,
        TOKEN_OP_OR_INT_LIT16 = 538,
        TOKEN_OP_XOR_INT_LIT16 = 539,
        TOKEN_OP_ADD_INT_LIT8 = 540,
        TOKEN_OP_RSUB_INT_LIT8 = 541,
        TOKEN_OP_MUL_INT_LIT8 = 542,
        TOKEN_OP_DIV_INT_LIT8 = 543,
        TOKEN_OP_REM_INT_LIT8 = 544,
        TOKEN_OP_AND_INT_LIT8 = 545,
        TOKEN_OP_OR_INT_LIT8 = 546,
        TOKEN_OP_XOR_INT_LIT8 = 547,
        TOKEN_OP_SHL_INT_LIT8 = 548,
        TOKEN_OP_SHR_INT_LIT8 = 549,
        TOKEN_OP_USHR_INT_LIT8 = 550,
        TOKEN_OP_IGET_VOLATILE = 551,
        TOKEN_OP_IPUT_VOLATILE = 552,
        TOKEN_OP_SGET_VOLATILE = 553,
        TOKEN_OP_SPUT_VOLATILE = 554,
        TOKEN_OP_IGET_OBJECT_VOLATILE = 555,
        TOKEN_OP_IGET_WIDE_VOLATILE = 556,
        TOKEN_OP_IPUT_WIDE_VOLATILE = 557,
        TOKEN_OP_SGET_WIDE_VOLATILE = 558,
        TOKEN_OP_SPUT_WIDE_VOLATILE = 559,
        TOKEN_OP_BREAKPOINT = 560,
        TOKEN_OP_THROW_VERIFICATION_ERROR = 561,
        TOKEN_OP_EXECUTE_INLINE = 562,
        TOKEN_OP_EXECUTE_INLINE_RANGE = 563,
        TOKEN_OP_INVOKE_OBJECT_INIT_RANGE = 564,
        TOKEN_OP_RETURN_VOID_BARRIER = 565,
        TOKEN_OP_IGET_QUICK = 566,
        TOKEN_OP_IGET_WIDE_QUICK = 567,
        TOKEN_OP_IGET_OBJECT_QUICK = 568,
        TOKEN_OP_IPUT_QUICK = 569,
        TOKEN_OP_IPUT_WIDE_QUICK = 570,
        TOKEN_OP_IPUT_OBJECT_QUICK = 571,
        TOKEN_OP_INVOKE_VIRTUAL_QUICK = 572,
        TOKEN_OP_INVOKE_VIRTUAL_QUICK_RANGE = 573,
        TOKEN_OP_INVOKE_SUPER_QUICK = 574,
        TOKEN_OP_INVOKE_SUPER_QUICK_RANGE = 575,
        TOKEN_OP_IPUT_OBJECT_VOLATILE = 576,
        TOKEN_OP_SGET_OBJECT_VOLATILE = 577,
        TOKEN_OP_SPUT_OBJECT_VOLATILE = 578,
        TOKEN_OP_UNUSED_FF = 579,
        TOKEN_OP_END = 580,
        TOKEN_SYMBOL_BEGIN = 581,
        TOKEN_DOTDOT = 582,
        TOKEN_ARROW = 583,
        TOKEN_EQUAL = 584,
        TOKEN_COLON = 585,
        TOKEN_COMMA = 586,
        TOKEN_OPEN_BRACE = 587,
        TOKEN_CLOSE_BRACE = 588,
        TOKEN_OPEN_PAREN = 589,
        TOKEN_CLOSE_PAREN = 590,
        TOKEN_SYMBOL_END = 591
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned short int token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Copy constructor.
      basic_symbol (const basic_symbol& other);

      /// Constructor for valueless symbols, and symbols from each type.

  basic_symbol (typename Base::kind_type t, const location_type& l);

  basic_symbol (typename Base::kind_type t, const int v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l);


      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    const semantic_type& v,
                    const location_type& l);

      /// Destroy the symbol.
      ~basic_symbol ();

      /// Destroy contents, and record that is empty.
      void clear ();

      /// Whether empty.
      bool empty () const;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

      /// Copy constructor.
      by_type (const by_type& other);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const;

      /// The token.
      token_type token () const;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    typedef basic_symbol<by_type> symbol_type;

    // Symbol constructors declarations.
    static inline
    symbol_type
    make_END (const location_type& l);

    static inline
    symbol_type
    make_EOL (const location_type& l);

    static inline
    symbol_type
    make_ERROR (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_KEYWORD_BEGIN (const location_type& l);

    static inline
    symbol_type
    make_CLASS_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_SUPER_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_IMPLEMENTS_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_SOURCE_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_FIELD_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_END_FIELD_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_SUBANNOTATION_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_END_SUBANNOTATION_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_ANNOTATION_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_END_ANNOTATION_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_ENUM_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_METHOD_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_END_METHOD_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_REGISTERS_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_LOCALS_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_ARRAY_DATA_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_END_ARRAY_DATA_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_PACKED_SWITCH_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_END_PACKED_SWITCH_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_SPARSE_SWITCH_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_END_SPARSE_SWITCH_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_CATCH_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_CATCHALL_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_LINE_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_PARAMETER_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_END_PARAMETER_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_LOCAL_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_END_LOCAL_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_RESTART_LOCAL_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_PROLOGUE_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_EPILOGUE_DIRECTIVE (const location_type& l);

    static inline
    symbol_type
    make_KEYWORD_END (const location_type& l);

    static inline
    symbol_type
    make_NUMBER_BEGIN (const location_type& l);

    static inline
    symbol_type
    make_POSITIVE_INTEGER_LITERAL (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_NEGATIVE_INTEGER_LITERAL (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_LONG_LITERAL (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_SHORT_LITERAL (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_BYTE_LITERAL (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_FLOAT_LITERAL_OR_ID (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_DOUBLE_LITERAL_OR_ID (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_FLOAT_LITERAL (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_DOUBLE_LITERAL (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_BOOL_LITERAL (const int& v, const location_type& l);

    static inline
    symbol_type
    make_NULL_LITERAL (const location_type& l);

    static inline
    symbol_type
    make_NUMBER_END (const location_type& l);

    static inline
    symbol_type
    make_FLAG (const int& v, const location_type& l);

    static inline
    symbol_type
    make_REGISTER (const int& v, const location_type& l);

    static inline
    symbol_type
    make_PARAM_LIST_OR_ID_PRIMITIVE_TYPE (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_PRIMITIVE_TYPE (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_CLASS_DESCRIPTOR (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_ARRAY_TYPE_PREFIX (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_VOID_TYPE (const location_type& l);

    static inline
    symbol_type
    make_SIMPLE_NAME (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_MEMBER_NAME (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_STRING_LITERAL (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_CHAR_LITERAL (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_ANNOTATION_VISIBILITY (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_VERIFICATION_ERROR_TYPE (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_INLINE_INDEX (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_VTABLE_INDEX (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_FIELD_OFFSET (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_LINE_COMMENT (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_OP_BEGIN (const location_type& l);

    static inline
    symbol_type
    make_OP_NOP (const location_type& l);

    static inline
    symbol_type
    make_OP_MOVE (const location_type& l);

    static inline
    symbol_type
    make_OP_MOVE_FROM16 (const location_type& l);

    static inline
    symbol_type
    make_OP_MOVE_16 (const location_type& l);

    static inline
    symbol_type
    make_OP_MOVE_WIDE (const location_type& l);

    static inline
    symbol_type
    make_OP_MOVE_WIDE_FROM16 (const location_type& l);

    static inline
    symbol_type
    make_OP_MOVE_WIDE_16 (const location_type& l);

    static inline
    symbol_type
    make_OP_MOVE_OBJECT (const location_type& l);

    static inline
    symbol_type
    make_OP_MOVE_OBJECT_FROM16 (const location_type& l);

    static inline
    symbol_type
    make_OP_MOVE_OBJECT_16 (const location_type& l);

    static inline
    symbol_type
    make_OP_MOVE_RESULT (const location_type& l);

    static inline
    symbol_type
    make_OP_MOVE_RESULT_WIDE (const location_type& l);

    static inline
    symbol_type
    make_OP_MOVE_RESULT_OBJECT (const location_type& l);

    static inline
    symbol_type
    make_OP_MOVE_EXCEPTION (const location_type& l);

    static inline
    symbol_type
    make_OP_RETURN_VOID (const location_type& l);

    static inline
    symbol_type
    make_OP_RETURN (const location_type& l);

    static inline
    symbol_type
    make_OP_RETURN_WIDE (const location_type& l);

    static inline
    symbol_type
    make_OP_RETURN_OBJECT (const location_type& l);

    static inline
    symbol_type
    make_OP_CONST_4 (const location_type& l);

    static inline
    symbol_type
    make_OP_CONST_16 (const location_type& l);

    static inline
    symbol_type
    make_OP_CONST (const location_type& l);

    static inline
    symbol_type
    make_OP_CONST_HIGH16 (const location_type& l);

    static inline
    symbol_type
    make_OP_CONST_WIDE_16 (const location_type& l);

    static inline
    symbol_type
    make_OP_CONST_WIDE_32 (const location_type& l);

    static inline
    symbol_type
    make_OP_CONST_WIDE (const location_type& l);

    static inline
    symbol_type
    make_OP_CONST_WIDE_HIGH16 (const location_type& l);

    static inline
    symbol_type
    make_OP_CONST_STRING (const location_type& l);

    static inline
    symbol_type
    make_OP_CONST_STRING_JUMBO (const location_type& l);

    static inline
    symbol_type
    make_OP_CONST_CLASS (const location_type& l);

    static inline
    symbol_type
    make_OP_MONITOR_ENTER (const location_type& l);

    static inline
    symbol_type
    make_OP_MONITOR_EXIT (const location_type& l);

    static inline
    symbol_type
    make_OP_CHECK_CAST (const location_type& l);

    static inline
    symbol_type
    make_OP_INSTANCE_OF (const location_type& l);

    static inline
    symbol_type
    make_OP_ARRAY_LENGTH (const location_type& l);

    static inline
    symbol_type
    make_OP_NEW_INSTANCE (const location_type& l);

    static inline
    symbol_type
    make_OP_NEW_ARRAY (const location_type& l);

    static inline
    symbol_type
    make_OP_FILLED_NEW_ARRAY (const location_type& l);

    static inline
    symbol_type
    make_OP_FILLED_NEW_ARRAY_RANGE (const location_type& l);

    static inline
    symbol_type
    make_OP_FILL_ARRAY_DATA (const location_type& l);

    static inline
    symbol_type
    make_OP_THROW (const location_type& l);

    static inline
    symbol_type
    make_OP_GOTO (const location_type& l);

    static inline
    symbol_type
    make_OP_GOTO_16 (const location_type& l);

    static inline
    symbol_type
    make_OP_GOTO_32 (const location_type& l);

    static inline
    symbol_type
    make_OP_PACKED_SWITCH (const location_type& l);

    static inline
    symbol_type
    make_OP_SPARSE_SWITCH (const location_type& l);

    static inline
    symbol_type
    make_OP_CMPL_FLOAT (const location_type& l);

    static inline
    symbol_type
    make_OP_CMPG_FLOAT (const location_type& l);

    static inline
    symbol_type
    make_OP_CMPL_DOUBLE (const location_type& l);

    static inline
    symbol_type
    make_OP_CMPG_DOUBLE (const location_type& l);

    static inline
    symbol_type
    make_OP_CMP_LONG (const location_type& l);

    static inline
    symbol_type
    make_OP_IF_EQ (const location_type& l);

    static inline
    symbol_type
    make_OP_IF_NE (const location_type& l);

    static inline
    symbol_type
    make_OP_IF_LT (const location_type& l);

    static inline
    symbol_type
    make_OP_IF_GE (const location_type& l);

    static inline
    symbol_type
    make_OP_IF_GT (const location_type& l);

    static inline
    symbol_type
    make_OP_IF_LE (const location_type& l);

    static inline
    symbol_type
    make_OP_IF_EQZ (const location_type& l);

    static inline
    symbol_type
    make_OP_IF_NEZ (const location_type& l);

    static inline
    symbol_type
    make_OP_IF_LTZ (const location_type& l);

    static inline
    symbol_type
    make_OP_IF_GEZ (const location_type& l);

    static inline
    symbol_type
    make_OP_IF_GTZ (const location_type& l);

    static inline
    symbol_type
    make_OP_IF_LEZ (const location_type& l);

    static inline
    symbol_type
    make_OP_UNUSED_3E (const location_type& l);

    static inline
    symbol_type
    make_OP_UNUSED_3F (const location_type& l);

    static inline
    symbol_type
    make_OP_UNUSED_40 (const location_type& l);

    static inline
    symbol_type
    make_OP_UNUSED_41 (const location_type& l);

    static inline
    symbol_type
    make_OP_UNUSED_42 (const location_type& l);

    static inline
    symbol_type
    make_OP_UNUSED_43 (const location_type& l);

    static inline
    symbol_type
    make_OP_AGET (const location_type& l);

    static inline
    symbol_type
    make_OP_AGET_WIDE (const location_type& l);

    static inline
    symbol_type
    make_OP_AGET_OBJECT (const location_type& l);

    static inline
    symbol_type
    make_OP_AGET_BOOLEAN (const location_type& l);

    static inline
    symbol_type
    make_OP_AGET_BYTE (const location_type& l);

    static inline
    symbol_type
    make_OP_AGET_CHAR (const location_type& l);

    static inline
    symbol_type
    make_OP_AGET_SHORT (const location_type& l);

    static inline
    symbol_type
    make_OP_APUT (const location_type& l);

    static inline
    symbol_type
    make_OP_APUT_WIDE (const location_type& l);

    static inline
    symbol_type
    make_OP_APUT_OBJECT (const location_type& l);

    static inline
    symbol_type
    make_OP_APUT_BOOLEAN (const location_type& l);

    static inline
    symbol_type
    make_OP_APUT_BYTE (const location_type& l);

    static inline
    symbol_type
    make_OP_APUT_CHAR (const location_type& l);

    static inline
    symbol_type
    make_OP_APUT_SHORT (const location_type& l);

    static inline
    symbol_type
    make_OP_IGET (const location_type& l);

    static inline
    symbol_type
    make_OP_IGET_WIDE (const location_type& l);

    static inline
    symbol_type
    make_OP_IGET_OBJECT (const location_type& l);

    static inline
    symbol_type
    make_OP_IGET_BOOLEAN (const location_type& l);

    static inline
    symbol_type
    make_OP_IGET_BYTE (const location_type& l);

    static inline
    symbol_type
    make_OP_IGET_CHAR (const location_type& l);

    static inline
    symbol_type
    make_OP_IGET_SHORT (const location_type& l);

    static inline
    symbol_type
    make_OP_IPUT (const location_type& l);

    static inline
    symbol_type
    make_OP_IPUT_WIDE (const location_type& l);

    static inline
    symbol_type
    make_OP_IPUT_OBJECT (const location_type& l);

    static inline
    symbol_type
    make_OP_IPUT_BOOLEAN (const location_type& l);

    static inline
    symbol_type
    make_OP_IPUT_BYTE (const location_type& l);

    static inline
    symbol_type
    make_OP_IPUT_CHAR (const location_type& l);

    static inline
    symbol_type
    make_OP_IPUT_SHORT (const location_type& l);

    static inline
    symbol_type
    make_OP_SGET (const location_type& l);

    static inline
    symbol_type
    make_OP_SGET_WIDE (const location_type& l);

    static inline
    symbol_type
    make_OP_SGET_OBJECT (const location_type& l);

    static inline
    symbol_type
    make_OP_SGET_BOOLEAN (const location_type& l);

    static inline
    symbol_type
    make_OP_SGET_BYTE (const location_type& l);

    static inline
    symbol_type
    make_OP_SGET_CHAR (const location_type& l);

    static inline
    symbol_type
    make_OP_SGET_SHORT (const location_type& l);

    static inline
    symbol_type
    make_OP_SPUT (const location_type& l);

    static inline
    symbol_type
    make_OP_SPUT_WIDE (const location_type& l);

    static inline
    symbol_type
    make_OP_SPUT_OBJECT (const location_type& l);

    static inline
    symbol_type
    make_OP_SPUT_BOOLEAN (const location_type& l);

    static inline
    symbol_type
    make_OP_SPUT_BYTE (const location_type& l);

    static inline
    symbol_type
    make_OP_SPUT_CHAR (const location_type& l);

    static inline
    symbol_type
    make_OP_SPUT_SHORT (const location_type& l);

    static inline
    symbol_type
    make_OP_INVOKE_VIRTUAL (const location_type& l);

    static inline
    symbol_type
    make_OP_INVOKE_SUPER (const location_type& l);

    static inline
    symbol_type
    make_OP_INVOKE_DIRECT (const location_type& l);

    static inline
    symbol_type
    make_OP_INVOKE_STATIC (const location_type& l);

    static inline
    symbol_type
    make_OP_INVOKE_INTERFACE (const location_type& l);

    static inline
    symbol_type
    make_OP_UNUSED_73 (const location_type& l);

    static inline
    symbol_type
    make_OP_INVOKE_VIRTUAL_RANGE (const location_type& l);

    static inline
    symbol_type
    make_OP_INVOKE_SUPER_RANGE (const location_type& l);

    static inline
    symbol_type
    make_OP_INVOKE_DIRECT_RANGE (const location_type& l);

    static inline
    symbol_type
    make_OP_INVOKE_STATIC_RANGE (const location_type& l);

    static inline
    symbol_type
    make_OP_INVOKE_INTERFACE_RANGE (const location_type& l);

    static inline
    symbol_type
    make_OP_UNUSED_79 (const location_type& l);

    static inline
    symbol_type
    make_OP_UNUSED_7A (const location_type& l);

    static inline
    symbol_type
    make_OP_NEG_INT (const location_type& l);

    static inline
    symbol_type
    make_OP_NOT_INT (const location_type& l);

    static inline
    symbol_type
    make_OP_NEG_LONG (const location_type& l);

    static inline
    symbol_type
    make_OP_NOT_LONG (const location_type& l);

    static inline
    symbol_type
    make_OP_NEG_FLOAT (const location_type& l);

    static inline
    symbol_type
    make_OP_NEG_DOUBLE (const location_type& l);

    static inline
    symbol_type
    make_OP_INT_TO_LONG (const location_type& l);

    static inline
    symbol_type
    make_OP_INT_TO_FLOAT (const location_type& l);

    static inline
    symbol_type
    make_OP_INT_TO_DOUBLE (const location_type& l);

    static inline
    symbol_type
    make_OP_LONG_TO_INT (const location_type& l);

    static inline
    symbol_type
    make_OP_LONG_TO_FLOAT (const location_type& l);

    static inline
    symbol_type
    make_OP_LONG_TO_DOUBLE (const location_type& l);

    static inline
    symbol_type
    make_OP_FLOAT_TO_INT (const location_type& l);

    static inline
    symbol_type
    make_OP_FLOAT_TO_LONG (const location_type& l);

    static inline
    symbol_type
    make_OP_FLOAT_TO_DOUBLE (const location_type& l);

    static inline
    symbol_type
    make_OP_DOUBLE_TO_INT (const location_type& l);

    static inline
    symbol_type
    make_OP_DOUBLE_TO_LONG (const location_type& l);

    static inline
    symbol_type
    make_OP_DOUBLE_TO_FLOAT (const location_type& l);

    static inline
    symbol_type
    make_OP_INT_TO_BYTE (const location_type& l);

    static inline
    symbol_type
    make_OP_INT_TO_CHAR (const location_type& l);

    static inline
    symbol_type
    make_OP_INT_TO_SHORT (const location_type& l);

    static inline
    symbol_type
    make_OP_ADD_INT (const location_type& l);

    static inline
    symbol_type
    make_OP_SUB_INT (const location_type& l);

    static inline
    symbol_type
    make_OP_MUL_INT (const location_type& l);

    static inline
    symbol_type
    make_OP_DIV_INT (const location_type& l);

    static inline
    symbol_type
    make_OP_REM_INT (const location_type& l);

    static inline
    symbol_type
    make_OP_AND_INT (const location_type& l);

    static inline
    symbol_type
    make_OP_OR_INT (const location_type& l);

    static inline
    symbol_type
    make_OP_XOR_INT (const location_type& l);

    static inline
    symbol_type
    make_OP_SHL_INT (const location_type& l);

    static inline
    symbol_type
    make_OP_SHR_INT (const location_type& l);

    static inline
    symbol_type
    make_OP_USHR_INT (const location_type& l);

    static inline
    symbol_type
    make_OP_ADD_LONG (const location_type& l);

    static inline
    symbol_type
    make_OP_SUB_LONG (const location_type& l);

    static inline
    symbol_type
    make_OP_MUL_LONG (const location_type& l);

    static inline
    symbol_type
    make_OP_DIV_LONG (const location_type& l);

    static inline
    symbol_type
    make_OP_REM_LONG (const location_type& l);

    static inline
    symbol_type
    make_OP_AND_LONG (const location_type& l);

    static inline
    symbol_type
    make_OP_OR_LONG (const location_type& l);

    static inline
    symbol_type
    make_OP_XOR_LONG (const location_type& l);

    static inline
    symbol_type
    make_OP_SHL_LONG (const location_type& l);

    static inline
    symbol_type
    make_OP_SHR_LONG (const location_type& l);

    static inline
    symbol_type
    make_OP_USHR_LONG (const location_type& l);

    static inline
    symbol_type
    make_OP_ADD_FLOAT (const location_type& l);

    static inline
    symbol_type
    make_OP_SUB_FLOAT (const location_type& l);

    static inline
    symbol_type
    make_OP_MUL_FLOAT (const location_type& l);

    static inline
    symbol_type
    make_OP_DIV_FLOAT (const location_type& l);

    static inline
    symbol_type
    make_OP_REM_FLOAT (const location_type& l);

    static inline
    symbol_type
    make_OP_ADD_DOUBLE (const location_type& l);

    static inline
    symbol_type
    make_OP_SUB_DOUBLE (const location_type& l);

    static inline
    symbol_type
    make_OP_MUL_DOUBLE (const location_type& l);

    static inline
    symbol_type
    make_OP_DIV_DOUBLE (const location_type& l);

    static inline
    symbol_type
    make_OP_REM_DOUBLE (const location_type& l);

    static inline
    symbol_type
    make_OP_ADD_INT_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_SUB_INT_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_MUL_INT_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_DIV_INT_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_REM_INT_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_AND_INT_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_OR_INT_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_XOR_INT_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_SHL_INT_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_SHR_INT_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_USHR_INT_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_ADD_LONG_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_SUB_LONG_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_MUL_LONG_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_DIV_LONG_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_REM_LONG_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_AND_LONG_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_OR_LONG_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_XOR_LONG_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_SHL_LONG_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_SHR_LONG_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_USHR_LONG_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_ADD_FLOAT_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_SUB_FLOAT_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_MUL_FLOAT_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_DIV_FLOAT_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_REM_FLOAT_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_ADD_DOUBLE_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_SUB_DOUBLE_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_MUL_DOUBLE_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_DIV_DOUBLE_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_REM_DOUBLE_2ADDR (const location_type& l);

    static inline
    symbol_type
    make_OP_ADD_INT_LIT16 (const location_type& l);

    static inline
    symbol_type
    make_OP_RSUB_INT (const location_type& l);

    static inline
    symbol_type
    make_OP_MUL_INT_LIT16 (const location_type& l);

    static inline
    symbol_type
    make_OP_DIV_INT_LIT16 (const location_type& l);

    static inline
    symbol_type
    make_OP_REM_INT_LIT16 (const location_type& l);

    static inline
    symbol_type
    make_OP_AND_INT_LIT16 (const location_type& l);

    static inline
    symbol_type
    make_OP_OR_INT_LIT16 (const location_type& l);

    static inline
    symbol_type
    make_OP_XOR_INT_LIT16 (const location_type& l);

    static inline
    symbol_type
    make_OP_ADD_INT_LIT8 (const location_type& l);

    static inline
    symbol_type
    make_OP_RSUB_INT_LIT8 (const location_type& l);

    static inline
    symbol_type
    make_OP_MUL_INT_LIT8 (const location_type& l);

    static inline
    symbol_type
    make_OP_DIV_INT_LIT8 (const location_type& l);

    static inline
    symbol_type
    make_OP_REM_INT_LIT8 (const location_type& l);

    static inline
    symbol_type
    make_OP_AND_INT_LIT8 (const location_type& l);

    static inline
    symbol_type
    make_OP_OR_INT_LIT8 (const location_type& l);

    static inline
    symbol_type
    make_OP_XOR_INT_LIT8 (const location_type& l);

    static inline
    symbol_type
    make_OP_SHL_INT_LIT8 (const location_type& l);

    static inline
    symbol_type
    make_OP_SHR_INT_LIT8 (const location_type& l);

    static inline
    symbol_type
    make_OP_USHR_INT_LIT8 (const location_type& l);

    static inline
    symbol_type
    make_OP_IGET_VOLATILE (const location_type& l);

    static inline
    symbol_type
    make_OP_IPUT_VOLATILE (const location_type& l);

    static inline
    symbol_type
    make_OP_SGET_VOLATILE (const location_type& l);

    static inline
    symbol_type
    make_OP_SPUT_VOLATILE (const location_type& l);

    static inline
    symbol_type
    make_OP_IGET_OBJECT_VOLATILE (const location_type& l);

    static inline
    symbol_type
    make_OP_IGET_WIDE_VOLATILE (const location_type& l);

    static inline
    symbol_type
    make_OP_IPUT_WIDE_VOLATILE (const location_type& l);

    static inline
    symbol_type
    make_OP_SGET_WIDE_VOLATILE (const location_type& l);

    static inline
    symbol_type
    make_OP_SPUT_WIDE_VOLATILE (const location_type& l);

    static inline
    symbol_type
    make_OP_BREAKPOINT (const location_type& l);

    static inline
    symbol_type
    make_OP_THROW_VERIFICATION_ERROR (const location_type& l);

    static inline
    symbol_type
    make_OP_EXECUTE_INLINE (const location_type& l);

    static inline
    symbol_type
    make_OP_EXECUTE_INLINE_RANGE (const location_type& l);

    static inline
    symbol_type
    make_OP_INVOKE_OBJECT_INIT_RANGE (const location_type& l);

    static inline
    symbol_type
    make_OP_RETURN_VOID_BARRIER (const location_type& l);

    static inline
    symbol_type
    make_OP_IGET_QUICK (const location_type& l);

    static inline
    symbol_type
    make_OP_IGET_WIDE_QUICK (const location_type& l);

    static inline
    symbol_type
    make_OP_IGET_OBJECT_QUICK (const location_type& l);

    static inline
    symbol_type
    make_OP_IPUT_QUICK (const location_type& l);

    static inline
    symbol_type
    make_OP_IPUT_WIDE_QUICK (const location_type& l);

    static inline
    symbol_type
    make_OP_IPUT_OBJECT_QUICK (const location_type& l);

    static inline
    symbol_type
    make_OP_INVOKE_VIRTUAL_QUICK (const location_type& l);

    static inline
    symbol_type
    make_OP_INVOKE_VIRTUAL_QUICK_RANGE (const location_type& l);

    static inline
    symbol_type
    make_OP_INVOKE_SUPER_QUICK (const location_type& l);

    static inline
    symbol_type
    make_OP_INVOKE_SUPER_QUICK_RANGE (const location_type& l);

    static inline
    symbol_type
    make_OP_IPUT_OBJECT_VOLATILE (const location_type& l);

    static inline
    symbol_type
    make_OP_SGET_OBJECT_VOLATILE (const location_type& l);

    static inline
    symbol_type
    make_OP_SPUT_OBJECT_VOLATILE (const location_type& l);

    static inline
    symbol_type
    make_OP_UNUSED_FF (const location_type& l);

    static inline
    symbol_type
    make_OP_END (const location_type& l);

    static inline
    symbol_type
    make_SYMBOL_BEGIN (const location_type& l);

    static inline
    symbol_type
    make_DOTDOT (const location_type& l);

    static inline
    symbol_type
    make_ARROW (const location_type& l);

    static inline
    symbol_type
    make_EQUAL (const location_type& l);

    static inline
    symbol_type
    make_COLON (const location_type& l);

    static inline
    symbol_type
    make_COMMA (const location_type& l);

    static inline
    symbol_type
    make_OPEN_BRACE (const location_type& l);

    static inline
    symbol_type
    make_CLOSE_BRACE (const location_type& l);

    static inline
    symbol_type
    make_OPEN_PAREN (const location_type& l);

    static inline
    symbol_type
    make_CLOSE_PAREN (const location_type& l);

    static inline
    symbol_type
    make_SYMBOL_END (const location_type& l);


    /// Build a parser object.
     SmaliParser  (Analysis::SmaliLexer &lexer_yyarg, Analysis::Interpreter &driver_yyarg);
    virtual ~ SmaliParser  ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

  private:
    /// This class is not copyable.
     SmaliParser  (const  SmaliParser &);
     SmaliParser & operator= (const  SmaliParser &);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const signed char yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const signed char yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const signed char yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const unsigned char yytable_[];

  static const unsigned char yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned short int yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned short int yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if YYDEBUG
  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short int yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const;

      /// The state number used to denote an empty symbol.
      enum { empty_state = -1 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, symbol_type& sym);
      /// Assignment, needed by push_back.
      stack_symbol_type& operator= (const stack_symbol_type& that);
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    void yypop_ (unsigned int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 0,     ///< Last index in yytable_.
      yynnts_ = 2,  ///< Number of nonterminal symbols.
      yyfinal_ = 2, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 337  ///< Number of tokens.
    };


    // User arguments.
    Analysis::SmaliLexer &lexer;
    Analysis::Interpreter &driver;
  };

  // Symbol number corresponding to token number t.
  inline
   SmaliParser ::token_number_type
   SmaliParser ::yytranslate_ (token_type t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336
    };
    const unsigned int user_token_number_max_ = 591;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  inline
   SmaliParser ::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
   SmaliParser ::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
   SmaliParser ::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
      switch (other.type_get ())
    {
      case 48: // "true|false"
      case 51: // "flag"
      case 52: // "v(p)x"
        value.copy< int > (other.value);
        break;

      case 4: // "lex error"
      case 39: // "Integer"
      case 40: // "- Integer"
      case 41: // "- Integer L"
      case 42: // "- Integer S"
      case 43: // "- Integer T"
      case 44: // "FloatOrID F"
      case 45: // "FloatOrID D"
      case 46: // "Float F"
      case 47: // "Float D"
      case 53: // "ZBSCIJFDLIT"
      case 54: // "ZBSCIJFD"
      case 55: // "Lxxx;"
      case 56: // "[["
      case 58: // "simple name"
      case 59: // "member name"
      case 60: // "string"
      case 61: // "char"
      case 62: // "build runtime system"
      case 63: // "ver type error"
      case 64: // "inline@0x"
      case 65: // "vtable@0x"
      case 66: // "field@0x"
      case 67: // "#xxx"
        value.copy< std::string > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
   SmaliParser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {
    (void) v;
      switch (this->type_get ())
    {
      case 48: // "true|false"
      case 51: // "flag"
      case 52: // "v(p)x"
        value.copy< int > (v);
        break;

      case 4: // "lex error"
      case 39: // "Integer"
      case 40: // "- Integer"
      case 41: // "- Integer L"
      case 42: // "- Integer S"
      case 43: // "- Integer T"
      case 44: // "FloatOrID F"
      case 45: // "FloatOrID D"
      case 46: // "Float F"
      case 47: // "Float D"
      case 53: // "ZBSCIJFDLIT"
      case 54: // "ZBSCIJFD"
      case 55: // "Lxxx;"
      case 56: // "[["
      case 58: // "simple name"
      case 59: // "member name"
      case 60: // "string"
      case 61: // "char"
      case 62: // "build runtime system"
      case 63: // "ver type error"
      case 64: // "inline@0x"
      case 65: // "vtable@0x"
      case 66: // "field@0x"
      case 67: // "#xxx"
        value.copy< std::string > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
   SmaliParser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
   SmaliParser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const int v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   SmaliParser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  template <typename Base>
  inline
   SmaliParser ::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
   SmaliParser ::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
    switch (yytype)
    {
      case 48: // "true|false"
      case 51: // "flag"
      case 52: // "v(p)x"
        value.template destroy< int > ();
        break;

      case 4: // "lex error"
      case 39: // "Integer"
      case 40: // "- Integer"
      case 41: // "- Integer L"
      case 42: // "- Integer S"
      case 43: // "- Integer T"
      case 44: // "FloatOrID F"
      case 45: // "FloatOrID D"
      case 46: // "Float F"
      case 47: // "Float D"
      case 53: // "ZBSCIJFDLIT"
      case 54: // "ZBSCIJFD"
      case 55: // "Lxxx;"
      case 56: // "[["
      case 58: // "simple name"
      case 59: // "member name"
      case 60: // "string"
      case 61: // "char"
      case 62: // "build runtime system"
      case 63: // "ver type error"
      case 64: // "inline@0x"
      case 65: // "vtable@0x"
      case 66: // "field@0x"
      case 67: // "#xxx"
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  inline
  bool
   SmaliParser ::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
   SmaliParser ::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 48: // "true|false"
      case 51: // "flag"
      case 52: // "v(p)x"
        value.move< int > (s.value);
        break;

      case 4: // "lex error"
      case 39: // "Integer"
      case 40: // "- Integer"
      case 41: // "- Integer L"
      case 42: // "- Integer S"
      case 43: // "- Integer T"
      case 44: // "FloatOrID F"
      case 45: // "FloatOrID D"
      case 46: // "Float F"
      case 47: // "Float D"
      case 53: // "ZBSCIJFDLIT"
      case 54: // "ZBSCIJFD"
      case 55: // "Lxxx;"
      case 56: // "[["
      case 58: // "simple name"
      case 59: // "member name"
      case 60: // "string"
      case 61: // "char"
      case 62: // "build runtime system"
      case 63: // "ver type error"
      case 64: // "inline@0x"
      case 65: // "vtable@0x"
      case 66: // "field@0x"
      case 67: // "#xxx"
        value.move< std::string > (s.value);
        break;

      default:
        break;
    }

    location = s.location;
  }

  // by_type.
  inline
   SmaliParser ::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
   SmaliParser ::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
   SmaliParser ::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
   SmaliParser ::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
   SmaliParser ::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
   SmaliParser ::by_type::type_get () const
  {
    return type;
  }

  inline
   SmaliParser ::token_type
   SmaliParser ::by_type::token () const
  {
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short int
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     555,   556,   557,   558,   559,   560,   561,   562,   563,   564,
     565,   566,   567,   568,   569,   570,   571,   572,   573,   574,
     575,   576,   577,   578,   579,   580,   581,   582,   583,   584,
     585,   586,   587,   588,   589,   590,   591
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }
  // Implementation of make_symbol for each symbol type.
   SmaliParser ::symbol_type
   SmaliParser ::make_END (const location_type& l)
  {
    return symbol_type (token::TOKEN_END, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_EOL (const location_type& l)
  {
    return symbol_type (token::TOKEN_EOL, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_ERROR (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_ERROR, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_KEYWORD_BEGIN (const location_type& l)
  {
    return symbol_type (token::TOKEN_KEYWORD_BEGIN, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_CLASS_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_CLASS_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_SUPER_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_SUPER_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_IMPLEMENTS_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_IMPLEMENTS_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_SOURCE_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_SOURCE_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_FIELD_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_FIELD_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_END_FIELD_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_END_FIELD_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_SUBANNOTATION_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_SUBANNOTATION_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_END_SUBANNOTATION_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_END_SUBANNOTATION_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_ANNOTATION_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_ANNOTATION_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_END_ANNOTATION_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_END_ANNOTATION_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_ENUM_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_ENUM_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_METHOD_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_METHOD_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_END_METHOD_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_END_METHOD_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_REGISTERS_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_REGISTERS_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_LOCALS_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_LOCALS_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_ARRAY_DATA_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_ARRAY_DATA_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_END_ARRAY_DATA_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_END_ARRAY_DATA_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_PACKED_SWITCH_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_PACKED_SWITCH_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_END_PACKED_SWITCH_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_END_PACKED_SWITCH_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_SPARSE_SWITCH_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_SPARSE_SWITCH_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_END_SPARSE_SWITCH_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_END_SPARSE_SWITCH_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_CATCH_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_CATCH_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_CATCHALL_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_CATCHALL_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_LINE_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_LINE_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_PARAMETER_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_PARAMETER_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_END_PARAMETER_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_END_PARAMETER_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_LOCAL_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_LOCAL_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_END_LOCAL_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_END_LOCAL_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_RESTART_LOCAL_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_RESTART_LOCAL_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_PROLOGUE_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_PROLOGUE_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_EPILOGUE_DIRECTIVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_EPILOGUE_DIRECTIVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_KEYWORD_END (const location_type& l)
  {
    return symbol_type (token::TOKEN_KEYWORD_END, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_NUMBER_BEGIN (const location_type& l)
  {
    return symbol_type (token::TOKEN_NUMBER_BEGIN, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_POSITIVE_INTEGER_LITERAL (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_POSITIVE_INTEGER_LITERAL, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_NEGATIVE_INTEGER_LITERAL (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_NEGATIVE_INTEGER_LITERAL, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_LONG_LITERAL (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_LONG_LITERAL, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_SHORT_LITERAL (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_SHORT_LITERAL, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_BYTE_LITERAL (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_BYTE_LITERAL, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_FLOAT_LITERAL_OR_ID (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_FLOAT_LITERAL_OR_ID, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_DOUBLE_LITERAL_OR_ID (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_DOUBLE_LITERAL_OR_ID, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_FLOAT_LITERAL (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_FLOAT_LITERAL, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_DOUBLE_LITERAL (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_DOUBLE_LITERAL, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_BOOL_LITERAL (const int& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_BOOL_LITERAL, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_NULL_LITERAL (const location_type& l)
  {
    return symbol_type (token::TOKEN_NULL_LITERAL, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_NUMBER_END (const location_type& l)
  {
    return symbol_type (token::TOKEN_NUMBER_END, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_FLAG (const int& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_FLAG, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_REGISTER (const int& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_REGISTER, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_PARAM_LIST_OR_ID_PRIMITIVE_TYPE (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_PARAM_LIST_OR_ID_PRIMITIVE_TYPE, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_PRIMITIVE_TYPE (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_PRIMITIVE_TYPE, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_CLASS_DESCRIPTOR (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_CLASS_DESCRIPTOR, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_ARRAY_TYPE_PREFIX (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_ARRAY_TYPE_PREFIX, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_VOID_TYPE (const location_type& l)
  {
    return symbol_type (token::TOKEN_VOID_TYPE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_SIMPLE_NAME (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_SIMPLE_NAME, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_MEMBER_NAME (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_MEMBER_NAME, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_STRING_LITERAL (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_STRING_LITERAL, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_CHAR_LITERAL (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_CHAR_LITERAL, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_ANNOTATION_VISIBILITY (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_ANNOTATION_VISIBILITY, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_VERIFICATION_ERROR_TYPE (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_VERIFICATION_ERROR_TYPE, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_INLINE_INDEX (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_INLINE_INDEX, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_VTABLE_INDEX (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_VTABLE_INDEX, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_FIELD_OFFSET (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_FIELD_OFFSET, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_LINE_COMMENT (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_LINE_COMMENT, v, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_BEGIN (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_BEGIN, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_NOP (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_NOP, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_MOVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_MOVE_FROM16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE_FROM16, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_MOVE_16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE_16, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_MOVE_WIDE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE_WIDE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_MOVE_WIDE_FROM16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE_WIDE_FROM16, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_MOVE_WIDE_16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE_WIDE_16, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_MOVE_OBJECT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE_OBJECT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_MOVE_OBJECT_FROM16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE_OBJECT_FROM16, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_MOVE_OBJECT_16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE_OBJECT_16, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_MOVE_RESULT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE_RESULT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_MOVE_RESULT_WIDE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE_RESULT_WIDE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_MOVE_RESULT_OBJECT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE_RESULT_OBJECT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_MOVE_EXCEPTION (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE_EXCEPTION, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_RETURN_VOID (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_RETURN_VOID, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_RETURN (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_RETURN, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_RETURN_WIDE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_RETURN_WIDE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_RETURN_OBJECT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_RETURN_OBJECT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_CONST_4 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CONST_4, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_CONST_16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CONST_16, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_CONST (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CONST, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_CONST_HIGH16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CONST_HIGH16, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_CONST_WIDE_16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CONST_WIDE_16, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_CONST_WIDE_32 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CONST_WIDE_32, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_CONST_WIDE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CONST_WIDE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_CONST_WIDE_HIGH16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CONST_WIDE_HIGH16, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_CONST_STRING (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CONST_STRING, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_CONST_STRING_JUMBO (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CONST_STRING_JUMBO, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_CONST_CLASS (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CONST_CLASS, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_MONITOR_ENTER (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MONITOR_ENTER, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_MONITOR_EXIT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MONITOR_EXIT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_CHECK_CAST (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CHECK_CAST, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_INSTANCE_OF (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INSTANCE_OF, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_ARRAY_LENGTH (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_ARRAY_LENGTH, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_NEW_INSTANCE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_NEW_INSTANCE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_NEW_ARRAY (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_NEW_ARRAY, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_FILLED_NEW_ARRAY (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_FILLED_NEW_ARRAY, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_FILLED_NEW_ARRAY_RANGE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_FILLED_NEW_ARRAY_RANGE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_FILL_ARRAY_DATA (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_FILL_ARRAY_DATA, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_THROW (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_THROW, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_GOTO (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_GOTO, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_GOTO_16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_GOTO_16, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_GOTO_32 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_GOTO_32, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_PACKED_SWITCH (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_PACKED_SWITCH, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SPARSE_SWITCH (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SPARSE_SWITCH, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_CMPL_FLOAT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CMPL_FLOAT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_CMPG_FLOAT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CMPG_FLOAT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_CMPL_DOUBLE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CMPL_DOUBLE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_CMPG_DOUBLE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CMPG_DOUBLE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_CMP_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CMP_LONG, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IF_EQ (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IF_EQ, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IF_NE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IF_NE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IF_LT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IF_LT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IF_GE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IF_GE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IF_GT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IF_GT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IF_LE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IF_LE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IF_EQZ (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IF_EQZ, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IF_NEZ (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IF_NEZ, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IF_LTZ (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IF_LTZ, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IF_GEZ (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IF_GEZ, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IF_GTZ (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IF_GTZ, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IF_LEZ (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IF_LEZ, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_UNUSED_3E (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_UNUSED_3E, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_UNUSED_3F (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_UNUSED_3F, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_UNUSED_40 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_UNUSED_40, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_UNUSED_41 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_UNUSED_41, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_UNUSED_42 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_UNUSED_42, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_UNUSED_43 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_UNUSED_43, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_AGET (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AGET, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_AGET_WIDE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AGET_WIDE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_AGET_OBJECT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AGET_OBJECT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_AGET_BOOLEAN (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AGET_BOOLEAN, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_AGET_BYTE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AGET_BYTE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_AGET_CHAR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AGET_CHAR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_AGET_SHORT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AGET_SHORT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_APUT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_APUT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_APUT_WIDE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_APUT_WIDE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_APUT_OBJECT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_APUT_OBJECT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_APUT_BOOLEAN (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_APUT_BOOLEAN, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_APUT_BYTE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_APUT_BYTE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_APUT_CHAR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_APUT_CHAR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_APUT_SHORT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_APUT_SHORT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IGET (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IGET_WIDE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET_WIDE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IGET_OBJECT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET_OBJECT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IGET_BOOLEAN (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET_BOOLEAN, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IGET_BYTE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET_BYTE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IGET_CHAR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET_CHAR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IGET_SHORT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET_SHORT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IPUT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IPUT_WIDE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT_WIDE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IPUT_OBJECT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT_OBJECT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IPUT_BOOLEAN (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT_BOOLEAN, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IPUT_BYTE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT_BYTE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IPUT_CHAR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT_CHAR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IPUT_SHORT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT_SHORT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SGET (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SGET, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SGET_WIDE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SGET_WIDE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SGET_OBJECT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SGET_OBJECT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SGET_BOOLEAN (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SGET_BOOLEAN, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SGET_BYTE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SGET_BYTE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SGET_CHAR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SGET_CHAR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SGET_SHORT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SGET_SHORT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SPUT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SPUT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SPUT_WIDE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SPUT_WIDE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SPUT_OBJECT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SPUT_OBJECT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SPUT_BOOLEAN (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SPUT_BOOLEAN, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SPUT_BYTE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SPUT_BYTE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SPUT_CHAR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SPUT_CHAR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SPUT_SHORT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SPUT_SHORT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_INVOKE_VIRTUAL (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_VIRTUAL, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_INVOKE_SUPER (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_SUPER, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_INVOKE_DIRECT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_DIRECT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_INVOKE_STATIC (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_STATIC, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_INVOKE_INTERFACE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_INTERFACE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_UNUSED_73 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_UNUSED_73, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_INVOKE_VIRTUAL_RANGE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_VIRTUAL_RANGE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_INVOKE_SUPER_RANGE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_SUPER_RANGE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_INVOKE_DIRECT_RANGE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_DIRECT_RANGE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_INVOKE_STATIC_RANGE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_STATIC_RANGE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_INVOKE_INTERFACE_RANGE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_INTERFACE_RANGE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_UNUSED_79 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_UNUSED_79, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_UNUSED_7A (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_UNUSED_7A, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_NEG_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_NEG_INT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_NOT_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_NOT_INT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_NEG_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_NEG_LONG, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_NOT_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_NOT_LONG, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_NEG_FLOAT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_NEG_FLOAT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_NEG_DOUBLE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_NEG_DOUBLE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_INT_TO_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INT_TO_LONG, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_INT_TO_FLOAT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INT_TO_FLOAT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_INT_TO_DOUBLE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INT_TO_DOUBLE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_LONG_TO_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_LONG_TO_INT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_LONG_TO_FLOAT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_LONG_TO_FLOAT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_LONG_TO_DOUBLE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_LONG_TO_DOUBLE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_FLOAT_TO_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_FLOAT_TO_INT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_FLOAT_TO_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_FLOAT_TO_LONG, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_FLOAT_TO_DOUBLE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_FLOAT_TO_DOUBLE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_DOUBLE_TO_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DOUBLE_TO_INT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_DOUBLE_TO_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DOUBLE_TO_LONG, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_DOUBLE_TO_FLOAT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DOUBLE_TO_FLOAT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_INT_TO_BYTE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INT_TO_BYTE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_INT_TO_CHAR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INT_TO_CHAR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_INT_TO_SHORT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INT_TO_SHORT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_ADD_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_ADD_INT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SUB_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SUB_INT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_MUL_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MUL_INT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_DIV_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DIV_INT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_REM_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_REM_INT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_AND_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AND_INT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_OR_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_OR_INT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_XOR_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_XOR_INT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SHL_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SHL_INT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SHR_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SHR_INT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_USHR_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_USHR_INT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_ADD_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_ADD_LONG, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SUB_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SUB_LONG, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_MUL_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MUL_LONG, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_DIV_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DIV_LONG, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_REM_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_REM_LONG, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_AND_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AND_LONG, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_OR_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_OR_LONG, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_XOR_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_XOR_LONG, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SHL_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SHL_LONG, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SHR_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SHR_LONG, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_USHR_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_USHR_LONG, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_ADD_FLOAT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_ADD_FLOAT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SUB_FLOAT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SUB_FLOAT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_MUL_FLOAT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MUL_FLOAT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_DIV_FLOAT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DIV_FLOAT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_REM_FLOAT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_REM_FLOAT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_ADD_DOUBLE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_ADD_DOUBLE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SUB_DOUBLE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SUB_DOUBLE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_MUL_DOUBLE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MUL_DOUBLE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_DIV_DOUBLE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DIV_DOUBLE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_REM_DOUBLE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_REM_DOUBLE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_ADD_INT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_ADD_INT_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SUB_INT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SUB_INT_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_MUL_INT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MUL_INT_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_DIV_INT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DIV_INT_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_REM_INT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_REM_INT_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_AND_INT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AND_INT_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_OR_INT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_OR_INT_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_XOR_INT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_XOR_INT_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SHL_INT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SHL_INT_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SHR_INT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SHR_INT_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_USHR_INT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_USHR_INT_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_ADD_LONG_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_ADD_LONG_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SUB_LONG_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SUB_LONG_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_MUL_LONG_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MUL_LONG_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_DIV_LONG_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DIV_LONG_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_REM_LONG_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_REM_LONG_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_AND_LONG_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AND_LONG_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_OR_LONG_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_OR_LONG_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_XOR_LONG_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_XOR_LONG_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SHL_LONG_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SHL_LONG_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SHR_LONG_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SHR_LONG_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_USHR_LONG_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_USHR_LONG_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_ADD_FLOAT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_ADD_FLOAT_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SUB_FLOAT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SUB_FLOAT_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_MUL_FLOAT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MUL_FLOAT_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_DIV_FLOAT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DIV_FLOAT_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_REM_FLOAT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_REM_FLOAT_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_ADD_DOUBLE_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_ADD_DOUBLE_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SUB_DOUBLE_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SUB_DOUBLE_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_MUL_DOUBLE_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MUL_DOUBLE_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_DIV_DOUBLE_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DIV_DOUBLE_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_REM_DOUBLE_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_REM_DOUBLE_2ADDR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_ADD_INT_LIT16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_ADD_INT_LIT16, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_RSUB_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_RSUB_INT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_MUL_INT_LIT16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MUL_INT_LIT16, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_DIV_INT_LIT16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DIV_INT_LIT16, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_REM_INT_LIT16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_REM_INT_LIT16, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_AND_INT_LIT16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AND_INT_LIT16, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_OR_INT_LIT16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_OR_INT_LIT16, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_XOR_INT_LIT16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_XOR_INT_LIT16, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_ADD_INT_LIT8 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_ADD_INT_LIT8, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_RSUB_INT_LIT8 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_RSUB_INT_LIT8, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_MUL_INT_LIT8 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MUL_INT_LIT8, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_DIV_INT_LIT8 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DIV_INT_LIT8, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_REM_INT_LIT8 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_REM_INT_LIT8, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_AND_INT_LIT8 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AND_INT_LIT8, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_OR_INT_LIT8 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_OR_INT_LIT8, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_XOR_INT_LIT8 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_XOR_INT_LIT8, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SHL_INT_LIT8 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SHL_INT_LIT8, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SHR_INT_LIT8 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SHR_INT_LIT8, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_USHR_INT_LIT8 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_USHR_INT_LIT8, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IGET_VOLATILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET_VOLATILE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IPUT_VOLATILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT_VOLATILE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SGET_VOLATILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SGET_VOLATILE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SPUT_VOLATILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SPUT_VOLATILE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IGET_OBJECT_VOLATILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET_OBJECT_VOLATILE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IGET_WIDE_VOLATILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET_WIDE_VOLATILE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IPUT_WIDE_VOLATILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT_WIDE_VOLATILE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SGET_WIDE_VOLATILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SGET_WIDE_VOLATILE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SPUT_WIDE_VOLATILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SPUT_WIDE_VOLATILE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_BREAKPOINT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_BREAKPOINT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_THROW_VERIFICATION_ERROR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_THROW_VERIFICATION_ERROR, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_EXECUTE_INLINE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_EXECUTE_INLINE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_EXECUTE_INLINE_RANGE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_EXECUTE_INLINE_RANGE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_INVOKE_OBJECT_INIT_RANGE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_OBJECT_INIT_RANGE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_RETURN_VOID_BARRIER (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_RETURN_VOID_BARRIER, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IGET_QUICK (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET_QUICK, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IGET_WIDE_QUICK (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET_WIDE_QUICK, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IGET_OBJECT_QUICK (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET_OBJECT_QUICK, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IPUT_QUICK (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT_QUICK, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IPUT_WIDE_QUICK (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT_WIDE_QUICK, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IPUT_OBJECT_QUICK (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT_OBJECT_QUICK, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_INVOKE_VIRTUAL_QUICK (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_VIRTUAL_QUICK, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_INVOKE_VIRTUAL_QUICK_RANGE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_VIRTUAL_QUICK_RANGE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_INVOKE_SUPER_QUICK (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_SUPER_QUICK, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_INVOKE_SUPER_QUICK_RANGE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_SUPER_QUICK_RANGE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_IPUT_OBJECT_VOLATILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT_OBJECT_VOLATILE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SGET_OBJECT_VOLATILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SGET_OBJECT_VOLATILE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_SPUT_OBJECT_VOLATILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SPUT_OBJECT_VOLATILE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_UNUSED_FF (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_UNUSED_FF, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OP_END (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_END, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_SYMBOL_BEGIN (const location_type& l)
  {
    return symbol_type (token::TOKEN_SYMBOL_BEGIN, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_DOTDOT (const location_type& l)
  {
    return symbol_type (token::TOKEN_DOTDOT, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_ARROW (const location_type& l)
  {
    return symbol_type (token::TOKEN_ARROW, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_EQUAL (const location_type& l)
  {
    return symbol_type (token::TOKEN_EQUAL, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_COLON (const location_type& l)
  {
    return symbol_type (token::TOKEN_COLON, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_COMMA (const location_type& l)
  {
    return symbol_type (token::TOKEN_COMMA, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OPEN_BRACE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OPEN_BRACE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_CLOSE_BRACE (const location_type& l)
  {
    return symbol_type (token::TOKEN_CLOSE_BRACE, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_OPEN_PAREN (const location_type& l)
  {
    return symbol_type (token::TOKEN_OPEN_PAREN, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_CLOSE_PAREN (const location_type& l)
  {
    return symbol_type (token::TOKEN_CLOSE_PAREN, l);
  }

   SmaliParser ::symbol_type
   SmaliParser ::make_SYMBOL_END (const location_type& l)
  {
    return symbol_type (token::TOKEN_SYMBOL_END, l);
  }


#line 9 "SmaliParser.yy" // lalr1.cc:377
} //  Analysis 
#line 4807 "SmaliParser.hpp" // lalr1.cc:377




#endif // !YY_YY_SMALIPARSER_HPP_INCLUDED
