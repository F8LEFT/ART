// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

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
// //                    "%code top" blocks.
#line 41 "SmaliParser.yy" // lalr1.cc:397

    #include <iostream>
    #include "SmaliParser.hpp"
    #include "location.hh"
    #include "Interpreter.h"
    #include "SmaliLexer.h"
    #include "utils/Defs.h"

    static Analysis::SmaliParser::symbol_type yylex(Analysis::SmaliLexer &lexer
                                    , Analysis::Interpreter &driver ) {
        return lexer.get_next_token();
    }
    using namespace std;
    using namespace Analysis;

#line 50 "SmaliParser.cpp" // lalr1.cc:397


// First part of user declarations.

#line 55 "SmaliParser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "SmaliParser.hpp"

// User implementation prologue.

#line 69 "SmaliParser.cpp" // lalr1.cc:412


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 9 "SmaliParser.yy" // lalr1.cc:479
namespace  Analysis  {
#line 155 "SmaliParser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
   SmaliParser ::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
   SmaliParser :: SmaliParser  (Analysis::SmaliLexer &lexer_yyarg, Analysis::Interpreter &driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      lexer (lexer_yyarg),
      driver (driver_yyarg)
  {}

   SmaliParser ::~ SmaliParser  ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
   SmaliParser ::by_state::by_state ()
    : state (empty_state)
  {}

  inline
   SmaliParser ::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
   SmaliParser ::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
   SmaliParser ::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
   SmaliParser ::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
   SmaliParser ::symbol_number_type
   SmaliParser ::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
   SmaliParser ::stack_symbol_type::stack_symbol_type ()
  {}


  inline
   SmaliParser ::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 365: // instruction
        value.move< OpCode* > (that.value);
        break;

      case 48: // "true|false"
      case 51: // "flag"
      case 52: // "v(p)x"
      case 348: // exp
      case 349: // classdef
      case 350: // superdef
      case 351: // srcdef
      case 352: // fielddef
      case 353: // methoddef
      case 354: // flags
      case 361: // registers
        value.move< int > (that.value);
        break;

      case 341: // "integer"
      case 363: // integer
        value.move< long long int > (that.value);
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
      case 54: // "ZBSCIJFDLIT"
      case 55: // "ZBSCIJFD"
      case 56: // "Lxxx;"
      case 57: // "[["
      case 60: // "simple name"
      case 61: // "member name"
      case 62: // "string"
      case 63: // "char"
      case 65: // "build runtime system"
      case 66: // "ver type error"
      case 67: // "inline@0x"
      case 68: // "vtable@0x"
      case 69: // "field@0x"
      case 71: // "# comments"
      case 342: // "classtype"
      case 343: // "[classtype"
      case 344: // "field or class name"
      case 345: // "integer-str"
      case 355: // namestring
      case 356: // classtype
      case 357: // classtypeOrArray
      case 360: // comment
      case 362: // jmplabel
      case 364: // INTEGER_LITERAL
        value.move< std::string > (that.value);
        break;

      case 359: // regs
        value.move< std::vector<int> > (that.value);
        break;

      case 358: // args
        value.move< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
   SmaliParser ::stack_symbol_type&
   SmaliParser ::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 365: // instruction
        value.copy< OpCode* > (that.value);
        break;

      case 48: // "true|false"
      case 51: // "flag"
      case 52: // "v(p)x"
      case 348: // exp
      case 349: // classdef
      case 350: // superdef
      case 351: // srcdef
      case 352: // fielddef
      case 353: // methoddef
      case 354: // flags
      case 361: // registers
        value.copy< int > (that.value);
        break;

      case 341: // "integer"
      case 363: // integer
        value.copy< long long int > (that.value);
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
      case 54: // "ZBSCIJFDLIT"
      case 55: // "ZBSCIJFD"
      case 56: // "Lxxx;"
      case 57: // "[["
      case 60: // "simple name"
      case 61: // "member name"
      case 62: // "string"
      case 63: // "char"
      case 65: // "build runtime system"
      case 66: // "ver type error"
      case 67: // "inline@0x"
      case 68: // "vtable@0x"
      case 69: // "field@0x"
      case 71: // "# comments"
      case 342: // "classtype"
      case 343: // "[classtype"
      case 344: // "field or class name"
      case 345: // "integer-str"
      case 355: // namestring
      case 356: // classtype
      case 357: // classtypeOrArray
      case 360: // comment
      case 362: // jmplabel
      case 364: // INTEGER_LITERAL
        value.copy< std::string > (that.value);
        break;

      case 359: // regs
        value.copy< std::vector<int> > (that.value);
        break;

      case 358: // args
        value.copy< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
   SmaliParser ::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
   SmaliParser ::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
   SmaliParser ::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
   SmaliParser ::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
   SmaliParser ::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
   SmaliParser ::debug_stream () const
  {
    return *yycdebug_;
  }

  void
   SmaliParser ::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


   SmaliParser ::debug_level_type
   SmaliParser ::debug_level () const
  {
    return yydebug_;
  }

  void
   SmaliParser ::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline  SmaliParser ::state_type
   SmaliParser ::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
   SmaliParser ::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
   SmaliParser ::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
   SmaliParser ::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (lexer, driver));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 365: // instruction
        yylhs.value.build< OpCode* > ();
        break;

      case 48: // "true|false"
      case 51: // "flag"
      case 52: // "v(p)x"
      case 348: // exp
      case 349: // classdef
      case 350: // superdef
      case 351: // srcdef
      case 352: // fielddef
      case 353: // methoddef
      case 354: // flags
      case 361: // registers
        yylhs.value.build< int > ();
        break;

      case 341: // "integer"
      case 363: // integer
        yylhs.value.build< long long int > ();
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
      case 54: // "ZBSCIJFDLIT"
      case 55: // "ZBSCIJFD"
      case 56: // "Lxxx;"
      case 57: // "[["
      case 60: // "simple name"
      case 61: // "member name"
      case 62: // "string"
      case 63: // "char"
      case 65: // "build runtime system"
      case 66: // "ver type error"
      case 67: // "inline@0x"
      case 68: // "vtable@0x"
      case 69: // "field@0x"
      case 71: // "# comments"
      case 342: // "classtype"
      case 343: // "[classtype"
      case 344: // "field or class name"
      case 345: // "integer-str"
      case 355: // namestring
      case 356: // classtype
      case 357: // classtypeOrArray
      case 360: // comment
      case 362: // jmplabel
      case 364: // INTEGER_LITERAL
        yylhs.value.build< std::string > ();
        break;

      case 359: // regs
        yylhs.value.build< std::vector<int> > ();
        break;

      case 358: // args
        yylhs.value.build< std::vector<std::string> > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 6:
#line 459 "SmaliParser.yy" // lalr1.cc:859
    {yyerrok; driver.mLexer->yyBegin(0);}
#line 735 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 468 "SmaliParser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 1; driver.addOpcode(yystack_[0].value.as< OpCode* > ());}
#line 741 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 469 "SmaliParser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 1; driver.endMethod();}
#line 747 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 473 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 1;
        driver.setClassDefine(yystack_[1].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 755 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 477 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 1;
        driver.setSuperDefine(yystack_[0].value.as< std::string > ());
    }
#line 763 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 481 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 1;
        driver.setSourceDefine(yystack_[0].value.as< std::string > ());
    }
#line 771 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 485 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 1;
        driver.addField(yystack_[2].value.as< std::string > (), yystack_[3].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 779 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 489 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 1;
        driver.addMethod(yystack_[4].value.as< std::string > (), yystack_[5].value.as< int > (), yystack_[0].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > ());
    }
#line 787 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 493 "SmaliParser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 0;}
#line 793 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 494 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< int > () = yystack_[0].value.as< int > ();
    }
#line 801 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 497 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< int > () = yystack_[1].value.as< int > ();
        yylhs.value.as< int > () |= yystack_[0].value.as< int > ();
    }
#line 810 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 504 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 816 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 505 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 822 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 509 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 828 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 510 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 834 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 511 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 840 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 512 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "V"; }
#line 846 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 516 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 852 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 517 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[1].value.as< std::string > () + yystack_[0].value.as< std::string > (); }
#line 858 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 521 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();}
#line 864 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 522 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();
        yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
    }
#line 873 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 526 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::vector<std::string> > () = yystack_[1].value.as< std::vector<std::string> > ();
        yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
    }
#line 882 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 532 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<int> > () = std::vector<int>();}
#line 888 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 533 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::vector<int> > () = std::vector<int>();
        yylhs.value.as< std::vector<int> > ().push_back(yystack_[0].value.as< int > ());
    }
