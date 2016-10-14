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
 ** \file Parser.hpp
 ** Define the  Analysis ::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
// //                    "%code requires" blocks.
#line 11 "Parser.yy" // lalr1.cc:377

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
// bison -o Parser.cpp Parser.yy
// to generate parser source file
// or
// bison -v -o Parser.cpp Parser.yy
// to debug.
//===----------------------------------------------------------------------===//
    #include <iostream>
    #include <string>
    #include <vector>
    #include <stdint.h>
    #include "Ops/Ops.h"

    namespace Analysis {
        class Lexer;
        class Interpreter;
    }

#line 73 "Parser.hpp" // lalr1.cc:377

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

#line 9 "Parser.yy" // lalr1.cc:377
namespace  Analysis  {
#line 150 "Parser.hpp" // lalr1.cc:377



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
  class  Parser 
  {
  public:
#ifndef YYSTYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // instruction
      char dummy1[sizeof(OpCode*)];

      // "flag"
      // "v(p)x"
      // exp
      // classdef
      // superdef
      // srcdef
      // fielddef
      // methoddef
      // flags
      // registers
      char dummy2[sizeof(int)];

      // "number"
      char dummy3[sizeof(int64_t)];

      // "c type string"
      // "name string"
      // "comment"
      // "class name"
      // "class type"
      // comment
      // jmplabel
      char dummy4[sizeof(std::string)];

      // regs
      char dummy5[sizeof(std::vector<int>)];

      // args
      char dummy6[sizeof(std::vector<std::string>)];
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
        TOKEN_CSTRING = 259,
        TOKEN_NAMESTRING = 260,
        TOKEN_COMMENT = 261,
        TOKEN_CLASSNAME = 262,
        TOKEN_CLASSTYPE = 263,
        TOKEN_KEYWORD_BEGIN = 264,
        TOKEN_CLASSBEG = 265,
        TOKEN_SUPERBEG = 266,
        TOKEN_SRCBEG = 267,
        TOKEN_FIELDBEG = 268,
        TOKEN_METHODBEG = 269,
        TOKEN_METHODEND = 270,
        TOKEN_REGISTERS = 271,
        TOKEN_PROLOGUE = 272,
        TOKEN_LINE = 273,
        TOKEN_KEYWORD_END = 274,
        TOKEN_FLAG = 275,
        TOKEN_REGD = 276,
        TOKEN_NUMBER = 277,
        TOKEN_OP_BEGIN = 278,
        TOKEN_OP_NOP = 279,
        TOKEN_OP_MOVE = 280,
        TOKEN_OP_MOVE_FROM16 = 281,
        TOKEN_OP_MOVE_16 = 282,
        TOKEN_OP_MOVE_WIDE = 283,
        TOKEN_OP_MOVE_WIDE_FROM16 = 284,
        TOKEN_OP_MOVE_WIDE_16 = 285,
        TOKEN_OP_MOVE_OBJECT = 286,
        TOKEN_OP_MOVE_OBJECT_FROM16 = 287,
        TOKEN_OP_MOVE_OBJECT_16 = 288,
        TOKEN_OP_MOVE_RESULT = 289,
        TOKEN_OP_MOVE_RESULT_WIDE = 290,
        TOKEN_OP_MOVE_RESULT_OBJECT = 291,
        TOKEN_OP_MOVE_EXCEPTION = 292,
        TOKEN_OP_RETURN_VOID = 293,
        TOKEN_OP_RETURN = 294,
        TOKEN_OP_RETURN_WIDE = 295,
        TOKEN_OP_RETURN_OBJECT = 296,
        TOKEN_OP_CONST_4 = 297,
        TOKEN_OP_CONST_16 = 298,
        TOKEN_OP_CONST = 299,
        TOKEN_OP_CONST_HIGH16 = 300,
        TOKEN_OP_CONST_WIDE_16 = 301,
        TOKEN_OP_CONST_WIDE_32 = 302,
        TOKEN_OP_CONST_WIDE = 303,
        TOKEN_OP_CONST_WIDE_HIGH16 = 304,
        TOKEN_OP_CONST_STRING = 305,
        TOKEN_OP_CONST_STRING_JUMBO = 306,
        TOKEN_OP_CONST_CLASS = 307,
        TOKEN_OP_MONITOR_ENTER = 308,
        TOKEN_OP_MONITOR_EXIT = 309,
        TOKEN_OP_CHECK_CAST = 310,
        TOKEN_OP_INSTANCE_OF = 311,
        TOKEN_OP_ARRAY_LENGTH = 312,
        TOKEN_OP_NEW_INSTANCE = 313,
        TOKEN_OP_NEW_ARRAY = 314,
        TOKEN_OP_FILLED_NEW_ARRAY = 315,
        TOKEN_OP_FILLED_NEW_ARRAY_RANGE = 316,
        TOKEN_OP_FILL_ARRAY_DATA = 317,
        TOKEN_OP_THROW = 318,
        TOKEN_OP_GOTO = 319,
        TOKEN_OP_GOTO_16 = 320,
        TOKEN_OP_GOTO_32 = 321,
        TOKEN_OP_PACKED_SWITCH = 322,
        TOKEN_OP_SPARSE_SWITCH = 323,
        TOKEN_OP_CMPL_FLOAT = 324,
        TOKEN_OP_CMPG_FLOAT = 325,
        TOKEN_OP_CMPL_DOUBLE = 326,
        TOKEN_OP_CMPG_DOUBLE = 327,
        TOKEN_OP_CMP_LONG = 328,
        TOKEN_OP_IF_EQ = 329,
        TOKEN_OP_IF_NE = 330,
        TOKEN_OP_IF_LT = 331,
        TOKEN_OP_IF_GE = 332,
        TOKEN_OP_IF_GT = 333,
        TOKEN_OP_IF_LE = 334,
        TOKEN_OP_IF_EQZ = 335,
        TOKEN_OP_IF_NEZ = 336,
        TOKEN_OP_IF_LTZ = 337,
        TOKEN_OP_IF_GEZ = 338,
        TOKEN_OP_IF_GTZ = 339,
        TOKEN_OP_IF_LEZ = 340,
        TOKEN_OP_UNUSED_3E = 341,
        TOKEN_OP_UNUSED_3F = 342,
        TOKEN_OP_UNUSED_40 = 343,
        TOKEN_OP_UNUSED_41 = 344,
        TOKEN_OP_UNUSED_42 = 345,
        TOKEN_OP_UNUSED_43 = 346,
        TOKEN_OP_AGET = 347,
        TOKEN_OP_AGET_WIDE = 348,
        TOKEN_OP_AGET_OBJECT = 349,
        TOKEN_OP_AGET_BOOLEAN = 350,
        TOKEN_OP_AGET_BYTE = 351,
        TOKEN_OP_AGET_CHAR = 352,
        TOKEN_OP_AGET_SHORT = 353,
        TOKEN_OP_APUT = 354,
        TOKEN_OP_APUT_WIDE = 355,
        TOKEN_OP_APUT_OBJECT = 356,
        TOKEN_OP_APUT_BOOLEAN = 357,
        TOKEN_OP_APUT_BYTE = 358,
        TOKEN_OP_APUT_CHAR = 359,
        TOKEN_OP_APUT_SHORT = 360,
        TOKEN_OP_IGET = 361,
        TOKEN_OP_IGET_WIDE = 362,
        TOKEN_OP_IGET_OBJECT = 363,
        TOKEN_OP_IGET_BOOLEAN = 364,
        TOKEN_OP_IGET_BYTE = 365,
        TOKEN_OP_IGET_CHAR = 366,
        TOKEN_OP_IGET_SHORT = 367,
        TOKEN_OP_IPUT = 368,
        TOKEN_OP_IPUT_WIDE = 369,
        TOKEN_OP_IPUT_OBJECT = 370,
        TOKEN_OP_IPUT_BOOLEAN = 371,
        TOKEN_OP_IPUT_BYTE = 372,
        TOKEN_OP_IPUT_CHAR = 373,
        TOKEN_OP_IPUT_SHORT = 374,
        TOKEN_OP_SGET = 375,
        TOKEN_OP_SGET_WIDE = 376,
        TOKEN_OP_SGET_OBJECT = 377,
        TOKEN_OP_SGET_BOOLEAN = 378,
        TOKEN_OP_SGET_BYTE = 379,
        TOKEN_OP_SGET_CHAR = 380,
        TOKEN_OP_SGET_SHORT = 381,
        TOKEN_OP_SPUT = 382,
        TOKEN_OP_SPUT_WIDE = 383,
        TOKEN_OP_SPUT_OBJECT = 384,
        TOKEN_OP_SPUT_BOOLEAN = 385,
        TOKEN_OP_SPUT_BYTE = 386,
        TOKEN_OP_SPUT_CHAR = 387,
        TOKEN_OP_SPUT_SHORT = 388,
        TOKEN_OP_INVOKE_VIRTUAL = 389,
        TOKEN_OP_INVOKE_SUPER = 390,
        TOKEN_OP_INVOKE_DIRECT = 391,
        TOKEN_OP_INVOKE_STATIC = 392,
        TOKEN_OP_INVOKE_INTERFACE = 393,
        TOKEN_OP_UNUSED_73 = 394,
        TOKEN_OP_INVOKE_VIRTUAL_RANGE = 395,
        TOKEN_OP_INVOKE_SUPER_RANGE = 396,
        TOKEN_OP_INVOKE_DIRECT_RANGE = 397,
        TOKEN_OP_INVOKE_STATIC_RANGE = 398,
        TOKEN_OP_INVOKE_INTERFACE_RANGE = 399,
        TOKEN_OP_UNUSED_79 = 400,
        TOKEN_OP_UNUSED_7A = 401,
        TOKEN_OP_NEG_INT = 402,
        TOKEN_OP_NOT_INT = 403,
        TOKEN_OP_NEG_LONG = 404,
        TOKEN_OP_NOT_LONG = 405,
        TOKEN_OP_NEG_FLOAT = 406,
        TOKEN_OP_NEG_DOUBLE = 407,
        TOKEN_OP_INT_TO_LONG = 408,
        TOKEN_OP_INT_TO_FLOAT = 409,
        TOKEN_OP_INT_TO_DOUBLE = 410,
        TOKEN_OP_LONG_TO_INT = 411,
        TOKEN_OP_LONG_TO_FLOAT = 412,
        TOKEN_OP_LONG_TO_DOUBLE = 413,
        TOKEN_OP_FLOAT_TO_INT = 414,
        TOKEN_OP_FLOAT_TO_LONG = 415,
        TOKEN_OP_FLOAT_TO_DOUBLE = 416,
        TOKEN_OP_DOUBLE_TO_INT = 417,
        TOKEN_OP_DOUBLE_TO_LONG = 418,
        TOKEN_OP_DOUBLE_TO_FLOAT = 419,
        TOKEN_OP_INT_TO_BYTE = 420,
        TOKEN_OP_INT_TO_CHAR = 421,
        TOKEN_OP_INT_TO_SHORT = 422,
        TOKEN_OP_ADD_INT = 423,
        TOKEN_OP_SUB_INT = 424,
        TOKEN_OP_MUL_INT = 425,
        TOKEN_OP_DIV_INT = 426,
        TOKEN_OP_REM_INT = 427,
        TOKEN_OP_AND_INT = 428,
        TOKEN_OP_OR_INT = 429,
        TOKEN_OP_XOR_INT = 430,
        TOKEN_OP_SHL_INT = 431,
        TOKEN_OP_SHR_INT = 432,
        TOKEN_OP_USHR_INT = 433,
        TOKEN_OP_ADD_LONG = 434,
        TOKEN_OP_SUB_LONG = 435,
        TOKEN_OP_MUL_LONG = 436,
        TOKEN_OP_DIV_LONG = 437,
        TOKEN_OP_REM_LONG = 438,
        TOKEN_OP_AND_LONG = 439,
        TOKEN_OP_OR_LONG = 440,
        TOKEN_OP_XOR_LONG = 441,
        TOKEN_OP_SHL_LONG = 442,
        TOKEN_OP_SHR_LONG = 443,
        TOKEN_OP_USHR_LONG = 444,
        TOKEN_OP_ADD_FLOAT = 445,
        TOKEN_OP_SUB_FLOAT = 446,
        TOKEN_OP_MUL_FLOAT = 447,
        TOKEN_OP_DIV_FLOAT = 448,
        TOKEN_OP_REM_FLOAT = 449,
        TOKEN_OP_ADD_DOUBLE = 450,
        TOKEN_OP_SUB_DOUBLE = 451,
        TOKEN_OP_MUL_DOUBLE = 452,
        TOKEN_OP_DIV_DOUBLE = 453,
        TOKEN_OP_REM_DOUBLE = 454,
        TOKEN_OP_ADD_INT_2ADDR = 455,
        TOKEN_OP_SUB_INT_2ADDR = 456,
        TOKEN_OP_MUL_INT_2ADDR = 457,
        TOKEN_OP_DIV_INT_2ADDR = 458,
        TOKEN_OP_REM_INT_2ADDR = 459,
        TOKEN_OP_AND_INT_2ADDR = 460,
        TOKEN_OP_OR_INT_2ADDR = 461,
        TOKEN_OP_XOR_INT_2ADDR = 462,
        TOKEN_OP_SHL_INT_2ADDR = 463,
        TOKEN_OP_SHR_INT_2ADDR = 464,
        TOKEN_OP_USHR_INT_2ADDR = 465,
        TOKEN_OP_ADD_LONG_2ADDR = 466,
        TOKEN_OP_SUB_LONG_2ADDR = 467,
        TOKEN_OP_MUL_LONG_2ADDR = 468,
        TOKEN_OP_DIV_LONG_2ADDR = 469,
        TOKEN_OP_REM_LONG_2ADDR = 470,
        TOKEN_OP_AND_LONG_2ADDR = 471,
        TOKEN_OP_OR_LONG_2ADDR = 472,
        TOKEN_OP_XOR_LONG_2ADDR = 473,
        TOKEN_OP_SHL_LONG_2ADDR = 474,
        TOKEN_OP_SHR_LONG_2ADDR = 475,
        TOKEN_OP_USHR_LONG_2ADDR = 476,
        TOKEN_OP_ADD_FLOAT_2ADDR = 477,
        TOKEN_OP_SUB_FLOAT_2ADDR = 478,
        TOKEN_OP_MUL_FLOAT_2ADDR = 479,
        TOKEN_OP_DIV_FLOAT_2ADDR = 480,
        TOKEN_OP_REM_FLOAT_2ADDR = 481,
        TOKEN_OP_ADD_DOUBLE_2ADDR = 482,
        TOKEN_OP_SUB_DOUBLE_2ADDR = 483,
        TOKEN_OP_MUL_DOUBLE_2ADDR = 484,
        TOKEN_OP_DIV_DOUBLE_2ADDR = 485,
        TOKEN_OP_REM_DOUBLE_2ADDR = 486,
        TOKEN_OP_ADD_INT_LIT16 = 487,
        TOKEN_OP_RSUB_INT = 488,
        TOKEN_OP_MUL_INT_LIT16 = 489,
        TOKEN_OP_DIV_INT_LIT16 = 490,
        TOKEN_OP_REM_INT_LIT16 = 491,
        TOKEN_OP_AND_INT_LIT16 = 492,
        TOKEN_OP_OR_INT_LIT16 = 493,
        TOKEN_OP_XOR_INT_LIT16 = 494,
        TOKEN_OP_ADD_INT_LIT8 = 495,
        TOKEN_OP_RSUB_INT_LIT8 = 496,
        TOKEN_OP_MUL_INT_LIT8 = 497,
        TOKEN_OP_DIV_INT_LIT8 = 498,
        TOKEN_OP_REM_INT_LIT8 = 499,
        TOKEN_OP_AND_INT_LIT8 = 500,
        TOKEN_OP_OR_INT_LIT8 = 501,
        TOKEN_OP_XOR_INT_LIT8 = 502,
        TOKEN_OP_SHL_INT_LIT8 = 503,
        TOKEN_OP_SHR_INT_LIT8 = 504,
        TOKEN_OP_USHR_INT_LIT8 = 505,
        TOKEN_OP_IGET_VOLATILE = 506,
        TOKEN_OP_IPUT_VOLATILE = 507,
        TOKEN_OP_SGET_VOLATILE = 508,
        TOKEN_OP_SPUT_VOLATILE = 509,
        TOKEN_OP_IGET_OBJECT_VOLATILE = 510,
        TOKEN_OP_IGET_WIDE_VOLATILE = 511,
        TOKEN_OP_IPUT_WIDE_VOLATILE = 512,
        TOKEN_OP_SGET_WIDE_VOLATILE = 513,
        TOKEN_OP_SPUT_WIDE_VOLATILE = 514,
        TOKEN_OP_BREAKPOINT = 515,
        TOKEN_OP_THROW_VERIFICATION_ERROR = 516,
        TOKEN_OP_EXECUTE_INLINE = 517,
        TOKEN_OP_EXECUTE_INLINE_RANGE = 518,
        TOKEN_OP_INVOKE_OBJECT_INIT_RANGE = 519,
        TOKEN_OP_RETURN_VOID_BARRIER = 520,
        TOKEN_OP_IGET_QUICK = 521,
        TOKEN_OP_IGET_WIDE_QUICK = 522,
        TOKEN_OP_IGET_OBJECT_QUICK = 523,
        TOKEN_OP_IPUT_QUICK = 524,
        TOKEN_OP_IPUT_WIDE_QUICK = 525,
        TOKEN_OP_IPUT_OBJECT_QUICK = 526,
        TOKEN_OP_INVOKE_VIRTUAL_QUICK = 527,
        TOKEN_OP_INVOKE_VIRTUAL_QUICK_RANGE = 528,
        TOKEN_OP_INVOKE_SUPER_QUICK = 529,
        TOKEN_OP_INVOKE_SUPER_QUICK_RANGE = 530,
        TOKEN_OP_IPUT_OBJECT_VOLATILE = 531,
        TOKEN_OP_SGET_OBJECT_VOLATILE = 532,
        TOKEN_OP_SPUT_OBJECT_VOLATILE = 533,
        TOKEN_OP_UNUSED_FF = 534,
        TOKEN_OP_CATCH = 535,
        TOKEN_OP_END = 536,
        TOKEN_OP_PACKED_SWITCHDATABEG = 537,
        TOKEN_OP_PACKED_SWITCHDATAEND = 538,
        TOKEN_SYMBOL_BEGIN = 539,
        TOKEN_COLON = 540,
        TOKEN_LEFTPAR = 541,
        TOKEN_RIGHTPAR = 542,
        TOKEN_COMMA = 543,
        TOKEN_POINT = 544,
        TOKEN_INIBRACE = 545,
        TOKEN_CLOBRACE = 546,
        TOKEN_ELLIPSIS = 547,
        TOKEN_SYMBOL_END = 548
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