#line 897 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 537 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::vector<int> > () = yystack_[2].value.as< std::vector<int> > ();
        yylhs.value.as< std::vector<int> > ().push_back(yystack_[0].value.as< int > ());
    }
#line 906 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 543 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();
    }
#line 914 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 549 "SmaliParser.yy" // lalr1.cc:859
    {
        driver.setCurMethodRegSize(yystack_[0].value.as< long long int > ());
     }
#line 922 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 552 "SmaliParser.yy" // lalr1.cc:859
    {
        // TODO Register size should be integer + argsize
        driver.setCurMethodRegSize(yystack_[0].value.as< long long int > ());
     }
#line 931 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 559 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();
    }
#line 939 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 563 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< long long int > () = driver.parseLongInt(yystack_[0].value.as< std::string > ());
     }
#line 947 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 566 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< long long int > () = driver.parseLongInt(yystack_[0].value.as< std::string > ());
     }
#line 955 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 569 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< long long int > () = driver.parseLongInt(yystack_[0].value.as< std::string > ());
     }
#line 963 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 572 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< long long int > () = driver.parseLongInt(yystack_[0].value.as< std::string > ());
     }
#line 971 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 575 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< long long int > () = driver.parseLongInt(yystack_[0].value.as< std::string > ());
     }
#line 979 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 581 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 985 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 582 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 991 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 587 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NOP(OP_NOP, driver.stringPool());
    }
#line 999 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 590 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1007 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 593 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_FROM16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1015 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 596 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1023 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 599 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_WIDE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1031 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 602 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_WIDE_FROM16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1039 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 605 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_WIDE_16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1047 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 608 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_OBJECT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1055 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 611 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_OBJECT_FROM16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1063 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 614 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_OBJECT_16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1071 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 617 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_MOVE_RESULT(OP_MOVE_RESULT, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1079 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 620 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_MOVE_RESULT(OP_MOVE_RESULT_WIDE, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1087 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 623 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_MOVE_RESULT(OP_MOVE_RESULT_OBJECT, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1095 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 626 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE_EXCEPTION(OP_MOVE_EXCEPTION, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1103 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 629 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_RETURN_VOID(OP_RETURN_VOID, driver.stringPool());
    }
#line 1111 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 632 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_RETURN(OP_RETURN, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1119 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 635 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_RETURN(OP_RETURN_WIDE, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1127 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 638 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_RETURN(OP_RETURN_OBJECT, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1135 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 641 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_4, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 1143 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 644 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 1151 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 647 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 1159 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 650 "SmaliParser.yy" // lalr1.cc:859
    {
        auto number = yystack_[0].value.as< std::string > ().substr (0, yystack_[0].value.as< std::string > ().length () - 4);
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_HIGH16, driver.stringPool(), yystack_[2].value.as< int > (),
                         strtoll(number.c_str(), 0, 16));

    }
#line 1170 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 656 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_WIDE_16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 1178 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 659 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_WIDE_32, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 1186 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 662 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_WIDE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 1194 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 665 "SmaliParser.yy" // lalr1.cc:859
    {
        auto number = yystack_[0].value.as< std::string > ().substr (0, yystack_[0].value.as< std::string > ().length () - 13);
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_WIDE_HIGH16, driver.stringPool(), yystack_[2].value.as< int > (),
                        strtoll(number.c_str(), 0, 16));
    }
#line 1204 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 670 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CONST_STRING(OP_CONST_STRING, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1212 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 673 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CONST_STRING(OP_CONST_STRING_JUMBO, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1220 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 676 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CONST_CLASS(OP_CONST_CLASS, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1228 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 679 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MONITOR(OP_MONITOR_ENTER, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1236 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 682 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MONITOR(OP_MONITOR_EXIT, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1244 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 685 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CHECK_CAST(OP_CHECK_CAST, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1252 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 688 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INSTANCE_OF(OP_INSTANCE_OF, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
   }
#line 1260 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 691 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_ARRAY_LENGTH(OP_ARRAY_LENGTH, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1268 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 694 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_NEW_INSTANCE(OP_NEW_INSTANCE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1276 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 697 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEW_ARRAY(OP_NEW_ARRAY, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1284 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 700 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_FILLED_NEW_ARRAY(OP_FILLED_NEW_ARRAY, driver.stringPool(), yystack_[3].value.as< std::vector<int> > (), yystack_[0].value.as< std::string > ());
    }
#line 1292 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 703 "SmaliParser.yy" // lalr1.cc:859
    {
       std::vector<int> regs;
       regs.push_back(yystack_[5].value.as< int > ());
       regs.push_back(yystack_[3].value.as< int > ());
       yylhs.value.as< OpCode* > () = new Op_FILLED_NEW_ARRAY(OP_FILLED_NEW_ARRAY_RANGE, driver.stringPool(), regs, yystack_[0].value.as< std::string > ());
    }
#line 1303 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 709 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_FILL_ARRAY_DATA(OP_FILL_ARRAY_DATA, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1311 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 712 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_THROW(OP_THROW, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1319 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 715 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_GOTO(OP_GOTO, driver.stringPool(), yystack_[0].value.as< std::string > ());
    }
#line 1327 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 718 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_GOTO(OP_GOTO_16, driver.stringPool(), yystack_[0].value.as< std::string > ());
    }
#line 1335 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 721 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_GOTO(OP_GOTO_32, driver.stringPool(), yystack_[0].value.as< std::string > ());
    }
#line 1343 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 724 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_SWITCH(OP_PACKED_SWITCH, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1351 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 727 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_SWITCH(OP_SPARSE_SWITCH, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1359 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 730 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CMP(OP_CMPL_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1367 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 733 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CMP(OP_CMPG_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1375 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 736 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CMP(OP_CMPL_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1383 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 739 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CMP(OP_CMPG_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1391 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 742 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CMP(OP_CMP_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1399 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 745 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_EQ, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1407 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 748 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_NE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1415 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 751 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_LT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1423 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 754 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_GE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1431 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 757 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_GT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1439 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 760 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_LE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1447 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 763 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_EQZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1455 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 766 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_NEZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1463 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 769 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_LTZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1471 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 772 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_GEZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1479 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 775 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_GTZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1487 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 778 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_LEZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1495 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 787 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1503 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 790 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_WIDE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1511 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 793 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_OBJECT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1519 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 796 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_BOOLEAN, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1527 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 799 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_BYTE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1535 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 802 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_CHAR, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1543 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 805 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_SHORT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1551 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 808 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1559 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 811 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT_WIDE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1567 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 814 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT_OBJECT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1575 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 817 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT_BOOLEAN, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1583 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 820 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT_BYTE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1591 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 823 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT_CHAR, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1599 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 826 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT_SHORT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1607 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 829 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1615 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 832 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET_WIDE, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1623 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 835 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET_OBJECT, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1631 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 838 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET_BOOLEAN, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1639 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 841 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET_BYTE, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1647 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 844 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET_CHAR, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1655 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 847 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET_SHORT, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1663 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 850 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1671 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 853 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT_WIDE, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1679 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 856 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT_OBJECT, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1687 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 859 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT_BOOLEAN, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1695 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 862 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT_BYTE, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1703 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 865 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT_CHAR, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1711 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 868 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT_SHORT, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1719 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 871 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1727 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 874 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_WIDE, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1735 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 877 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_OBJECT, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1743 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 880 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_BOOLEAN, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1751 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 883 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_BYTE, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1759 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 886 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_CHAR, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1767 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 889 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_SHORT, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1775 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 892 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1783 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 895 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_WIDE, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1791 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 898 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_OBJECT, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1799 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 901 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_BOOLEAN, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1807 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 904 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_BYTE, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1815 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 907 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_CHAR, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1823 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 910 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_SHORT, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1831 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 913 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE(OP_INVOKE_VIRTUAL, driver.stringPool(), yystack_[9].value.as< std::vector<int> > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1839 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 916 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE(OP_INVOKE_SUPER, driver.stringPool(), yystack_[9].value.as< std::vector<int> > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1847 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 919 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE(OP_INVOKE_DIRECT, driver.stringPool(), yystack_[9].value.as< std::vector<int> > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1855 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 922 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE(OP_INVOKE_STATIC, driver.stringPool(), yystack_[9].value.as< std::vector<int> > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1863 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 925 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE(OP_INVOKE_INTERFACE, driver.stringPool(), yystack_[9].value.as< std::vector<int> > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1871 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 929 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE_X_RANGE(OP_INVOKE_VIRTUAL_RANGE, driver.stringPool(), yystack_[11].value.as< int > (), yystack_[9].value.as< int > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1879 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 932 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE_X_RANGE(OP_INVOKE_SUPER_RANGE, driver.stringPool(), yystack_[11].value.as< int > (), yystack_[9].value.as< int > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1887 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 935 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE_X_RANGE(OP_INVOKE_DIRECT_RANGE, driver.stringPool(), yystack_[11].value.as< int > (), yystack_[9].value.as< int > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1895 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 938 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE_X_RANGE(OP_INVOKE_STATIC_RANGE, driver.stringPool(), yystack_[11].value.as< int > (), yystack_[9].value.as< int > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1903 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 941 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE_X_RANGE(OP_INVOKE_INTERFACE_RANGE, driver.stringPool(), yystack_[11].value.as< int > (), yystack_[9].value.as< int > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1911 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 946 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEGNOT_X(OP_NEG_INT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1919 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 949 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEGNOT_X(OP_NOT_INT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1927 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 952 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEGNOT_X(OP_NEG_LONG, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1935 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 955 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEGNOT_X(OP_NOT_LONG, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1943 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 958 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEGNOT_X(OP_NEG_FLOAT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1951 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 961 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEGNOT_X(OP_NEG_DOUBLE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1959 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 964 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_INT_TO_LONG, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1967 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 967 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_INT_TO_FLOAT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1975 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 970 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_INT_TO_DOUBLE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1983 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 973 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_LONG_TO_INT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1991 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 181:
#line 976 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_LONG_TO_FLOAT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1999 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 182:
#line 979 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_LONG_TO_DOUBLE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2007 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 183:
#line 982 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_FLOAT_TO_INT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2015 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 184:
#line 985 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_FLOAT_TO_LONG, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2023 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 185:
#line 988 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_FLOAT_TO_DOUBLE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2031 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 186:
#line 991 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_DOUBLE_TO_INT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2039 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 187:
#line 994 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_DOUBLE_TO_LONG, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2047 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 188:
#line 997 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_DOUBLE_TO_FLOAT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2055 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 189:
#line 1000 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_INT_TO_BYTE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2063 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 190:
#line 1003 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_INT_TO_CHAR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2071 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 191:
#line 1006 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_INT_TO_SHORT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2079 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 192:
#line 1009 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_ADD_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2087 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 193:
#line 1012 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_SUB_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2095 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 194:
#line 1015 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_MUL_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2103 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 195:
#line 1018 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_DIV_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2111 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 196:
#line 1021 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_REM_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2119 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 197:
#line 1024 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_AND_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2127 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 198:
#line 1027 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_OR_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2135 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 199:
#line 1030 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_XOR_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2143 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 200:
#line 1033 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_SHL_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2151 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 201:
#line 1036 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_SHR_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2159 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 202:
#line 1039 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_USHR_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2167 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 203:
#line 1042 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_ADD_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2175 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 204:
#line 1045 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_SUB_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2183 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 205:
#line 1048 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_MUL_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2191 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 206:
#line 1051 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_DIV_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2199 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 207:
#line 1054 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_REM_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2207 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 208:
#line 1057 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_AND_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2215 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 209:
#line 1060 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_OR_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2223 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 210:
#line 1063 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_XOR_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2231 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 211:
#line 1066 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_SHL_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2239 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 212:
#line 1069 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_SHR_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2247 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 213:
#line 1072 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_USHR_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2255 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 214:
#line 1075 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT(OP_ADD_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2263 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 215:
#line 1078 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT(OP_SUB_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2271 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 216:
#line 1081 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT(OP_MUL_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2279 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 217:
#line 1084 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT(OP_DIV_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2287 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 218:
#line 1087 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT(OP_REM_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2295 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 219:
#line 1090 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE(OP_ADD_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2303 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 220:
#line 1093 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE(OP_SUB_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2311 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 221:
#line 1096 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE(OP_MUL_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2319 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 222:
#line 1099 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE(OP_DIV_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2327 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 223:
#line 1102 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE(OP_REM_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2335 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 224:
#line 1105 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_ADD_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2343 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 225:
#line 1108 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_SUB_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2351 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 226:
#line 1111 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_MUL_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2359 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 227:
#line 1114 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_DIV_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2367 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 228:
#line 1117 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_REM_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2375 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 229:
#line 1120 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_AND_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2383 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 230:
#line 1123 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_OR_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2391 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 231:
#line 1126 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_XOR_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2399 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 232:
#line 1129 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_SHL_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2407 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 233:
#line 1132 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_SHR_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2415 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 234:
#line 1135 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_USHR_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2423 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 235:
#line 1138 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_ADD_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2431 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 236:
#line 1141 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_SUB_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2439 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 237:
#line 1144 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_MUL_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2447 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 238:
#line 1147 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_DIV_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2455 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 239:
#line 1150 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_REM_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2463 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 240:
#line 1153 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_AND_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2471 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 241:
#line 1156 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_OR_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2479 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 242:
#line 1159 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_XOR_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2487 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 243:
#line 1162 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_SHL_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2495 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 244:
#line 1165 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_SHR_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2503 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 245:
#line 1168 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_USHR_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2511 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 246:
#line 1171 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT_2ADDR(OP_ADD_FLOAT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2519 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 247:
#line 1174 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT_2ADDR(OP_SUB_FLOAT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2527 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 248:
#line 1177 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT_2ADDR(OP_MUL_FLOAT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2535 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 249:
#line 1180 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT_2ADDR(OP_DIV_FLOAT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2543 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 250:
#line 1183 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT_2ADDR(OP_REM_FLOAT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2551 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 251:
#line 1186 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE_2ADDR(OP_ADD_DOUBLE_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2559 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 252:
#line 1189 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE_2ADDR(OP_SUB_DOUBLE_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2567 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 253:
#line 1192 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE_2ADDR(OP_MUL_DOUBLE_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2575 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 254:
#line 1195 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE_2ADDR(OP_DIV_DOUBLE_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2583 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 255:
#line 1198 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE_2ADDR(OP_REM_DOUBLE_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2591 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 256:
#line 1201 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_ADD_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2599 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 257:
#line 1204 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_RSUB_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2607 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 258:
#line 1207 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_MUL_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2615 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 259:
#line 1210 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_DIV_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2623 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 260:
#line 1213 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_REM_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2631 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 261:
#line 1216 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_AND_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2639 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 262:
#line 1219 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_OR_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2647 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 263:
#line 1222 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_XOR_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2655 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 264:
#line 1225 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_ADD_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2663 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 265:
#line 1228 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_RSUB_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2671 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 266:
#line 1231 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_MUL_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2679 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 267:
#line 1234 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_DIV_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2687 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 268:
#line 1237 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_REM_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2695 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 269:
#line 1240 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_AND_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2703 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 270:
#line 1243 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_OR_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2711 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 271:
#line 1246 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_XOR_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2719 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 272:
#line 1249 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_SHL_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2727 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 273:
#line 1252 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_SHR_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2735 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 274:
#line 1255 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_USHR_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2743 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 304:
#line 1287 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_JmpLabel(OP_JMPLABEL, driver.stringPool(), yystack_[0].value.as< std::string > ());
    }