  basic_symbol (typename Base::kind_type t, const OpCode* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const int v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const int64_t v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<int> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<std::string> v, const location_type& l);


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
    make_CSTRING (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_NAMESTRING (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_COMMENT (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_CLASSNAME (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_CLASSTYPE (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_KEYWORD_BEGIN (const location_type& l);

    static inline
    symbol_type
    make_CLASSBEG (const location_type& l);

    static inline
    symbol_type
    make_SUPERBEG (const location_type& l);

    static inline
    symbol_type
    make_SRCBEG (const location_type& l);

    static inline
    symbol_type
    make_FIELDBEG (const location_type& l);

    static inline
    symbol_type
    make_METHODBEG (const location_type& l);

    static inline
    symbol_type
    make_METHODEND (const location_type& l);

    static inline
    symbol_type
    make_REGISTERS (const location_type& l);

    static inline
    symbol_type
    make_PROLOGUE (const location_type& l);

    static inline
    symbol_type
    make_LINE (const location_type& l);

    static inline
    symbol_type
    make_KEYWORD_END (const location_type& l);

    static inline
    symbol_type
    make_FLAG (const int& v, const location_type& l);

    static inline
    symbol_type
    make_REGD (const int& v, const location_type& l);

    static inline
    symbol_type
    make_NUMBER (const int64_t& v, const location_type& l);

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
    make_OP_CATCH (const location_type& l);

    static inline
    symbol_type
    make_OP_END (const location_type& l);

    static inline
    symbol_type
    make_OP_PACKED_SWITCHDATABEG (const location_type& l);

    static inline
    symbol_type
    make_OP_PACKED_SWITCHDATAEND (const location_type& l);

    static inline
    symbol_type
    make_SYMBOL_BEGIN (const location_type& l);

    static inline
    symbol_type
    make_COLON (const location_type& l);

    static inline
    symbol_type
    make_LEFTPAR (const location_type& l);

    static inline
    symbol_type
    make_RIGHTPAR (const location_type& l);

    static inline
    symbol_type
    make_COMMA (const location_type& l);

    static inline
    symbol_type
    make_POINT (const location_type& l);

    static inline
    symbol_type
    make_INIBRACE (const location_type& l);

    static inline
    symbol_type
    make_CLOBRACE (const location_type& l);

    static inline
    symbol_type
    make_ELLIPSIS (const location_type& l);

    static inline
    symbol_type
    make_SYMBOL_END (const location_type& l);


    /// Build a parser object.
     Parser  (Analysis::Lexer &lexer_yyarg, Analysis::Interpreter &driver_yyarg);
    virtual ~ Parser  ();

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
     Parser  (const  Parser &);
     Parser & operator= (const  Parser &);

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

    static const short int yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short int yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned short int yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const short int yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short int yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const unsigned short int yytable_[];

  static const short int yycheck_[];

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
      yylast_ = 1008,     ///< Last index in yytable_.
      yynnts_ = 15,  ///< Number of nonterminal symbols.
      yyfinal_ = 2, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 294  ///< Number of tokens.
    };


    // User arguments.
    Analysis::Lexer &lexer;
    Analysis::Interpreter &driver;
  };

  // Symbol number corresponding to token number t.
  inline
   Parser ::token_number_type
   Parser ::yytranslate_ (token_type t)
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
     285,   286,   287,   288,   289,   290,   291,   292,   293
    };
    const unsigned int user_token_number_max_ = 548;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  inline
   Parser ::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
   Parser ::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
   Parser ::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
      switch (other.type_get ())
    {
      case 308: // instruction
        value.copy< OpCode* > (other.value);
        break;

      case 20: // "flag"
      case 21: // "v(p)x"
      case 296: // exp
      case 297: // classdef
      case 298: // superdef
      case 299: // srcdef
      case 300: // fielddef
      case 301: // methoddef
      case 302: // flags
      case 306: // registers
        value.copy< int > (other.value);
        break;

      case 22: // "number"
        value.copy< int64_t > (other.value);
        break;

      case 4: // "c type string"
      case 5: // "name string"
      case 6: // "comment"
      case 7: // "class name"
      case 8: // "class type"
      case 305: // comment
      case 307: // jmplabel
        value.copy< std::string > (other.value);
        break;

      case 304: // regs
        value.copy< std::vector<int> > (other.value);
        break;

      case 303: // args
        value.copy< std::vector<std::string> > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {
    (void) v;
      switch (this->type_get ())
    {
      case 308: // instruction
        value.copy< OpCode* > (v);
        break;

      case 20: // "flag"
      case 21: // "v(p)x"
      case 296: // exp
      case 297: // classdef
      case 298: // superdef
      case 299: // srcdef
      case 300: // fielddef
      case 301: // methoddef
      case 302: // flags
      case 306: // registers
        value.copy< int > (v);
        break;

      case 22: // "number"
        value.copy< int64_t > (v);
        break;

      case 4: // "c type string"
      case 5: // "name string"
      case 6: // "comment"
      case 7: // "class name"
      case 8: // "class type"
      case 305: // comment
      case 307: // jmplabel
        value.copy< std::string > (v);
        break;

      case 304: // regs
        value.copy< std::vector<int> > (v);
        break;

      case 303: // args
        value.copy< std::vector<std::string> > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const OpCode* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const int v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const int64_t v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<int> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<std::string> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  template <typename Base>
  inline
   Parser ::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
   Parser ::basic_symbol<Base>::clear ()
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
      case 308: // instruction
        value.template destroy< OpCode* > ();
        break;

      case 20: // "flag"
      case 21: // "v(p)x"
      case 296: // exp
      case 297: // classdef
      case 298: // superdef
      case 299: // srcdef
      case 300: // fielddef
      case 301: // methoddef
      case 302: // flags
      case 306: // registers
        value.template destroy< int > ();
        break;

      case 22: // "number"
        value.template destroy< int64_t > ();
        break;

      case 4: // "c type string"
      case 5: // "name string"
      case 6: // "comment"
      case 7: // "class name"
      case 8: // "class type"
      case 305: // comment
      case 307: // jmplabel
        value.template destroy< std::string > ();
        break;

      case 304: // regs
        value.template destroy< std::vector<int> > ();
        break;

      case 303: // args
        value.template destroy< std::vector<std::string> > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  inline
  bool
   Parser ::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
   Parser ::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 308: // instruction
        value.move< OpCode* > (s.value);
        break;

      case 20: // "flag"
      case 21: // "v(p)x"
      case 296: // exp
      case 297: // classdef
      case 298: // superdef
      case 299: // srcdef
      case 300: // fielddef
      case 301: // methoddef
      case 302: // flags
      case 306: // registers
        value.move< int > (s.value);
        break;

      case 22: // "number"
        value.move< int64_t > (s.value);
        break;

      case 4: // "c type string"
      case 5: // "name string"
      case 6: // "comment"
      case 7: // "class name"
      case 8: // "class type"
      case 305: // comment
      case 307: // jmplabel
        value.move< std::string > (s.value);
        break;

      case 304: // regs
        value.move< std::vector<int> > (s.value);
        break;

      case 303: // args
        value.move< std::vector<std::string> > (s.value);
        break;

      default:
        break;
    }

    location = s.location;
  }

  // by_type.
  inline
   Parser ::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
   Parser ::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
   Parser ::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
   Parser ::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
   Parser ::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
   Parser ::by_type::type_get () const
  {
    return type;
  }

  inline
   Parser ::token_type
   Parser ::by_type::token () const
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
     545,   546,   547,   548
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }
  // Implementation of make_symbol for each symbol type.
   Parser ::symbol_type
   Parser ::make_END (const location_type& l)
  {
    return symbol_type (token::TOKEN_END, l);
  }

   Parser ::symbol_type
   Parser ::make_EOL (const location_type& l)
  {
    return symbol_type (token::TOKEN_EOL, l);
  }

   Parser ::symbol_type
   Parser ::make_CSTRING (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_CSTRING, v, l);
  }

   Parser ::symbol_type
   Parser ::make_NAMESTRING (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_NAMESTRING, v, l);
  }