#line 2751 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 305:
#line 1290 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CATCH(OP_CATCH, driver.stringPool(), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 2759 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 306:
#line 1293 "SmaliParser.yy" // lalr1.cc:859
    {
       std::string allclass = "";
       yylhs.value.as< OpCode* > () = new Op_CATCH(OP_CATCHALL, driver.stringPool(), allclass, yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 2768 "SmaliParser.cpp" // lalr1.cc:859
    break;


#line 2772 "SmaliParser.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
   SmaliParser ::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
   SmaliParser ::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short int  SmaliParser ::yypact_ninf_ = -1227;

  const signed char  SmaliParser ::yytable_ninf_ = -1;

  const short int
   SmaliParser ::yypact_[] =
  {
   -1227,  1277, -1227,    15, -1227,    42,    55,    56,    42,    42,
   -1227,    39,    39,    29,  -219, -1227, -1227,    67,    68,    69,
      70,    71,    72,    73,    75,    76,    77,    78,    79,    80,
   -1227,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,  -210,  -182,   103,   104,  -177,  -177,  -177,   106,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125, -1227, -1227,
   -1227, -1227, -1227, -1227,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,  -116,  -115,  -114,  -113,
    -112, -1227,  -111,  -110,  -109,  -108,  -107, -1227, -1227,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   237,   238,   239,   240,
     242,   243,   244,   245,   247,   248,   249,   250,   251,   252,
     254,   255,   256,   257,   259,   260,   261,   262,   264,   265,
     266,   267,   269,   270,   271,   272,   274,   275,   276,   277,
     278,   279,   281,   282,   283,   284,   286,   287,   288,   289,
     291,   292,   293, -1227, -1227, -1227, -1227, -1227, -1227, -1227,
   -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227,
   -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227,
   -1227, -1227,    14, -1227, -1227, -1227, -1227, -1227, -1227, -1227,
   -1227, -1227, -1227, -1227,    17, -1227, -1227,    16,    16, -1227,
   -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227,    40,
   -1227, -1227,    10,  -177,  -176,    12,    13,    18,    19,    20,
      21,    22,    23, -1227, -1227, -1227, -1227, -1227, -1227, -1227,
      24,    25,    26,    27,    28,    30,    31,    32,    33,    34,
      35, -1227, -1227,    36,    37,    38,    41,    43,   297,   298,
      44, -1227,    14, -1227, -1227, -1227,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,   102,   105,   169,   172,
     173,   174,   175,   176,   177,   195,   236,   241,   246,   253,
     258,   280,   285,   290,   294,   295,   296,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   297,   297,   297,
     297,   297,   322,   323,   325,   338,   339,   319,   320,   321,
     324,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   340,   341,   342,   343,   344,   345,   346,
     347,   349,   350,   351,   352,   353,   354,   355,   356,   357,
     358,   359,   360,   361,   362,   363,   364,   365,   366,   367,
     368,   369,   370,   371,   372,   373,   374,   375,   376,   377,
     378,   379,   380,   381,   382,   383,   384,   385,   386,   387,
     389,   390,   391,   392,   393,   394,   395,   396,   397,   398,
     399,   400,   401,   402,   403,   404,   405,   406,   407,   408,
     409,   410,   411,   412,   413,   414,   415,   416,   417,   432,
     433,   434,   435,   436,   437,   438,   439,   440,   441,   442,
     443, -1227, -1227, -1227, -1227, -1227,   168,   273, -1227,  -177,
     170,   418,   419,   420,   422,   423,   424,   425,   426,   427,
      39,    39,    39,    74,    39,    39,    39,   388,   348,   421,
      29,    29,   428,   429,    29,   430, -1227,  -266,   263,  -177,
   -1227,  -177,  -177,   444,   445,   446,   447,   448,   461,   462,
     463,   464,   465,   472,  -177,  -177,  -177,  -177,  -177,  -177,
     473,   474,   475,   476,   477,   479,   480,   481,   482,   483,
     484,   487,   488,   490,   491,   492,   493,   494,   498,   502,
     503,   504,   505,   506,   507,   508,   509,   510,    29,    29,
      29,    29,    29,    29,    29,    29,    29,    29,    29,    29,
      29,    29,  -265,  -238,  -229,  -228,  -225,   449,   450,   451,
     452,   453,   511,   512,   513,   514,   515,   516,   517,   518,
     520,   521,   522,   523,   525,   526,   527,   528,   530,   531,
     532,   533,   534,   535,   537,   538,   539,   540,   557,   558,
     560,   561,   562,   564,   565,   566,   567,   569,   570,   571,
     572,   574,   575,   576,   580,   581,   605,   606,   608,   621,
     622,   727,   733,   734,   735,   736,   737,   738,   739,   740,
     741,   742,   743,   744,   745,   746,   747,   748,   749,   750,
     751,   752,   753,   754,   755,   756,   757,   758,   759,   760,
     761,   762,   763,   764,   765,   766,   767,   768,   769,   770,
     771,   772,   773,   774,   775,   776,   777,   778,   779,   780,
     781,   782,   783,   784,   785,   786,    29,    29,   519,  -177,
   -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227,
   -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227,
   -1227, -1227, -1227,   524, -1227, -1227,   529,   787,   536,   788,
   -1227, -1227, -1227,   541,   542,   543,   544,   545,   546,   547,
     548,   549,   550,   551, -1227, -1227, -1227, -1227, -1227, -1227,
     552,   553,   554,   555,   556,   559,   563,   568,   577,   578,
     579,   582,   583,   584,   585,   586,   587,   588,   589,   590,
     591,   592,   593,   594,   595,   596,   597,   598,   602,   604,
     610,   611,   612,   613,   614,   615,   616,   617,   618,   619,
     620,   655,   653,   654,   656,   657,   658,   789,   790,   791,
     792,   793, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227,
   -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227,
   -1227, -1227, -1227,   659,   660,   666,   667,   668,   669,   670,
     671,   672,   673,   674,   675,   676,   677,   678,   679,   680,
     681,   683,   684,   685,   686,   687,   688,   689,   690,   691,
     692,   693,   694,   695,   696, -1227, -1227, -1227, -1227, -1227,
   -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227,
   -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227,
   -1227, -1227, -1227, -1227, -1227, -1227, -1227,   697,   698,   699,
     700,   701,   702,   703,   704,   705,   706,   707,   708,   709,
     710,   711,   712,   713,   714,   715, -1227, -1227,   -51,  -177,
     600,    29,    29, -1227,    29,   603,   794,   795,   796,   797,
     799,  -177,  -177,  -177,  -177,  -177,  -177,   800,   801,   802,
     803,   804,   805,   806,   808,   809,   810,   811,   813,   814,
     815,    29,    29,    29,    29,    29,    29,    29,    29,    29,
      29,    29,    29,    29,    29,    14,    14,    14,    14,    14,
      14,    14,    14,    14,    14,    14,    14,    14,    14,    29,
      29,    29,    29,    29,   719,   798,   807,   812,   816,   817,
     818,   820,   821,   822,   823,   840,   843,   844,   845,   847,
     848,   849,   850,   852,   859,   863,   864,   901,   938,  1025,
    1026,  1027,  1028,  1029,  1030,  1031,  1032,  1033,  1034,  1035,
    1036,    39,    39,    39,    39,    39,    39,    39,    39,    39,
      39,    39,    39,    39,    39,    39,    39,    39,    39,    39,
      29, -1227,   819,  -177, -1227, -1227, -1227,   824, -1227, -1227,
   -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227,
   -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227,
   -1227, -1227, -1227,   825,   826,   828,   829,   830,   831,   832,
     833,   834,   835,   836,   837,   838,   839,   841,   842,   846,
     851,   853,   854,   855,   856,   857,   858,   860,   861,   862,
     877,   880,   881,   882,   883,   889,   887,   888,   890,   891,
     892, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227,
   -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227,
   -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227,
   -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227,
   -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227,
   -1227, -1227, -1227,  -177, -1227,    29,    14,    14,    14,    14,
      14,    14,    14,    14,    14,    14,    14,    14,    14,    14,
      29,    29,    29,    29,    29,    29,    29,    29,    29,    29,
      29,    29,    29,    29,    14,    14,    14,    14,    14,    29,
      29,    29,    29,    29, -1227, -1227,   894,   895,   896,   897,
     898,   899,   900,   902,   903,   904,   905,   906,   907,   908,
   -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227,
   -1227, -1227, -1227, -1227,   886,   909,   910,   911,   912,   913,
     914,   919,   920,   921,    29,    29,    29,    29,    29,    29,
      29,    29,    29,    29,    29,    29,    29,    29,    29,    29,
      29,    29,    29,    14,    14,    14,    14,    14, -1227, -1227,
   -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227,
   -1227, -1227,   -46,   -41,   -34,   -29,   -24,   916,   917,   918,
     922,   937,    29,    29,    29,    29,    29,    29,    29,    29,
      29,    29, -1227, -1227, -1227, -1227, -1227,   -19,   -14,    -7,
      -2,     3,    29,    29,    29,    29,    29, -1227, -1227, -1227,
   -1227, -1227
  };

  const unsigned short int
   SmaliParser ::yydefact_[] =
  {
       2,     0,     1,     0,     3,    20,     0,     0,    20,    20,
      14,     0,     0,     0,     0,    37,    48,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      62,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   110,   111,
     112,   113,   114,   115,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   163,     0,     0,     0,     0,     0,   169,   170,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,     0,     5,     7,     8,     9,    10,    11,     4,
      12,    13,     6,    21,     0,    16,    17,     0,     0,    41,
      42,    43,    44,    45,    38,    39,    27,    26,    25,     0,
      28,    29,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    58,    59,    60,    61,    63,    64,    65,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    77,    78,     0,     0,     0,     0,     0,    34,     0,
       0,    87,     0,    88,    89,    90,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    34,    34,    34,
      34,    34,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    23,    24,   304,    22,    15,     0,     0,    30,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    35,     0,     0,     0,
      40,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    31,     0,     0,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    66,
      67,    68,    46,    47,    69,    70,    71,    72,    73,    74,
      75,    76,    79,     0,    81,    82,     0,     0,     0,     0,
      86,    91,    92,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   104,   105,   106,   107,   108,   109,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    18,    32,     0,     0,
       0,     0,     0,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    33,     0,     0,    80,    83,    84,     0,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,    19,     0,   306,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   305,    85,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    31,    31,
      31,    31,    31,     0,     0,     0,     0,     0,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    31,    31,    31,
      31,    31,   158,   159,   160,   161,   162,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   164,   165,   166,
     167,   168
  };

  const short int
   SmaliParser ::yypgoto_[] =
  {
   -1227, -1227, -1227, -1227, -1227, -1227, -1227, -1227,   107,  -242,
     827,   -13, -1226,  -319, -1227, -1227,   -56,     7, -1227, -1227
  };

  const short int
   SmaliParser ::yydefgoto_[] =
  {
      -1,     1,   273,   274,   275,   276,   277,   278,   284,   523,
     301,   947,   948,   557,   279,   280,   343,   294,   754,   281
  };

  const unsigned short int
   SmaliParser ::yytable_[] =
  {
     302,   344,   345,   296,   297,   298,   299,   300,   296,   297,
     298,   299,   300,   296,   297,   298,   299,   300,   282,   295,
     296,   297,   298,   299,   300,   296,   297,   298,   299,   300,
     296,   297,   298,   299,   300,   296,   297,   298,   299,   300,
     296,   297,   298,   299,   300,   526,   527,   296,   297,   298,
     299,   300,   296,   297,   298,   299,   300,   296,   297,   298,
     299,   300,  1312,  1313,  1314,  1315,  1316,   524,   524,   767,
     767,   768,   832,   525,   521,   522,   521,   522,   289,   290,
     291,   292,   293,   296,   297,   298,   299,   300,   622,   623,
     624,   625,   626,   283,   296,   297,   298,   767,   300,   833,
     560,  1337,  1338,  1339,  1340,  1341,   767,   767,   834,   835,
     767,   285,   836,   752,   753,   287,   288,   303,   286,   304,
     305,   306,   307,   308,   309,   310,   338,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   339,   340,   341,   342,   346,   531,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   366,
     367,   368,   369,   370,   371,   372,   373,   374,   375,   376,
     377,   378,   379,   380,   381,   382,   383,   384,   385,   386,
     387,   388,   389,   390,   391,   392,   393,   394,   395,   396,
     397,   398,   399,   400,   401,   402,   403,   404,   405,   406,
     407,   408,   409,   410,   411,   412,   413,   414,   415,   416,
     417,   418,   419,   420,   421,   422,   423,   424,   425,   426,
     427,   428,   429,   430,   431,   432,   433,   530,   434,   435,
     436,   437,   438,   439,   440,   441,   442,   443,   444,   445,
     446,   447,   448,   449,   450,   451,   452,   453,   454,   455,
     456,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,  1070,   474,
     475,   476,   477,  1322,   478,   479,   480,   481,  1323,   482,
     483,   484,   485,   486,   487,  1324,   488,   489,   490,   491,
    1325,   492,   493,   494,   495,  1326,   496,   497,   498,   499,
    1342,   500,   501,   502,   503,  1343,   504,   505,   506,   507,
     508,   509,  1344,   510,   511,   512,   513,  1345,   514,   515,
     516,   517,  1346,   518,   519,   520,   529,   532,   533,   556,
     558,     0,     0,   534,   535,   536,   537,   538,   539,   540,
     541,   542,   543,   544,     0,   545,   546,   547,   548,   549,
     550,   551,   552,   553,   627,   628,   554,   629,   555,   559,
     561,   562,   563,   564,   565,   566,   567,   568,   569,   570,
     630,   631,   571,   572,   573,   574,   575,   576,   577,   578,
     579,   580,     0,     0,     0,     0,     0,     0,     0,     0,
     759,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   758,
       0,     0,     0,     0,     0,     0,     0,   581,     0,     0,
     582,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     740,   741,   742,   738,   743,   744,   745,   746,   747,   748,
     763,   764,   766,   760,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   773,   774,   775,   776,
     777,   739,   736,   770,   583,   771,   772,   584,   585,   586,
     587,   588,   589,   778,   779,   780,   781,   782,   784,   785,
     786,   787,   788,   789,   783,   790,   791,   792,   793,   794,
     590,   795,   796,   797,   798,   799,   800,   761,   762,   801,
     802,   765,   803,   804,   805,   806,   807,   749,   750,   751,
     808,   755,   756,   757,   809,   810,   811,   812,   813,   814,
     815,   816,   817,   842,   843,   844,   845,   846,   847,   848,
     849,   591,   850,   851,   852,   853,   592,   854,   855,   856,
     857,   593,   858,   859,   860,   861,   862,   863,   594,   864,
     865,   866,   867,   595,   769,   818,   819,   820,   821,   822,
     823,   824,   825,   826,   827,   828,   829,   830,   831,   868,
     869,   737,   870,   871,   872,   596,   873,   874,   875,   876,
     597,   877,   878,   879,   880,   598,   881,   882,   883,   599,
     600,   601,   884,   885,   602,   603,   604,   605,   606,   607,
     608,   609,   610,   611,   612,   613,   614,   615,   616,   617,
     618,   619,   620,   621,   632,   633,   634,   886,   887,   635,
     888,   636,   637,   638,   639,   640,   641,   642,   643,   644,
     645,   646,   647,   889,   890,   648,   649,   650,   651,   652,
     653,   654,   655,   950,   656,   657,   658,   659,   660,   661,
     662,   663,   664,   665,   666,   667,   668,   669,   670,   671,
     672,   673,   674,   675,   676,   677,   678,   679,   680,   681,
     682,   683,   684,   685,   686,   687,   688,   689,   690,   691,
     692,   693,   694,   946,   695,   696,   697,   698,   699,   700,
     701,   702,   703,   704,   705,   706,   707,   708,   709,   710,
     711,   712,   713,   714,   715,   716,   717,   718,   719,   720,
     721,   722,   723,  1117,  1118,  1119,  1120,  1121,  1122,  1123,
    1124,  1125,  1126,  1127,  1128,  1129,  1130,   724,   725,   726,
     727,   728,   729,   730,   731,   732,   733,   734,   735,   891,
     837,   838,   839,   840,   841,   892,   893,   894,   895,   896,
     897,   898,   899,   900,   901,   902,   903,   904,   905,   906,
     907,   908,   909,   910,   911,   912,   913,   914,   915,   916,
     917,   918,   919,   920,   921,   922,   923,   924,   925,   926,
     927,   928,   929,   930,   931,   932,   933,   934,   935,   936,
     937,   938,   939,   940,   941,   942,   943,   944,   945,   953,
     955,  1014,  1015,  1016,  1017,  1018,  1078,  1079,  1080,  1081,
     949,  1082,  1089,  1090,  1091,  1092,  1093,  1094,  1095,   951,
    1096,  1097,  1098,  1099,   952,  1100,  1101,  1102,     0,  1141,
    1142,   954,  1143,  1144,  1145,  1146,   956,   957,   958,   959,
     960,   961,   962,   963,   964,   965,   966,   967,   968,   969,
     970,   971,  1147,  1072,   972,  1148,  1149,  1150,   973,  1151,
    1152,  1153,  1154,   974,  1155,  1083,  1084,  1085,  1086,  1087,
    1088,  1156,   975,   976,   977,  1157,  1158,   978,   979,   980,
     981,   982,   983,   984,   985,   986,   987,   988,   989,   990,
     991,   992,   993,   994,   995,  1071,   996,  1073,  1074,  1075,
    1077,  1076,   997,   998,   999,  1000,  1001,  1002,  1003,  1004,
    1005,  1006,  1007,  1159,  1236,  1237,  1238,  1239,  1240,  1241,
    1242,  1243,  1244,  1245,  1246,  1247,  1248,  1249,  1103,  1104,
    1105,  1106,  1107,  1108,  1109,  1110,  1111,  1112,  1113,  1114,
    1115,  1116,  1264,  1265,  1266,  1267,  1268,  1008,  1009,  1010,
    1160,  1011,  1012,  1013,  1019,  1020,  1131,  1132,  1133,  1134,
    1135,  1021,  1022,  1023,  1024,  1025,  1026,  1027,  1028,  1029,
    1030,  1031,  1032,  1033,  1034,  1035,  1036,  1194,  1037,  1038,
    1039,  1040,  1041,  1042,  1043,  1044,  1045,  1046,  1047,  1048,
    1049,  1050,  1051,  1052,  1053,  1054,  1055,  1056,  1057,  1058,
    1059,  1060,  1061,  1062,  1063,  1064,  1065,  1066,  1067,  1068,
    1069,  1317,  1318,  1319,  1320,  1321,  1136,  1192,  1173,  1174,
    1175,  1176,  1177,  1178,  1179,  1180,  1181,  1182,  1183,  1184,
    1185,  1186,  1187,  1188,  1189,  1190,  1191,  1161,  1162,  1163,
    1164,  1165,  1166,  1167,  1168,  1169,  1170,  1171,  1172,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   528,     0,     0,     0,
       0,     0,     0,     0,     0,  1137,     0,  1234,     0,     0,
       0,     0,     0,     0,  1138,     0,     0,     0,     0,  1139,
       0,     0,     0,  1140,     0,     0,  1193,  1196,  1197,  1195,
    1198,  1199,  1200,  1201,  1202,  1203,  1204,  1205,  1206,  1207,
    1208,  1209,     0,     0,     0,  1210,  1211,     0,     0,     0,
    1212,     0,  1235,     0,     0,  1213,     0,  1214,  1215,  1216,
    1217,  1218,  1219,     0,  1220,  1221,  1222,  1250,  1251,  1252,
    1253,  1254,  1255,  1256,  1257,  1258,  1259,  1260,  1261,  1262,
    1263,  1223,  1224,  1225,  1226,  1227,  1269,  1270,  1271,  1272,
    1273,  1228,  1229,  1230,  1288,  1231,  1232,  1233,  1274,  1275,
    1276,  1277,  1278,  1279,  1280,     0,  1281,  1282,  1283,  1284,
    1285,  1286,  1287,     0,     0,  1293,  1294,  1289,  1290,  1291,
    1292,  1295,  1296,  1297,  1327,  1328,  1329,     0,     0,     0,
    1330,  1298,  1299,  1300,  1301,  1302,  1303,  1304,  1305,  1306,
    1307,  1308,  1309,  1310,  1311,  1331,     0,     2,     3,     0,
       4,     0,     0,     5,     6,     0,     7,     8,     0,     0,
       0,     0,     0,     0,     9,    10,    11,    12,     0,  1071,
    1071,  1071,  1071,  1071,    13,    14,     0,     0,     0,  1332,
    1333,  1334,  1335,  1336,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1071,  1071,  1071,  1071,  1071,  1347,
    1348,  1349,  1350,  1351,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    15,     0,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,     0,     0,     0,     0,
       0,   272
  };

  const short int
   SmaliParser ::yycheck_[] =
  {
      13,    57,    58,    54,    55,    56,    57,    58,    54,    55,
      56,    57,    58,    54,    55,    56,    57,    58,     3,    12,
      54,    55,    56,    57,    58,    54,    55,    56,    57,    58,
      54,    55,    56,    57,    58,    54,    55,    56,    57,    58,
      54,    55,    56,    57,    58,   287,   288,    54,    55,    56,
      57,    58,    54,    55,    56,    57,    58,    54,    55,    56,
      57,    58,  1288,  1289,  1290,  1291,  1292,    51,    51,   335,
     335,   337,   337,    56,    60,    61,    60,    61,    39,    40,
      41,    42,    43,    54,    55,    56,    57,    58,   407,   408,
     409,   410,   411,    51,    54,    55,    56,   335,    58,   337,
     342,  1327,  1328,  1329,  1330,  1331,   335,   335,   337,   337,
     335,    56,   337,    39,    40,     8,     9,   336,    62,    52,
      52,    52,    52,    52,    52,    52,   336,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,   336,    52,    52,   334,    52,   335,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
     336,   336,   336,   336,   336,   336,   336,   336,   336,   336,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,   303,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,   339,    52,
      52,    52,    52,   339,    52,    52,    52,    52,   339,    52,
      52,    52,    52,    52,    52,   339,    52,    52,    52,    52,
     339,    52,    52,    52,    52,   339,    52,    52,    52,    52,
     339,    52,    52,    52,    52,   339,    52,    52,    52,    52,
      52,    52,   339,    52,    52,    52,    52,   339,    52,    52,
      52,    52,   339,    52,    52,    52,   336,   335,   335,    52,
      52,    -1,    -1,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,    -1,   335,   335,   335,   335,   335,
     335,   335,   335,   335,    52,    52,   335,    52,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
      52,    52,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   335,    -1,    -1,
     335,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    52,    52,   529,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    52,    52,    52,
      52,   331,   334,   559,   335,   561,   562,   335,   335,   335,
     335,   335,   335,    52,    52,    52,    52,    52,   574,   575,
     576,   577,   578,   579,    52,    52,    52,    52,    52,    52,
     335,    52,    52,    52,    52,    52,    52,   550,   551,    52,
      52,   554,    52,    52,    52,    52,    52,   540,   541,   542,
      52,   544,   545,   546,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,   335,    52,    52,    52,    52,   335,    52,    52,    52,
      52,   335,    52,    52,    52,    52,    52,    52,   335,    52,
      52,    52,    52,   335,   331,   608,   609,   610,   611,   612,
     613,   614,   615,   616,   617,   618,   619,   620,   621,    52,
      52,   338,    52,    52,    52,   335,    52,    52,    52,    52,
     335,    52,    52,    52,    52,   335,    52,    52,    52,   335,
     335,   335,    52,    52,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,    52,    52,   335,
      52,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,    52,    52,   335,   335,   335,   335,   335,
     335,   335,   335,   739,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   736,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   995,   996,   997,   998,   999,  1000,  1001,
    1002,  1003,  1004,  1005,  1006,  1007,  1008,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,    52,
     331,   331,   331,   331,   331,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
     331,    52,    52,    52,    52,    52,    52,    52,    52,   335,
      52,    52,    52,    52,   335,    52,    52,    52,    -1,    52,
      52,   335,    52,    52,    52,    52,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,    52,   949,   335,    52,    52,    52,   335,    52,
      52,    52,    52,   335,    52,   961,   962,   963,   964,   965,
     966,    52,   335,   335,   335,    52,    52,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   332,   948,   332,   337,   951,   952,
     337,   954,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   332,   332,    52,  1196,  1197,  1198,  1199,  1200,  1201,
    1202,  1203,  1204,  1205,  1206,  1207,  1208,  1209,   981,   982,
     983,   984,   985,   986,   987,   988,   989,   990,   991,   992,
     993,   994,  1224,  1225,  1226,  1227,  1228,   332,   335,   335,
      52,   335,   335,   335,   335,   335,  1009,  1010,  1011,  1012,
    1013,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,  1073,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,  1293,  1294,  1295,  1296,  1297,   337,  1070,  1051,  1052,
    1053,  1054,  1055,  1056,  1057,  1058,  1059,  1060,  1061,  1062,
    1063,  1064,  1065,  1066,  1067,  1068,  1069,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   299,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   337,    -1,  1193,    -1,    -1,
      -1,    -1,    -1,    -1,   337,    -1,    -1,    -1,    -1,   337,
      -1,    -1,    -1,   337,    -1,    -1,   337,   332,   332,   335,
     332,   332,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   332,    -1,    -1,    -1,   334,   334,    -1,    -1,    -1,
     334,    -1,  1195,    -1,    -1,   334,    -1,   334,   334,   334,
     334,   334,   334,    -1,   334,   334,   334,  1210,  1211,  1212,
    1213,  1214,  1215,  1216,  1217,  1218,  1219,  1220,  1221,  1222,
    1223,   334,   332,   332,   332,   332,  1229,  1230,  1231,  1232,
    1233,   332,   335,   335,   338,   335,   335,   335,   334,   334,
     334,   334,   334,   334,   334,    -1,   334,   334,   334,   334,
     334,   334,   334,    -1,    -1,   332,   332,   338,   338,   338,
     338,   332,   332,   332,   338,   338,   338,    -1,    -1,    -1,
     338,  1274,  1275,  1276,  1277,  1278,  1279,  1280,  1281,  1282,
    1283,  1284,  1285,  1286,  1287,   338,    -1,     0,     1,    -1,
       3,    -1,    -1,     6,     7,    -1,     9,    10,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    -1,  1312,
    1313,  1314,  1315,  1316,    27,    28,    -1,    -1,    -1,  1322,
    1323,  1324,  1325,  1326,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1337,  1338,  1339,  1340,  1341,  1342,
    1343,  1344,  1345,  1346,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,    -1,    -1,    -1,    -1,
      -1,   334
  };

  const unsigned short int
   SmaliParser ::yystos_[] =
  {
       0,   347,     0,     1,     3,     6,     7,     9,    10,    17,
      18,    19,    20,    27,    28,    71,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   334,   348,   349,   350,   351,   352,   353,   360,
     361,   365,     3,    51,   354,    56,    62,   354,   354,    39,
      40,    41,    42,    43,   363,   363,    54,    55,    56,    57,
      58,   356,   357,   336,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,   336,   336,
      52,    52,   334,   362,   362,   362,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,   336,   336,   336,
     336,   336,   336,   336,   336,   336,   336,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    60,    61,   355,    51,    56,   355,   355,   356,   336,
     362,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,    52,   359,    52,   335,
     355,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   359,   359,   359,   359,   359,    52,    52,    52,
      52,    52,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   334,   338,   362,   331,
      52,    52,    52,    52,    52,    52,    52,    52,    52,   363,
     363,   363,    39,    40,   364,   363,   363,   363,    41,    62,
      62,   357,   357,    52,    52,   357,    52,   335,   337,   331,
     362,   362,   362,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,   362,   362,   362,   362,   362,   362,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,   357,   357,
     357,   357,   357,   357,   357,   357,   357,   357,   357,   357,
     357,   357,   337,   337,   337,   337,   337,   331,   331,   331,
     331,   331,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,   357,   357,   358,   331,
     362,   335,   335,    52,   335,    52,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   332,   332,   332,   332,   332,
     332,   332,   332,   332,   332,   332,   332,   332,   332,   335,
     335,   335,   335,   335,    52,    52,    52,    52,    52,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     339,   357,   362,   337,   357,   357,   357,   337,    52,    52,
      52,    52,    52,   362,   362,   362,   362,   362,   362,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,   357,   357,   357,   357,   357,   357,   357,
     357,   357,   357,   357,   357,   357,   357,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   357,   357,   357,   357,   357,   337,   337,   337,   337,
     337,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,   363,   363,   363,   363,   363,   363,   363,
     363,   363,   363,   363,   363,   363,   363,   363,   363,   363,
     363,   363,   357,   337,   362,   335,   332,   332,   332,   332,
     332,   332,   332,   332,   332,   332,   332,   332,   332,   332,
     334,   334,   334,   334,   334,   334,   334,   334,   334,   334,
     334,   334,   334,   334,   332,   332,   332,   332,   332,   335,
     335,   335,   335,   335,   362,   357,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     357,   357,   357,   357,   357,   357,   357,   357,   357,   357,
     357,   357,   357,   357,   355,   355,   355,   355,   355,   357,
     357,   357,   357,   357,   334,   334,   334,   334,   334,   334,
     334,   334,   334,   334,   334,   334,   334,   334,   338,   338,
     338,   338,   338,   332,   332,   332,   332,   332,   357,   357,
     357,   357,   357,   357,   357,   357,   357,   357,   357,   357,
     357,   357,   358,   358,   358,   358,   358,   355,   355,   355,
     355,   355,   339,   339,   339,   339,   339,   338,   338,   338,
     338,   338,   357,   357,   357,   357,   357,   358,   358,   358,
     358,   358,   339,   339,   339,   339,   339,   357,   357,   357,
     357,   357
  };

  const unsigned short int
   SmaliParser ::yyr1_[] =
  {
       0,   346,   347,   347,   347,   347,   347,   348,   348,   348,
     348,   348,   348,   348,   348,   349,   350,   351,   352,   353,
     354,   354,   354,   355,   355,   356,   356,   356,   356,   357,
     357,   358,   358,   358,   359,   359,   359,   360,   361,   361,
     362,   363,   363,   363,   363,   363,   364,   364,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365
  };

  const unsigned char
   SmaliParser ::yyr2_[] =
  {
       0,     2,     0,     2,     2,     2,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     2,     2,     5,     7,
       0,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       2,     0,     1,     2,     0,     1,     3,     1,     2,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     2,     2,
       2,     2,     1,     2,     2,     2,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     2,     2,     4,
       6,     4,     4,     6,     6,     8,     4,     2,     2,     2,
       2,     4,     4,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     4,     4,     4,     4,     4,     4,
       1,     1,     1,     1,     1,     1,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
      10,    10,    10,    10,    10,    10,    10,    10,    10,    10,
      10,    10,    10,    10,     8,     8,     8,     8,     8,     8,
       8,     8,     8,     8,     8,     8,     8,     8,    12,    12,
      12,    12,    12,     1,    14,    14,    14,    14,    14,     1,
       1,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     8,     7
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const  SmaliParser ::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"end of line\"",
  "\"lex error\"", "\"begin of keywords\"", "\".class\"", "\".super\"",
  "\".implements\"", "\".source\"", "\".field\"", "\".end field\"",
  "\".subannotation\"", "\".end subannotation\"", "\".annotation\"",
  "\".end annotation\"", "\".enum\"", "\".method\"", "\".end method\"",
  "\".registers\"", "\".locals\"", "\".array-data\"",
  "\".end array-data\"", "\".packed-switch\"", "\".end packed-switch\"",
  "\".sparse-switch\"", "\".end sparse-switch\"", "\".catch\"",
  "\".catchall\"", "\".line\"", "\".param\"", "\".end param\"",
  "\".local\"", "\".end local\"", "\".restart local\"", "\".prologue\"",
  "\".epilogue\"", "\"end of keywords\"", "\"begin of numbers\"",
  "\"Integer\"", "\"- Integer\"", "\"- Integer L\"", "\"- Integer S\"",
  "\"- Integer T\"", "\"FloatOrID F\"", "\"FloatOrID D\"", "\"Float F\"",
  "\"Float D\"", "\"true|false\"", "\"null\"", "\"end of numbers\"",
  "\"flag\"", "\"v(p)x\"", "\"begin of param\"", "\"ZBSCIJFDLIT\"",
  "\"ZBSCIJFD\"", "\"Lxxx;\"", "\"[[\"", "\"V\"", "\"end of param\"",
  "\"simple name\"", "\"member name\"", "\"string\"", "\"char\"",
  "MISC_BEGIN", "\"build runtime system\"", "\"ver type error\"",
  "\"inline@0x\"", "\"vtable@0x\"", "\"field@0x\"", "MISC_END",
  "\"# comments\"", "\"begin of opcodes\"", "\"nop\"", "\"move\"",
  "\"move/from16\"", "\"move/16\"", "\"move-wide\"",
  "\"move-wide/from16\"", "\"move-wide/16\"", "\"move-object\"",
  "\"move-object/from16\"", "\"move-object/16\"", "\"move-result\"",
  "\"move-result-wide\"", "\"move-result-object\"", "\"move-exception\"",
  "\"return-void\"", "\"return\"", "\"return-wide\"", "\"return-object\"",
  "\"const/4\"", "\"const/16\"", "\"const\"", "\"const/high16\"",
  "\"const-wide/16\"", "\"const-wide/32\"", "\"const-wide\"",
  "\"const-wide/high16\"", "\"const-string\"", "\"const-string/jumbo\"",
  "\"const-class\"", "\"monitor-enter\"", "\"monitor-exit\"",
  "\"check-cast\"", "\"instance-of\"", "\"array-length\"",
  "\"new-instance\"", "\"new-array\"", "\"filled-new-array\"",
  "\"filled-new-array/range\"", "\"fill-array-data\"", "\"throw\"",
  "\"goto\"", "\"goto/16\"", "\"goto/32\"", "\"packed-switch\"",
  "\"sparse-switch\"", "\"cmpl-float\"", "\"cmpg-float\"",
  "\"cmpl-double\"", "\"cmpg-double\"", "\"cmp-long\"", "\"if-eq\"",
  "\"if-ne\"", "\"if-lt\"", "\"if-ge\"", "\"if-gt\"", "\"if-le\"",
  "\"if-eqz\"", "\"if-nez\"", "\"if-ltz\"", "\"if-gez\"", "\"if-gtz\"",
  "\"if-lez\"", "\"unused-3e\"", "\"unused-3f\"", "\"unused-40\"",
  "\"unused-41\"", "\"unused-42\"", "\"unused-43\"", "\"aget\"",
  "\"aget-wide\"", "\"aget-object\"", "\"aget-boolean\"", "\"aget-byte\"",
  "\"aget-char\"", "\"aget-short\"", "\"aput\"", "\"aput-wide\"",
  "\"aput-object\"", "\"aput-boolean\"", "\"aput-byte\"", "\"aput-char\"",
  "\"aput-short\"", "\"iget\"", "\"iget-wide\"", "\"iget-object\"",
  "\"iget-boolean\"", "\"iget-byte\"", "\"iget-char\"", "\"iget-short\"",
  "\"iput\"", "\"iput-wide\"", "\"iput-object\"", "\"iput-boolean\"",
  "\"iput-byte\"", "\"iput-char\"", "\"iput-short\"", "\"sget\"",
  "\"sget-wide\"", "\"sget-object\"", "\"sget-boolean\"", "\"sget-byte\"",
  "\"sget-char\"", "\"sget-short\"", "\"sput\"", "\"sput-wide\"",
  "\"sput-object\"", "\"sput-boolean\"", "\"sput-byte\"", "\"sput-char\"",
  "\"sput-short\"", "\"invoke-virtual\"", "\"invoke-super\"",
  "\"invoke-direct\"", "\"invoke-static\"", "\"invoke-interface\"",
  "\"unused-73\"", "\"invoke-virtual/range\"", "\"invoke-super/range\"",
  "\"invoke-direct/range\"", "\"invoke-static/range\"",
  "\"invoke-interface/range\"", "\"unused-79\"", "\"unused-7a\"",
  "\"neg-int\"", "\"not-int\"", "\"neg-long\"", "\"not-long\"",
  "\"neg-float\"", "\"neg-double\"", "\"int-to-long\"", "\"int-to-float\"",
  "\"int-to-double\"", "\"long-to-int\"", "\"long-to-float\"",
  "\"long-to-double\"", "\"float-to-int\"", "\"float-to-long\"",
  "\"float-to-double\"", "\"double-to-int\"", "\"double-to-long\"",
  "\"double-to-float\"", "\"int-to-byte\"", "\"int-to-char\"",
  "\"int-to-short\"", "\"add-int\"", "\"sub-int\"", "\"mul-int\"",
  "\"div-int\"", "\"rem-int\"", "\"and-int\"", "\"or-int\"", "\"xor-int\"",
  "\"shl-int\"", "\"shr-int\"", "\"ushr-int\"", "\"add-long\"",
  "\"sub-long\"", "\"mul-long\"", "\"div-long\"", "\"rem-long\"",
  "\"and-long\"", "\"or-long\"", "\"xor-long\"", "\"shl-long\"",
  "\"shr-long\"", "\"ushr-long\"", "\"add-float\"", "\"sub-float\"",
  "\"mul-float\"", "\"div-float\"", "\"rem-float\"", "\"add-double\"",
  "\"sub-double\"", "\"mul-double\"", "\"div-double\"", "\"rem-double\"",
  "\"add-int/2addr\"", "\"sub-int/2addr\"", "\"mul-int/2addr\"",
  "\"div-int/2addr\"", "\"rem-int/2addr\"", "\"and-int/2addr\"",
  "\"or-int/2addr\"", "\"xor-int/2addr\"", "\"shl-int/2addr\"",
  "\"shr-int/2addr\"", "\"ushr-int/2addr\"", "\"add-long/2addr\"",
  "\"sub-long/2addr\"", "\"mul-long/2addr\"", "\"div-long/2addr\"",
  "\"rem-long/2addr\"", "\"and-long/2addr\"", "\"or-long/2addr\"",
  "\"xor-long/2addr\"", "\"shl-long/2addr\"", "\"shr-long/2addr\"",
  "\"ushr-long/2addr\"", "\"add-float/2addr\"", "\"sub-float/2addr\"",
  "\"mul-float/2addr\"", "\"div-float/2addr\"", "\"rem-float/2addr\"",
  "\"add-double/2addr\"", "\"sub-double/2addr\"", "\"mul-double/2addr\"",
  "\"div-double/2addr\"", "\"rem-double/2addr\"", "\"add-int/lit16\"",
  "\"rsub-int\"", "\"mul-int/lit16\"", "\"div-int/lit16\"",
  "\"rem-int/lit16\"", "\"and-int/lit16\"", "\"or-int/lit16\"",
  "\"xor-int/lit16\"", "\"add-int/lit8\"", "\"rsub-int/lit8\"",
  "\"mul-int/lit8\"", "\"div-int/lit8\"", "\"rem-int/lit8\"",
  "\"and-int/lit8\"", "\"or-int/lit8\"", "\"xor-int/lit8\"",
  "\"shl-int/lit8\"", "\"shr-int/lit8\"", "\"ushr-int/lit8\"",
  "\"+iget-volatile\"", "\"+iput-volatile\"", "\"+sget-volatile\"",
  "\"+sput-volatile\"", "\"+iget-object-volatile\"",
  "\"+iget-wide-volatile\"", "\"+iput-wide-volatile\"",
  "\"+sget-wide-volatile\"", "\"+sput-wide-volatile\"", "\"^breakpoint\"",
  "\"^throw-verification-error\"", "\"+execute-inline\"",
  "\"+execute-inline/range\"", "\"+invoke-object-init/range\"",
  "\"+return-void-barrier\"", "\"+iget-quick\"", "\"+iget-wide-quick\"",
  "\"+iget-object-quick\"", "\"+iput-quick\"", "\"+iput-wide-quick\"",
  "\"+iput-object-quick\"", "\"+invoke-virtual-quick\"",
  "\"+invoke-virtual-quick/range\"", "\"+invoke-super-quick\"",
  "\"+invoke-super-quick/range\"", "\"+iput-object-volatile\"",
  "\"+sget-object-volatile\"", "\"+sput-object-volatile\"",
  "\"unused-ff\"", "\"end of opcodes\"", "\"begin of symbol\"", "\"..\"",
  "\"->\"", "\"=\"", "\":\"", "\",\"", "\"{\"", "\"}\"", "\"(\"", "\")\"",
  "\"end of symbol\"", "\"integer\"", "\"classtype\"", "\"[classtype\"",
  "\"field or class name\"", "\"integer-str\"", "$accept", "program",
  "exp", "classdef", "superdef", "srcdef", "fielddef", "methoddef",
  "flags", "namestring", "classtype", "classtypeOrArray", "args", "regs",
  "comment", "registers", "jmplabel", "integer", "INTEGER_LITERAL",
  "instruction", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
   SmaliParser ::yyrline_[] =
  {
       0,   455,   455,   456,   457,   458,   459,   462,   463,   464,
     465,   466,   467,   468,   469,   473,   477,   481,   485,   489,
     493,   494,   497,   504,   505,   509,   510,   511,   512,   516,
     517,   521,   522,   526,   532,   533,   537,   543,   549,   552,
     559,   563,   566,   569,   572,   575,   581,   582,   587,   590,
     593,   596,   599,   602,   605,   608,   611,   614,   617,   620,
     623,   626,   629,   632,   635,   638,   641,   644,   647,   650,
     656,   659,   662,   665,   670,   673,   676,   679,   682,   685,
     688,   691,   694,   697,   700,   703,   709,   712,   715,   718,
     721,   724,   727,   730,   733,   736,   739,   742,   745,   748,
     751,   754,   757,   760,   763,   766,   769,   772,   775,   778,
     781,   782,   783,   784,   785,   786,   787,   790,   793,   796,
     799,   802,   805,   808,   811,   814,   817,   820,   823,   826,
     829,   832,   835,   838,   841,   844,   847,   850,   853,   856,
     859,   862,   865,   868,   871,   874,   877,   880,   883,   886,
     889,   892,   895,   898,   901,   904,   907,   910,   913,   916,
     919,   922,   925,   928,   929,   932,   935,   938,   941,   944,
     945,   946,   949,   952,   955,   958,   961,   964,   967,   970,
     973,   976,   979,   982,   985,   988,   991,   994,   997,  1000,
    1003,  1006,  1009,  1012,  1015,  1018,  1021,  1024,  1027,  1030,
    1033,  1036,  1039,  1042,  1045,  1048,  1051,  1054,  1057,  1060,
    1063,  1066,  1069,  1072,  1075,  1078,  1081,  1084,  1087,  1090,
    1093,  1096,  1099,  1102,  1105,  1108,  1111,  1114,  1117,  1120,
    1123,  1126,  1129,  1132,  1135,  1138,  1141,  1144,  1147,  1150,
    1153,  1156,  1159,  1162,  1165,  1168,  1171,  1174,  1177,  1180,
    1183,  1186,  1189,  1192,  1195,  1198,  1201,  1204,  1207,  1210,
    1213,  1216,  1219,  1222,  1225,  1228,  1231,  1234,  1237,  1240,
    1243,  1246,  1249,  1252,  1255,  1258,  1259,  1260,  1261,  1262,
    1263,  1264,  1265,  1266,  1267,  1268,  1269,  1270,  1271,  1272,
    1273,  1274,  1275,  1276,  1277,  1278,  1279,  1280,  1281,  1282,
    1283,  1284,  1285,  1286,  1287,  1290,  1293
  };

  // Print the state stack on the debug stream.
  void
   SmaliParser ::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
   SmaliParser ::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 9 "SmaliParser.yy" // lalr1.cc:1167
} //  Analysis 
#line 4057 "SmaliParser.cpp" // lalr1.cc:1167
#line 1298 "SmaliParser.yy" // lalr1.cc:1168


void Analysis::SmaliParser::error(const location &loc, const std::string &message) {
	cout << "Parse error: " << message << endl
	    << "Error location: " << loc << endl << driver.mLexer->text() << endl;
}