   Parser ::symbol_type
   Parser ::make_COMMENT (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_COMMENT, v, l);
  }

   Parser ::symbol_type
   Parser ::make_CLASSNAME (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_CLASSNAME, v, l);
  }

   Parser ::symbol_type
   Parser ::make_CLASSTYPE (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_CLASSTYPE, v, l);
  }

   Parser ::symbol_type
   Parser ::make_KEYWORD_BEGIN (const location_type& l)
  {
    return symbol_type (token::TOKEN_KEYWORD_BEGIN, l);
  }

   Parser ::symbol_type
   Parser ::make_CLASSBEG (const location_type& l)
  {
    return symbol_type (token::TOKEN_CLASSBEG, l);
  }

   Parser ::symbol_type
   Parser ::make_SUPERBEG (const location_type& l)
  {
    return symbol_type (token::TOKEN_SUPERBEG, l);
  }

   Parser ::symbol_type
   Parser ::make_SRCBEG (const location_type& l)
  {
    return symbol_type (token::TOKEN_SRCBEG, l);
  }

   Parser ::symbol_type
   Parser ::make_FIELDBEG (const location_type& l)
  {
    return symbol_type (token::TOKEN_FIELDBEG, l);
  }

   Parser ::symbol_type
   Parser ::make_METHODBEG (const location_type& l)
  {
    return symbol_type (token::TOKEN_METHODBEG, l);
  }

   Parser ::symbol_type
   Parser ::make_METHODEND (const location_type& l)
  {
    return symbol_type (token::TOKEN_METHODEND, l);
  }

   Parser ::symbol_type
   Parser ::make_REGISTERS (const location_type& l)
  {
    return symbol_type (token::TOKEN_REGISTERS, l);
  }

   Parser ::symbol_type
   Parser ::make_PROLOGUE (const location_type& l)
  {
    return symbol_type (token::TOKEN_PROLOGUE, l);
  }

   Parser ::symbol_type
   Parser ::make_LINE (const location_type& l)
  {
    return symbol_type (token::TOKEN_LINE, l);
  }

   Parser ::symbol_type
   Parser ::make_KEYWORD_END (const location_type& l)
  {
    return symbol_type (token::TOKEN_KEYWORD_END, l);
  }

   Parser ::symbol_type
   Parser ::make_FLAG (const int& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_FLAG, v, l);
  }

   Parser ::symbol_type
   Parser ::make_REGD (const int& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_REGD, v, l);
  }

   Parser ::symbol_type
   Parser ::make_NUMBER (const int64_t& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_NUMBER, v, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_BEGIN (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_BEGIN, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_NOP (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_NOP, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_MOVE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_MOVE_FROM16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE_FROM16, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_MOVE_16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE_16, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_MOVE_WIDE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE_WIDE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_MOVE_WIDE_FROM16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE_WIDE_FROM16, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_MOVE_WIDE_16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE_WIDE_16, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_MOVE_OBJECT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE_OBJECT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_MOVE_OBJECT_FROM16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE_OBJECT_FROM16, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_MOVE_OBJECT_16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE_OBJECT_16, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_MOVE_RESULT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE_RESULT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_MOVE_RESULT_WIDE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE_RESULT_WIDE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_MOVE_RESULT_OBJECT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE_RESULT_OBJECT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_MOVE_EXCEPTION (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MOVE_EXCEPTION, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_RETURN_VOID (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_RETURN_VOID, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_RETURN (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_RETURN, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_RETURN_WIDE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_RETURN_WIDE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_RETURN_OBJECT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_RETURN_OBJECT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_CONST_4 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CONST_4, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_CONST_16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CONST_16, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_CONST (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CONST, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_CONST_HIGH16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CONST_HIGH16, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_CONST_WIDE_16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CONST_WIDE_16, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_CONST_WIDE_32 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CONST_WIDE_32, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_CONST_WIDE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CONST_WIDE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_CONST_WIDE_HIGH16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CONST_WIDE_HIGH16, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_CONST_STRING (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CONST_STRING, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_CONST_STRING_JUMBO (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CONST_STRING_JUMBO, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_CONST_CLASS (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CONST_CLASS, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_MONITOR_ENTER (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MONITOR_ENTER, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_MONITOR_EXIT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MONITOR_EXIT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_CHECK_CAST (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CHECK_CAST, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_INSTANCE_OF (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INSTANCE_OF, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_ARRAY_LENGTH (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_ARRAY_LENGTH, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_NEW_INSTANCE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_NEW_INSTANCE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_NEW_ARRAY (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_NEW_ARRAY, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_FILLED_NEW_ARRAY (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_FILLED_NEW_ARRAY, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_FILLED_NEW_ARRAY_RANGE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_FILLED_NEW_ARRAY_RANGE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_FILL_ARRAY_DATA (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_FILL_ARRAY_DATA, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_THROW (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_THROW, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_GOTO (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_GOTO, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_GOTO_16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_GOTO_16, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_GOTO_32 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_GOTO_32, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_PACKED_SWITCH (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_PACKED_SWITCH, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SPARSE_SWITCH (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SPARSE_SWITCH, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_CMPL_FLOAT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CMPL_FLOAT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_CMPG_FLOAT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CMPG_FLOAT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_CMPL_DOUBLE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CMPL_DOUBLE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_CMPG_DOUBLE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CMPG_DOUBLE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_CMP_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CMP_LONG, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IF_EQ (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IF_EQ, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IF_NE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IF_NE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IF_LT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IF_LT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IF_GE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IF_GE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IF_GT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IF_GT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IF_LE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IF_LE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IF_EQZ (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IF_EQZ, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IF_NEZ (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IF_NEZ, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IF_LTZ (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IF_LTZ, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IF_GEZ (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IF_GEZ, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IF_GTZ (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IF_GTZ, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IF_LEZ (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IF_LEZ, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_UNUSED_3E (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_UNUSED_3E, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_UNUSED_3F (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_UNUSED_3F, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_UNUSED_40 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_UNUSED_40, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_UNUSED_41 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_UNUSED_41, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_UNUSED_42 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_UNUSED_42, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_UNUSED_43 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_UNUSED_43, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_AGET (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AGET, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_AGET_WIDE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AGET_WIDE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_AGET_OBJECT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AGET_OBJECT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_AGET_BOOLEAN (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AGET_BOOLEAN, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_AGET_BYTE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AGET_BYTE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_AGET_CHAR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AGET_CHAR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_AGET_SHORT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AGET_SHORT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_APUT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_APUT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_APUT_WIDE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_APUT_WIDE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_APUT_OBJECT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_APUT_OBJECT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_APUT_BOOLEAN (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_APUT_BOOLEAN, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_APUT_BYTE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_APUT_BYTE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_APUT_CHAR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_APUT_CHAR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_APUT_SHORT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_APUT_SHORT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IGET (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IGET_WIDE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET_WIDE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IGET_OBJECT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET_OBJECT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IGET_BOOLEAN (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET_BOOLEAN, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IGET_BYTE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET_BYTE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IGET_CHAR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET_CHAR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IGET_SHORT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET_SHORT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IPUT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IPUT_WIDE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT_WIDE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IPUT_OBJECT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT_OBJECT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IPUT_BOOLEAN (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT_BOOLEAN, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IPUT_BYTE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT_BYTE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IPUT_CHAR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT_CHAR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IPUT_SHORT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT_SHORT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SGET (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SGET, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SGET_WIDE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SGET_WIDE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SGET_OBJECT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SGET_OBJECT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SGET_BOOLEAN (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SGET_BOOLEAN, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SGET_BYTE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SGET_BYTE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SGET_CHAR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SGET_CHAR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SGET_SHORT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SGET_SHORT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SPUT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SPUT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SPUT_WIDE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SPUT_WIDE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SPUT_OBJECT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SPUT_OBJECT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SPUT_BOOLEAN (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SPUT_BOOLEAN, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SPUT_BYTE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SPUT_BYTE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SPUT_CHAR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SPUT_CHAR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SPUT_SHORT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SPUT_SHORT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_INVOKE_VIRTUAL (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_VIRTUAL, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_INVOKE_SUPER (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_SUPER, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_INVOKE_DIRECT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_DIRECT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_INVOKE_STATIC (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_STATIC, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_INVOKE_INTERFACE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_INTERFACE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_UNUSED_73 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_UNUSED_73, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_INVOKE_VIRTUAL_RANGE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_VIRTUAL_RANGE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_INVOKE_SUPER_RANGE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_SUPER_RANGE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_INVOKE_DIRECT_RANGE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_DIRECT_RANGE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_INVOKE_STATIC_RANGE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_STATIC_RANGE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_INVOKE_INTERFACE_RANGE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_INTERFACE_RANGE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_UNUSED_79 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_UNUSED_79, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_UNUSED_7A (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_UNUSED_7A, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_NEG_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_NEG_INT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_NOT_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_NOT_INT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_NEG_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_NEG_LONG, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_NOT_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_NOT_LONG, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_NEG_FLOAT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_NEG_FLOAT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_NEG_DOUBLE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_NEG_DOUBLE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_INT_TO_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INT_TO_LONG, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_INT_TO_FLOAT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INT_TO_FLOAT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_INT_TO_DOUBLE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INT_TO_DOUBLE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_LONG_TO_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_LONG_TO_INT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_LONG_TO_FLOAT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_LONG_TO_FLOAT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_LONG_TO_DOUBLE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_LONG_TO_DOUBLE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_FLOAT_TO_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_FLOAT_TO_INT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_FLOAT_TO_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_FLOAT_TO_LONG, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_FLOAT_TO_DOUBLE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_FLOAT_TO_DOUBLE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_DOUBLE_TO_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DOUBLE_TO_INT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_DOUBLE_TO_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DOUBLE_TO_LONG, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_DOUBLE_TO_FLOAT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DOUBLE_TO_FLOAT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_INT_TO_BYTE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INT_TO_BYTE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_INT_TO_CHAR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INT_TO_CHAR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_INT_TO_SHORT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INT_TO_SHORT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_ADD_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_ADD_INT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SUB_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SUB_INT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_MUL_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MUL_INT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_DIV_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DIV_INT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_REM_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_REM_INT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_AND_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AND_INT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_OR_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_OR_INT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_XOR_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_XOR_INT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SHL_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SHL_INT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SHR_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SHR_INT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_USHR_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_USHR_INT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_ADD_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_ADD_LONG, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SUB_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SUB_LONG, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_MUL_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MUL_LONG, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_DIV_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DIV_LONG, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_REM_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_REM_LONG, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_AND_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AND_LONG, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_OR_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_OR_LONG, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_XOR_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_XOR_LONG, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SHL_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SHL_LONG, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SHR_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SHR_LONG, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_USHR_LONG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_USHR_LONG, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_ADD_FLOAT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_ADD_FLOAT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SUB_FLOAT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SUB_FLOAT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_MUL_FLOAT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MUL_FLOAT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_DIV_FLOAT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DIV_FLOAT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_REM_FLOAT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_REM_FLOAT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_ADD_DOUBLE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_ADD_DOUBLE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SUB_DOUBLE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SUB_DOUBLE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_MUL_DOUBLE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MUL_DOUBLE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_DIV_DOUBLE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DIV_DOUBLE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_REM_DOUBLE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_REM_DOUBLE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_ADD_INT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_ADD_INT_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SUB_INT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SUB_INT_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_MUL_INT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MUL_INT_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_DIV_INT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DIV_INT_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_REM_INT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_REM_INT_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_AND_INT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AND_INT_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_OR_INT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_OR_INT_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_XOR_INT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_XOR_INT_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SHL_INT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SHL_INT_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SHR_INT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SHR_INT_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_USHR_INT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_USHR_INT_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_ADD_LONG_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_ADD_LONG_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SUB_LONG_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SUB_LONG_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_MUL_LONG_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MUL_LONG_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_DIV_LONG_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DIV_LONG_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_REM_LONG_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_REM_LONG_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_AND_LONG_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AND_LONG_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_OR_LONG_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_OR_LONG_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_XOR_LONG_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_XOR_LONG_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SHL_LONG_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SHL_LONG_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SHR_LONG_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SHR_LONG_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_USHR_LONG_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_USHR_LONG_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_ADD_FLOAT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_ADD_FLOAT_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SUB_FLOAT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SUB_FLOAT_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_MUL_FLOAT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MUL_FLOAT_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_DIV_FLOAT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DIV_FLOAT_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_REM_FLOAT_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_REM_FLOAT_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_ADD_DOUBLE_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_ADD_DOUBLE_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SUB_DOUBLE_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SUB_DOUBLE_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_MUL_DOUBLE_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MUL_DOUBLE_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_DIV_DOUBLE_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DIV_DOUBLE_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_REM_DOUBLE_2ADDR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_REM_DOUBLE_2ADDR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_ADD_INT_LIT16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_ADD_INT_LIT16, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_RSUB_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_RSUB_INT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_MUL_INT_LIT16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MUL_INT_LIT16, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_DIV_INT_LIT16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DIV_INT_LIT16, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_REM_INT_LIT16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_REM_INT_LIT16, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_AND_INT_LIT16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AND_INT_LIT16, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_OR_INT_LIT16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_OR_INT_LIT16, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_XOR_INT_LIT16 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_XOR_INT_LIT16, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_ADD_INT_LIT8 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_ADD_INT_LIT8, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_RSUB_INT_LIT8 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_RSUB_INT_LIT8, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_MUL_INT_LIT8 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_MUL_INT_LIT8, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_DIV_INT_LIT8 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_DIV_INT_LIT8, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_REM_INT_LIT8 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_REM_INT_LIT8, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_AND_INT_LIT8 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_AND_INT_LIT8, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_OR_INT_LIT8 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_OR_INT_LIT8, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_XOR_INT_LIT8 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_XOR_INT_LIT8, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SHL_INT_LIT8 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SHL_INT_LIT8, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SHR_INT_LIT8 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SHR_INT_LIT8, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_USHR_INT_LIT8 (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_USHR_INT_LIT8, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IGET_VOLATILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET_VOLATILE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IPUT_VOLATILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT_VOLATILE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SGET_VOLATILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SGET_VOLATILE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SPUT_VOLATILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SPUT_VOLATILE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IGET_OBJECT_VOLATILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET_OBJECT_VOLATILE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IGET_WIDE_VOLATILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET_WIDE_VOLATILE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IPUT_WIDE_VOLATILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT_WIDE_VOLATILE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SGET_WIDE_VOLATILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SGET_WIDE_VOLATILE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SPUT_WIDE_VOLATILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SPUT_WIDE_VOLATILE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_BREAKPOINT (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_BREAKPOINT, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_THROW_VERIFICATION_ERROR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_THROW_VERIFICATION_ERROR, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_EXECUTE_INLINE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_EXECUTE_INLINE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_EXECUTE_INLINE_RANGE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_EXECUTE_INLINE_RANGE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_INVOKE_OBJECT_INIT_RANGE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_OBJECT_INIT_RANGE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_RETURN_VOID_BARRIER (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_RETURN_VOID_BARRIER, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IGET_QUICK (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET_QUICK, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IGET_WIDE_QUICK (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET_WIDE_QUICK, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IGET_OBJECT_QUICK (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IGET_OBJECT_QUICK, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IPUT_QUICK (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT_QUICK, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IPUT_WIDE_QUICK (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT_WIDE_QUICK, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IPUT_OBJECT_QUICK (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT_OBJECT_QUICK, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_INVOKE_VIRTUAL_QUICK (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_VIRTUAL_QUICK, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_INVOKE_VIRTUAL_QUICK_RANGE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_VIRTUAL_QUICK_RANGE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_INVOKE_SUPER_QUICK (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_SUPER_QUICK, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_INVOKE_SUPER_QUICK_RANGE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_INVOKE_SUPER_QUICK_RANGE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_IPUT_OBJECT_VOLATILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_IPUT_OBJECT_VOLATILE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SGET_OBJECT_VOLATILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SGET_OBJECT_VOLATILE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_SPUT_OBJECT_VOLATILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_SPUT_OBJECT_VOLATILE, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_UNUSED_FF (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_UNUSED_FF, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_CATCH (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_CATCH, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_END (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_END, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_PACKED_SWITCHDATABEG (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_PACKED_SWITCHDATABEG, l);
  }

   Parser ::symbol_type
   Parser ::make_OP_PACKED_SWITCHDATAEND (const location_type& l)
  {
    return symbol_type (token::TOKEN_OP_PACKED_SWITCHDATAEND, l);
  }

   Parser ::symbol_type
   Parser ::make_SYMBOL_BEGIN (const location_type& l)
  {
    return symbol_type (token::TOKEN_SYMBOL_BEGIN, l);
  }

   Parser ::symbol_type
   Parser ::make_COLON (const location_type& l)
  {
    return symbol_type (token::TOKEN_COLON, l);
  }

   Parser ::symbol_type
   Parser ::make_LEFTPAR (const location_type& l)
  {
    return symbol_type (token::TOKEN_LEFTPAR, l);
  }

   Parser ::symbol_type
   Parser ::make_RIGHTPAR (const location_type& l)
  {
    return symbol_type (token::TOKEN_RIGHTPAR, l);
  }

   Parser ::symbol_type
   Parser ::make_COMMA (const location_type& l)
  {
    return symbol_type (token::TOKEN_COMMA, l);
  }

   Parser ::symbol_type
   Parser ::make_POINT (const location_type& l)
  {
    return symbol_type (token::TOKEN_POINT, l);
  }

   Parser ::symbol_type
   Parser ::make_INIBRACE (const location_type& l)
  {
    return symbol_type (token::TOKEN_INIBRACE, l);
  }

   Parser ::symbol_type
   Parser ::make_CLOBRACE (const location_type& l)
  {
    return symbol_type (token::TOKEN_CLOBRACE, l);
  }

   Parser ::symbol_type
   Parser ::make_ELLIPSIS (const location_type& l)
  {
    return symbol_type (token::TOKEN_ELLIPSIS, l);
  }

   Parser ::symbol_type
   Parser ::make_SYMBOL_END (const location_type& l)
  {
    return symbol_type (token::TOKEN_SYMBOL_END, l);
  }


#line 9 "Parser.yy" // lalr1.cc:377
} //  Analysis 
#line 4387 "Parser.hpp" // lalr1.cc:377




#endif // !YY_YY_PARSER_HPP_INCLUDED
