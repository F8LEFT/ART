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
#line 506 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 828 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 507 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 834 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 508 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "V"; }
#line 840 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 512 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 846 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 513 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 852 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 514 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 858 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 515 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "V"; }
#line 864 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 519 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 870 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 520 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[1].value.as< std::string > () + yystack_[0].value.as< std::string > (); }
#line 876 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 524 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();}
#line 882 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 525 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();
        yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
    }
#line 891 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 529 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::vector<std::string> > () = yystack_[1].value.as< std::vector<std::string> > ();
        yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
    }
#line 900 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 535 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<int> > () = std::vector<int>();}
#line 906 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 536 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::vector<int> > () = std::vector<int>();
        yylhs.value.as< std::vector<int> > ().push_back(yystack_[0].value.as< int > ());
    }
#line 915 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 540 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::vector<int> > () = yystack_[2].value.as< std::vector<int> > ();
        yylhs.value.as< std::vector<int> > ().push_back(yystack_[0].value.as< int > ());
    }
#line 924 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 546 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();
    }
#line 932 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 552 "SmaliParser.yy" // lalr1.cc:859
    {
        driver.setCurMethodRegSize(yystack_[0].value.as< long long int > ());
     }
#line 940 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 555 "SmaliParser.yy" // lalr1.cc:859
    {
        // TODO Register size should be integer + argsize
        driver.setCurMethodRegSize(yystack_[0].value.as< long long int > ());
     }
#line 949 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 562 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();
    }
#line 957 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 566 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< long long int > () = driver.parseLongInt(yystack_[0].value.as< std::string > ());
     }
#line 965 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 569 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< long long int > () = driver.parseLongInt(yystack_[0].value.as< std::string > ());
     }
#line 973 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 572 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< long long int > () = driver.parseLongInt(yystack_[0].value.as< std::string > ());
     }
#line 981 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 575 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< long long int > () = driver.parseLongInt(yystack_[0].value.as< std::string > ());
     }
#line 989 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 578 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< long long int > () = driver.parseLongInt(yystack_[0].value.as< std::string > ());
     }
#line 997 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 584 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 1003 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 585 "SmaliParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 1009 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 590 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NOP(OP_NOP, driver.stringPool());
    }
#line 1017 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 593 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1025 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 596 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_FROM16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1033 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 599 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1041 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 602 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_WIDE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1049 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 605 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_WIDE_FROM16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1057 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 608 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_WIDE_16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1065 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 611 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_OBJECT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1073 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 614 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_OBJECT_FROM16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1081 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 617 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_OBJECT_16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1089 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 620 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_MOVE_RESULT(OP_MOVE_RESULT, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1097 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 623 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_MOVE_RESULT(OP_MOVE_RESULT_WIDE, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1105 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 626 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_MOVE_RESULT(OP_MOVE_RESULT_OBJECT, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1113 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 629 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE_EXCEPTION(OP_MOVE_EXCEPTION, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1121 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 632 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_RETURN_VOID(OP_RETURN_VOID, driver.stringPool());
    }
#line 1129 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 635 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_RETURN(OP_RETURN, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1137 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 638 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_RETURN(OP_RETURN_WIDE, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1145 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 641 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_RETURN(OP_RETURN_OBJECT, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1153 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 644 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_4, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 1161 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 647 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 1169 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 650 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 1177 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 653 "SmaliParser.yy" // lalr1.cc:859
    {
        auto number = yystack_[0].value.as< std::string > ().substr (0, yystack_[0].value.as< std::string > ().length () - 4);
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_HIGH16, driver.stringPool(), yystack_[2].value.as< int > (),
                         strtoll(number.c_str(), 0, 16));

    }
#line 1188 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 659 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_WIDE_16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 1196 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 662 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_WIDE_32, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 1204 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 665 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_WIDE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 1212 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 668 "SmaliParser.yy" // lalr1.cc:859
    {
        auto number = yystack_[0].value.as< std::string > ().substr (0, yystack_[0].value.as< std::string > ().length () - 13);
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_WIDE_HIGH16, driver.stringPool(), yystack_[2].value.as< int > (),
                        strtoll(number.c_str(), 0, 16));
    }
#line 1222 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 673 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CONST_STRING(OP_CONST_STRING, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1230 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 676 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CONST_STRING(OP_CONST_STRING_JUMBO, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1238 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 679 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CONST_CLASS(OP_CONST_CLASS, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1246 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 682 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MONITOR(OP_MONITOR_ENTER, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1254 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 685 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MONITOR(OP_MONITOR_EXIT, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1262 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 688 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CHECK_CAST(OP_CHECK_CAST, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1270 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 691 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INSTANCE_OF(OP_INSTANCE_OF, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
   }
#line 1278 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 694 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_ARRAY_LENGTH(OP_ARRAY_LENGTH, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1286 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 697 "SmaliParser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_NEW_INSTANCE(OP_NEW_INSTANCE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1294 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 700 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEW_ARRAY(OP_NEW_ARRAY, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1302 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 703 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_FILLED_NEW_ARRAY(OP_FILLED_NEW_ARRAY, driver.stringPool(), yystack_[3].value.as< std::vector<int> > (), yystack_[0].value.as< std::string > ());
    }
#line 1310 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 706 "SmaliParser.yy" // lalr1.cc:859
    {
       std::vector<int> regs;
       regs.push_back(yystack_[5].value.as< int > ());
       regs.push_back(yystack_[3].value.as< int > ());
       yylhs.value.as< OpCode* > () = new Op_FILLED_NEW_ARRAY(OP_FILLED_NEW_ARRAY_RANGE, driver.stringPool(), regs, yystack_[0].value.as< std::string > ());
    }
#line 1321 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 712 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_FILL_ARRAY_DATA(OP_FILL_ARRAY_DATA, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1329 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 715 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_THROW(OP_THROW, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1337 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 718 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_GOTO(OP_GOTO, driver.stringPool(), yystack_[0].value.as< std::string > ());
    }
#line 1345 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 721 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_GOTO(OP_GOTO_16, driver.stringPool(), yystack_[0].value.as< std::string > ());
    }
#line 1353 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 724 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_GOTO(OP_GOTO_32, driver.stringPool(), yystack_[0].value.as< std::string > ());
    }
#line 1361 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 727 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_SWITCH(OP_PACKED_SWITCH, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1369 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 730 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_SWITCH(OP_SPARSE_SWITCH, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1377 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 733 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CMP(OP_CMPL_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1385 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 736 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CMP(OP_CMPG_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1393 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 739 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CMP(OP_CMPL_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1401 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 742 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CMP(OP_CMPG_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1409 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 745 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CMP(OP_CMP_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1417 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 748 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_EQ, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1425 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 751 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_NE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1433 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 754 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_LT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1441 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 757 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_GE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1449 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 760 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_GT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1457 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 763 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_LE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1465 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 766 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_EQZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1473 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 769 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_NEZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1481 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 772 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_LTZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1489 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 775 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_GEZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1497 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 778 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_GTZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1505 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 781 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_LEZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1513 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 784 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_UNUSED(OP_UNUSED_3E, driver.stringPool());
    }
#line 1521 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 787 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_UNUSED(OP_UNUSED_3F, driver.stringPool());
    }
#line 1529 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 790 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_UNUSED(OP_UNUSED_40, driver.stringPool());
    }
#line 1537 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 793 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_UNUSED(OP_UNUSED_41, driver.stringPool());
    }
#line 1545 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 796 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_UNUSED(OP_UNUSED_42, driver.stringPool());
    }
#line 1553 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 799 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_UNUSED(OP_UNUSED_43, driver.stringPool());
    }
#line 1561 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 802 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1569 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 805 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_WIDE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1577 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 808 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_OBJECT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1585 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 811 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_BOOLEAN, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1593 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 814 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_BYTE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1601 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 817 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_CHAR, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1609 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 820 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_SHORT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1617 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 823 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1625 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 826 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT_WIDE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1633 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 829 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT_OBJECT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1641 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 832 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT_BOOLEAN, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1649 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 835 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT_BYTE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1657 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 838 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT_CHAR, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1665 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 841 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT_SHORT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1673 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 844 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1681 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 847 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET_WIDE, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1689 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 850 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET_OBJECT, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1697 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 853 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET_BOOLEAN, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1705 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 856 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET_BYTE, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1713 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 859 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET_CHAR, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1721 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 862 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET_SHORT, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1729 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 865 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1737 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 868 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT_WIDE, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1745 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 871 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT_OBJECT, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1753 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 874 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT_BOOLEAN, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1761 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 877 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT_BYTE, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1769 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 880 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT_CHAR, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1777 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 883 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT_SHORT, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1785 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 886 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1793 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 889 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_WIDE, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1801 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 892 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_OBJECT, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1809 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 895 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_BOOLEAN, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1817 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 898 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_BYTE, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1825 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 901 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_CHAR, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1833 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 904 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_SHORT, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1841 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 907 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1849 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 910 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_WIDE, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1857 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 913 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_OBJECT, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1865 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 916 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_BOOLEAN, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1873 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 919 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_BYTE, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1881 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 922 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_CHAR, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1889 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 925 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_SHORT, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1897 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 928 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE(OP_INVOKE_VIRTUAL, driver.stringPool(), yystack_[9].value.as< std::vector<int> > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1905 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 931 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE(OP_INVOKE_SUPER, driver.stringPool(), yystack_[9].value.as< std::vector<int> > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1913 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 934 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE(OP_INVOKE_DIRECT, driver.stringPool(), yystack_[9].value.as< std::vector<int> > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1921 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 937 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE(OP_INVOKE_STATIC, driver.stringPool(), yystack_[9].value.as< std::vector<int> > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1929 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 940 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE(OP_INVOKE_INTERFACE, driver.stringPool(), yystack_[9].value.as< std::vector<int> > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1937 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 943 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_UNUSED(OP_UNUSED_73, driver.stringPool());
    }
#line 1945 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 946 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE_X_RANGE(OP_INVOKE_VIRTUAL_RANGE, driver.stringPool(), yystack_[11].value.as< int > (), yystack_[9].value.as< int > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1953 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 949 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE_X_RANGE(OP_INVOKE_SUPER_RANGE, driver.stringPool(), yystack_[11].value.as< int > (), yystack_[9].value.as< int > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1961 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 952 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE_X_RANGE(OP_INVOKE_DIRECT_RANGE, driver.stringPool(), yystack_[11].value.as< int > (), yystack_[9].value.as< int > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1969 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 955 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE_X_RANGE(OP_INVOKE_STATIC_RANGE, driver.stringPool(), yystack_[11].value.as< int > (), yystack_[9].value.as< int > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1977 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 958 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE_X_RANGE(OP_INVOKE_INTERFACE_RANGE, driver.stringPool(), yystack_[11].value.as< int > (), yystack_[9].value.as< int > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1985 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 961 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_UNUSED(OP_UNUSED_79, driver.stringPool());
    }
#line 1993 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 964 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_UNUSED(OP_UNUSED_7A, driver.stringPool());
    }
#line 2001 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 967 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEGNOT_X(OP_NEG_INT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2009 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 970 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEGNOT_X(OP_NOT_INT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2017 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 973 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEGNOT_X(OP_NEG_LONG, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2025 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 976 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEGNOT_X(OP_NOT_LONG, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2033 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 979 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEGNOT_X(OP_NEG_FLOAT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2041 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 982 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEGNOT_X(OP_NEG_DOUBLE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2049 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 985 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_INT_TO_LONG, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2057 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 181:
#line 988 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_INT_TO_FLOAT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2065 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 182:
#line 991 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_INT_TO_DOUBLE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2073 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 183:
#line 994 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_LONG_TO_INT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2081 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 184:
#line 997 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_LONG_TO_FLOAT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2089 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 185:
#line 1000 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_LONG_TO_DOUBLE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2097 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 186:
#line 1003 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_FLOAT_TO_INT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2105 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 187:
#line 1006 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_FLOAT_TO_LONG, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2113 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 188:
#line 1009 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_FLOAT_TO_DOUBLE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2121 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 189:
#line 1012 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_DOUBLE_TO_INT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2129 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 190:
#line 1015 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_DOUBLE_TO_LONG, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2137 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 191:
#line 1018 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_DOUBLE_TO_FLOAT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2145 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 192:
#line 1021 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_INT_TO_BYTE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2153 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 193:
#line 1024 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_INT_TO_CHAR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2161 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 194:
#line 1027 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_INT_TO_SHORT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2169 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 195:
#line 1030 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_ADD_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2177 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 196:
#line 1033 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_SUB_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2185 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 197:
#line 1036 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_MUL_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2193 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 198:
#line 1039 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_DIV_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2201 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 199:
#line 1042 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_REM_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2209 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 200:
#line 1045 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_AND_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2217 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 201:
#line 1048 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_OR_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2225 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 202:
#line 1051 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_XOR_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2233 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 203:
#line 1054 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_SHL_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2241 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 204:
#line 1057 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_SHR_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2249 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 205:
#line 1060 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_USHR_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2257 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 206:
#line 1063 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_ADD_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2265 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 207:
#line 1066 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_SUB_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2273 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 208:
#line 1069 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_MUL_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2281 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 209:
#line 1072 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_DIV_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2289 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 210:
#line 1075 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_REM_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2297 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 211:
#line 1078 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_AND_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2305 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 212:
#line 1081 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_OR_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2313 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 213:
#line 1084 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_XOR_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2321 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 214:
#line 1087 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_SHL_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2329 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 215:
#line 1090 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_SHR_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2337 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 216:
#line 1093 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_USHR_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2345 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 217:
#line 1096 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT(OP_ADD_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2353 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 218:
#line 1099 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT(OP_SUB_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2361 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 219:
#line 1102 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT(OP_MUL_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2369 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 220:
#line 1105 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT(OP_DIV_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2377 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 221:
#line 1108 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT(OP_REM_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2385 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 222:
#line 1111 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE(OP_ADD_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2393 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 223:
#line 1114 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE(OP_SUB_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2401 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 224:
#line 1117 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE(OP_MUL_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2409 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 225:
#line 1120 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE(OP_DIV_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2417 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 226:
#line 1123 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE(OP_REM_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2425 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 227:
#line 1126 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_ADD_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2433 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 228:
#line 1129 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_SUB_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2441 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 229:
#line 1132 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_MUL_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2449 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 230:
#line 1135 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_DIV_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2457 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 231:
#line 1138 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_REM_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2465 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 232:
#line 1141 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_AND_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2473 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 233:
#line 1144 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_OR_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2481 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 234:
#line 1147 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_XOR_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2489 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 235:
#line 1150 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_SHL_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2497 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 236:
#line 1153 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_SHR_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2505 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 237:
#line 1156 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_USHR_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2513 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 238:
#line 1159 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_ADD_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2521 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 239:
#line 1162 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_SUB_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2529 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 240:
#line 1165 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_MUL_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2537 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 241:
#line 1168 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_DIV_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2545 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 242:
#line 1171 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_REM_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2553 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 243:
#line 1174 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_AND_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2561 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 244:
#line 1177 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_OR_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2569 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 245:
#line 1180 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_XOR_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2577 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 246:
#line 1183 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_SHL_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2585 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 247:
#line 1186 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_SHR_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2593 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 248:
#line 1189 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_USHR_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2601 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 249:
#line 1192 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT_2ADDR(OP_ADD_FLOAT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2609 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 250:
#line 1195 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT_2ADDR(OP_SUB_FLOAT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2617 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 251:
#line 1198 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT_2ADDR(OP_MUL_FLOAT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2625 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 252:
#line 1201 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT_2ADDR(OP_DIV_FLOAT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2633 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 253:
#line 1204 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT_2ADDR(OP_REM_FLOAT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2641 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 254:
#line 1207 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE_2ADDR(OP_ADD_DOUBLE_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2649 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 255:
#line 1210 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE_2ADDR(OP_SUB_DOUBLE_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2657 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 256:
#line 1213 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE_2ADDR(OP_MUL_DOUBLE_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2665 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 257:
#line 1216 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE_2ADDR(OP_DIV_DOUBLE_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2673 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 258:
#line 1219 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE_2ADDR(OP_REM_DOUBLE_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2681 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 259:
#line 1222 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_ADD_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2689 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 260:
#line 1225 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_RSUB_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2697 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 261:
#line 1228 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_MUL_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2705 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 262:
#line 1231 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_DIV_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2713 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 263:
#line 1234 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_REM_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2721 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 264:
#line 1237 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_AND_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2729 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 265:
#line 1240 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_OR_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2737 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 266:
#line 1243 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_XOR_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2745 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 267:
#line 1246 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_ADD_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2753 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 268:
#line 1249 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_RSUB_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2761 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 269:
#line 1252 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_MUL_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2769 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 270:
#line 1255 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_DIV_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2777 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 271:
#line 1258 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_REM_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2785 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 272:
#line 1261 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_AND_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2793 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 273:
#line 1264 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_OR_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2801 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 274:
#line 1267 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_XOR_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2809 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 275:
#line 1270 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_SHL_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2817 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 276:
#line 1273 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_SHR_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2825 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 277:
#line 1276 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_USHR_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2833 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 278:
#line 1307 "SmaliParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_UNUSED(OP_UNUSED_FF, driver.stringPool());
    }
#line 2841 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 279:
#line 1310 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_JmpLabel(OP_JMPLABEL, driver.stringPool(), yystack_[0].value.as< std::string > ());
    }
#line 2849 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 280:
#line 1313 "SmaliParser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CATCH(OP_CATCH, driver.stringPool(), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 2857 "SmaliParser.cpp" // lalr1.cc:859
    break;

  case 281:
#line 1316 "SmaliParser.yy" // lalr1.cc:859
    {
       std::string allclass = "";
       yylhs.value.as< OpCode* > () = new Op_CATCH(OP_CATCHALL, driver.stringPool(), allclass, yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 2866 "SmaliParser.cpp" // lalr1.cc:859
    break;


#line 2870 "SmaliParser.cpp" // lalr1.cc:859
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


  const short int  SmaliParser ::yypact_ninf_ = -1199;

  const signed char  SmaliParser ::yytable_ninf_ = -1;

  const short int
   SmaliParser ::yypact_[] =
  {
   -1199,  1252, -1199,    75, -1199,    35,    34,    41,    35,    35,
   -1199,    54,    54,    44,  -212, -1199, -1199,    73,    74,    76,
      77,    78,    79,    80,    82,    83,    84,    85,    86,    87,
   -1199,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,  -209,  -203,   109,   110,  -171,  -171,  -171,   112,
     113,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131, -1199, -1199,
   -1199, -1199, -1199, -1199,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   168,
     169,   170,   171,   172,   173,   174,  -170,  -109,  -108,  -107,
    -106, -1199,  -105,  -104,  -103,  -102,  -101, -1199, -1199,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   237,   238,   239,   240,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   254,   255,   256,   257,
     259,   260,   261,   262,   264,   265,   266,   267,   269,   270,
     271,   272,   274,   275,   276,   277,   279,   280,   281,   282,
     284,   285,   286,   287,   289,   290,   291,   292,   294,   295,
     296,   297,   298, -1199,    27, -1199, -1199, -1199, -1199, -1199,
   -1199, -1199, -1199, -1199, -1199, -1199,    20, -1199, -1199,    19,
      19, -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199,
   -1199,    60, -1199, -1199,    15,  -171,    17,    18,    21,    22,
      23,    24,    25,    26,    28, -1199, -1199, -1199, -1199, -1199,
   -1199, -1199,    29,    30,    31,    32,    33,    36,    37,    38,
      39,    40,    42, -1199, -1199,    43,    45,    46,    47,    48,
     302,   303,    49, -1199,    27, -1199, -1199, -1199,    50,    51,
      52,    53,    55,    56,    57,    58,    59,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,   111,
     167,   175,   176,   179,   180,   182,   183,   253,   258,   263,
     268,   273,   278,   283,   288,   293,   299,   300,   301,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   324,   302,
     302,   302,   302,   302,   327,   337,   343,   356,   357,   325,
     326,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     338,   339,   340,   341,   342,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   358,   359,   360,
     361,   362,   364,   365,   366,   367,   368,   369,   370,   371,
     372,   373,   374,   375,   376,   377,   378,   379,   380,   381,
     382,   383,   384,   385,   386,   387,   388,   389,   390,   391,
     392,   407,   408,   409,   410,   411,   412,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,   423,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   433,   434,   435,
     436,   437,   438,   439,   440,   441,   442,   443,   444,   445,
     446,   447,   448, -1199, -1199, -1199, -1199, -1199, -1199, -1199,
   -1199,   450,   181, -1199,  -171,   177,   363,   393,   395,   397,
     398,   399,   400,   401,   402,    54,    54,    54,    81,    54,
      54,    54,   394,   396,   403,    44,    44,   404,   405,    44,
     449, -1199,  -322,   178,  -171, -1199,  -171,  -171,   451,   452,
     453,   454,   455,   468,   469,   473,   477,   478,   479,  -171,
    -171,  -171,  -171,  -171,  -171,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,    44,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,  -321,  -262,  -254,
    -246,  -218,   236,   456,   457,   458,   459,   508,   509,   510,
     511,   512,   513,   514,   516,   517,   532,   533,   534,   535,
     537,   538,   539,   540,   542,   543,   544,   545,   547,   548,
     549,   550,   552,   553,   554,   555,   557,   558,   559,   560,
     562,   563,   564,   565,   567,   568,   569,   570,   572,   573,
     574,   575,   577,   578,   579,   580,   581,   585,   586,   610,
     620,   626,   639,   640,   733,   734,   739,   740,   741,   742,
     743,   744,   745,   746,   747,   748,   749,   750,   751,   752,
     753,   754,   755,   756,   757,   758,   759,   760,   761,   762,
     763,   764,   765,   766,   767,   768,   769,   770,   771,   772,
     773,   774,   775,   776,   777,   778,   779,   780,   781,   782,
     783,    44,    44,   515,  -171, -1199, -1199, -1199, -1199, -1199,
   -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199,
   -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199,   518, -1199,
   -1199,   519,   784,   520,   785, -1199, -1199, -1199,   521,   522,
     523,   524,   525,   526,   527,   528,   529,   530,   531, -1199,
   -1199, -1199, -1199, -1199, -1199,   536,   541,   551,   556,   561,
     566,   571,   576,   582,   583,   584,   587,   588,   589,   590,
     591,   592,   593,   627,   628,   629,   630,   631,   632,   633,
     634,   635,   641,   546,   645,   646,   647,   648,   649,   650,
     651,   652,   653,   654,   655,   656,   657,   658,   659,   660,
     661,   662,   786,   787,   788,   789,   790, -1199, -1199, -1199,
   -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199,
   -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199,   663,   664,
     665,   666,   667,   668,   669,   670,   671,   672,   673,   674,
     675,   676,   677,   678,   679,   680,   681,   682,   683,   684,
     685,   686,   687,   688,   689,   690,   696,   717,   718,   719,
   -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199,
   -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199,
   -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199,
   -1199, -1199,   720,   721,   722,   723,   724,   725,   726,   727,
     728,   729,   730,   731,   732,   735,   736,   737,   738,   791,
     792, -1199, -1199,   -51,  -171,   793,    44,    44, -1199,    44,
     794,   795,   796,   797,   798,   799,  -171,  -171,  -171,  -171,
    -171,  -171,   800,   815,   817,   818,   820,   821,   822,   823,
     825,   827,   835,   836,   837,   838,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    44,
      27,    27,    27,    27,    27,    27,    27,    27,    27,    27,
      27,    27,    27,    27,    44,    44,    44,    44,    44,   801,
     802,   803,   804,   805,   840,   841,   842,   843,   845,   846,
     847,   848,   850,   851,   852,   853,   855,   856,   857,   860,
     863,   868,   869,   938,   939,  1016,  1017,  1022,  1023,  1024,
    1025,  1026,  1027,  1028,  1029,  1030,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    44, -1199,   806,  -171, -1199,
   -1199, -1199,   809, -1199, -1199, -1199, -1199, -1199, -1199, -1199,
   -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199,
   -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199,   813,   814,
     816,   819,   824,   826,   828,   829,   830,   831,   832,   833,
     834,   839,   854,   862,   864,   865,   866,   867,   870,   871,
     872,   873,   874,   875,   876,   877,   858,   880,   881,   882,
     883,   812,   884,   885,   886,   887, -1199, -1199, -1199, -1199,
   -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199,
   -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199,
   -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199,
   -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199,
   -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199,  -171, -1199,
      44,    27,    27,    27,    27,    27,    27,    27,    27,    27,
      27,    27,    27,    27,    27,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    27,
      27,    27,    27,    27,    44,    44,    44,    44,    44, -1199,
   -1199,   889,   890,   891,   892,   893,   894,   895,   896,   897,
     898,   899,   900,   901,   916, -1199, -1199, -1199, -1199, -1199,
   -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199,   811,
     849,   859,   878,   879,   919,   922,   924,   925,   928,    44,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    44,    27,    27,
      27,    27,    27, -1199, -1199, -1199, -1199, -1199, -1199, -1199,
   -1199, -1199, -1199, -1199, -1199, -1199, -1199,   -46,   -34,   -29,
     -24,   -19,   926,   927,   929,   930,   935,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44, -1199, -1199, -1199,
   -1199, -1199,   -14,    -9,    -4,     1,     6,    44,    44,    44,
      44,    44, -1199, -1199, -1199, -1199, -1199
  };

  const unsigned short int
   SmaliParser ::yydefact_[] =
  {
       2,     0,     1,     0,     3,    20,     0,     0,    20,    20,
      14,     0,     0,     0,     0,    40,    51,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      65,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   113,   114,
     115,   116,   117,   118,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   166,     0,     0,     0,     0,     0,   172,   173,     0,
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
       0,     0,     0,   278,     0,     5,     7,     8,     9,    10,
      11,     4,    12,    13,     6,    21,     0,    16,    17,     0,
       0,    44,    45,    46,    47,    48,    41,    42,    30,    29,
      28,     0,    31,    32,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    61,    62,    63,    64,    66,
      67,    68,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    80,    81,     0,     0,     0,     0,     0,
      37,     0,     0,    90,     0,    91,    92,    93,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    37,
      37,    37,    37,    37,     0,     0,     0,     0,     0,     0,
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
       0,     0,     0,    26,    27,    23,    24,    25,   279,    22,
      15,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    38,     0,     0,     0,    43,     0,     0,     0,     0,
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
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,     0,     0,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    69,    70,    71,    49,    50,    72,
      73,    74,    75,    76,    77,    78,    79,    82,     0,    84,
      85,     0,     0,     0,     0,    89,    94,    95,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   107,
     108,   109,   110,   111,   112,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    18,    35,     0,     0,     0,     0,     0,    39,     0,
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
       0,     0,     0,     0,     0,     0,    36,     0,     0,    83,
      86,    87,     0,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,    19,     0,   281,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   280,
      88,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    34,    34,    34,    34,    34,     0,     0,
       0,     0,     0,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,    34,    34,    34,    34,   161,   162,   163,
     164,   165,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   167,   168,   169,   170,   171
  };

  const short int
   SmaliParser ::yypgoto_[] =
  {
   -1199, -1199, -1199, -1199, -1199, -1199, -1199, -1199,   114,  -242,
     844,   -13, -1198,  -270, -1199, -1199,   -56,     7, -1199, -1199
  };

  const short int
   SmaliParser ::yydefgoto_[] =
  {
      -1,     1,   245,   246,   247,   248,   249,   250,   256,   498,
     273,   922,   923,   532,   251,   252,   315,   266,   729,   253
  };

  const unsigned short int
   SmaliParser ::yytable_[] =
  {
     274,   316,   317,   268,   269,   270,   271,   272,   268,   269,
     270,   271,   272,   742,   742,   743,   807,   501,   502,   267,
     268,   269,   270,   271,   272,   268,   269,   270,   271,   272,
     268,   269,   270,   271,   272,   268,   269,   270,   271,   272,
     268,   269,   270,   271,   272,   268,   269,   270,   271,   272,
     268,   269,   270,   271,   272,   268,   269,   270,   271,   272,
     268,   269,   270,   271,   272,  1287,  1288,  1289,  1290,  1291,
     499,   499,   535,   742,   493,   808,   500,   494,   254,   495,
     496,   742,   493,   809,   497,   494,   255,   495,   496,   742,
     257,   810,   497,   261,   262,   263,   264,   265,   268,   269,
     270,   271,   272,   258,  1312,  1313,  1314,  1315,  1316,   597,
     598,   599,   600,   601,   268,   269,   270,   742,   272,   811,
     727,   728,   259,   260,   275,   276,   277,   310,   278,   279,
     280,   281,   282,   311,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   312,   313,   314,   318,   319,   379,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   356,   357,   358,   359,   360,   361,   362,
     363,   364,   365,   366,   367,   368,   369,   370,   371,   505,
     372,   373,   374,   375,   376,   377,   378,   380,   381,   382,
     383,   384,   385,   386,   387,   388,   389,   390,   391,   392,
     393,   394,   395,   396,   397,   398,   399,   400,   401,   402,
     403,   404,   405,   406,   407,   408,   409,   410,   411,   412,
     413,   414,   415,   416,   417,   418,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   428,   429,   430,   431,   432,
     433,   434,   435,   436,   437,   438,   439,   440,  1045,   441,
     442,   443,   444,  1297,   445,   446,   447,   448,   449,   450,
     451,   452,   453,   454,   455,  1298,   456,   457,   458,   459,
    1299,   460,   461,   462,   463,  1300,   464,   465,   466,   467,
    1301,   468,   469,   470,   471,  1317,   472,   473,   474,   475,
    1318,   476,   477,   478,   479,  1319,   480,   481,   482,   483,
    1320,   484,   485,   486,   487,  1321,   488,   489,   490,   491,
     492,   504,   506,   507,   531,   533,   508,   509,   510,   511,
     512,   513,     0,   514,   515,   516,   517,   518,   519,     0,
       0,   520,   521,   522,   523,   524,     0,   525,   526,   602,
     527,   528,   529,   530,   534,   536,   537,   538,   539,   603,
     540,   541,   542,   543,   544,   604,   545,   546,   547,   548,
     549,   550,   551,   552,   553,   554,   555,   556,   605,   606,
       0,     0,     0,     0,     0,   715,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   733,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   716,   557,   717,   713,   718,
     719,   720,   721,   722,   723,     0,   738,   739,   734,     0,
       0,     0,     0,     0,     0,   735,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   745,     0,
     746,   747,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   759,   760,   761,   762,   763,   764,     0,
       0,   741,   558,   748,   749,   750,   751,   752,   714,   744,
     559,   560,   736,   737,   561,   562,   740,   563,   564,   712,
     753,   754,   724,   725,   726,   755,   730,   731,   732,   756,
     757,   758,   765,   766,   767,   768,   769,   770,   771,   772,
     773,   774,   775,   776,   777,   778,   779,   780,   781,   782,
     783,   784,   785,   786,   787,   788,   789,   790,   791,   792,
     817,   818,   819,   820,   821,   822,   823,   812,   824,   825,
     793,   794,   795,   796,   797,   798,   799,   800,   801,   802,
     803,   804,   805,   806,   826,   827,   828,   829,   565,   830,
     831,   832,   833,   566,   834,   835,   836,   837,   567,   838,
     839,   840,   841,   568,   842,   843,   844,   845,   569,   846,
     847,   848,   849,   570,   850,   851,   852,   853,   571,   854,
     855,   856,   857,   572,   858,   859,   860,   861,   573,   862,
     863,   864,   865,   866,   574,   575,   576,   867,   868,   577,
     578,   579,   580,   581,   582,   583,   584,   585,   586,   587,
     588,   589,   590,   591,   592,   593,   594,   595,   925,   596,
     607,   608,   869,   609,   610,   611,   612,   613,   614,   615,
     616,   617,   870,   618,   619,   620,   621,   622,   871,   623,
     624,   625,   626,   627,   628,   629,   630,   631,   632,   633,
     634,   872,   873,   635,   636,   637,   638,   639,   921,   640,
     641,   642,   643,   644,   645,   646,   647,   648,   649,   650,
     651,   652,   653,   654,   655,   656,   657,   658,   659,   660,
     661,   662,   663,   664,   665,   666,   667,   668,  1092,  1093,
    1094,  1095,  1096,  1097,  1098,  1099,  1100,  1101,  1102,  1103,
    1104,  1105,   669,   670,   671,   672,   673,   674,   675,   676,
     677,   678,   679,   680,   681,   682,   683,   684,   685,   686,
     687,   688,   689,   690,   691,   692,   693,   694,   695,   696,
     697,   698,   699,   700,   701,   702,   703,   704,   705,   706,
     707,   708,   709,   710,   711,   874,   875,   813,   814,   815,
     816,   876,   877,   878,   879,   880,   881,   882,   883,   884,
     885,   886,   887,   888,   889,   890,   891,   892,   893,   894,
     895,   896,   897,   898,   899,   900,   901,   902,   903,   904,
     905,   906,   907,   908,   909,   910,   911,   912,   913,   914,
     915,   916,   917,   918,   919,   920,   928,   930,   989,   990,
     991,   992,   993,     0,     0,     0,   924,  1053,  1054,  1055,
    1056,  1057,  1064,   926,   927,   929,   931,   932,   933,   934,
     935,   936,   937,   938,   939,   940,   941,  1065,  1047,  1066,
    1067,   942,  1068,  1069,  1070,  1071,   943,  1072,   970,  1073,
    1058,  1059,  1060,  1061,  1062,  1063,   944,  1074,  1075,  1076,
    1077,   945,  1116,  1117,  1118,  1119,   946,  1120,  1121,  1122,
    1123,   947,  1124,  1125,  1126,  1127,   948,  1128,  1129,  1130,
    1046,   949,  1131,  1049,  1050,  1132,  1051,   950,   951,   952,
    1133,  1134,   953,   954,   955,   956,   957,   958,   959,  1211,
    1212,  1213,  1214,  1215,  1216,  1217,  1218,  1219,  1220,  1221,
    1222,  1223,  1224,  1078,  1079,  1080,  1081,  1082,  1083,  1084,
    1085,  1086,  1087,  1088,  1089,  1090,  1091,  1239,  1240,  1241,
    1242,  1243,   960,   961,   962,   963,   964,   965,   966,   967,
     968,  1106,  1107,  1108,  1109,  1110,   969,   971,   972,   973,
     974,   975,   976,   977,   978,   979,   980,   981,   982,   983,
    1135,  1136,  1169,   984,   985,   986,   987,   988,   994,   995,
     996,   997,   998,   999,  1000,  1001,  1002,  1003,  1004,  1005,
    1006,  1007,  1008,  1009,  1010,  1011,  1012,  1013,  1014,  1015,
    1016,  1017,  1018,  1019,  1020,  1021,  1292,  1293,  1294,  1295,
    1296,  1022,  1167,  1148,  1149,  1150,  1151,  1152,  1153,  1154,
    1155,  1156,  1157,  1158,  1159,  1160,  1161,  1162,  1163,  1164,
    1165,  1166,  1023,  1024,  1025,  1026,  1027,  1028,  1029,  1030,
    1031,  1032,  1033,  1034,  1035,  1036,  1037,  1038,  1137,  1138,
    1039,  1040,  1041,  1042,  1139,  1140,  1141,  1142,  1143,  1144,
    1145,  1146,  1147,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1209,     0,     0,   503,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1043,  1044,     0,     0,
    1048,  1052,     0,     0,     0,     0,     0,     0,  1111,  1112,
    1113,  1114,  1115,  1168,  1170,  1171,  1172,  1204,  1173,  1263,
       0,  1174,     0,     0,     0,     0,  1175,  1210,  1176,     0,
    1177,  1178,  1179,  1180,  1181,  1182,  1183,     0,     0,     0,
       0,  1184,  1225,  1226,  1227,  1228,  1229,  1230,  1231,  1232,
    1233,  1234,  1235,  1236,  1237,  1238,     0,  1264,  1185,     0,
    1199,  1244,  1245,  1246,  1247,  1248,  1186,  1265,  1187,  1188,
    1189,  1190,     0,     0,  1191,  1192,  1193,  1194,  1195,  1196,
    1197,  1198,  1200,  1201,  1202,  1203,  1266,  1267,     0,  1205,
    1206,  1207,  1208,  1249,  1250,  1251,  1252,  1253,  1254,  1255,
    1256,  1257,  1258,  1259,  1260,  1261,  1273,  1274,  1275,  1276,
    1277,  1278,  1279,  1280,  1281,  1282,  1283,  1284,  1285,  1286,
    1262,  1268,     2,     3,  1269,     4,  1270,  1271,     5,     6,
    1272,     7,     8,     0,  1302,  1303,     0,  1304,  1305,     9,
      10,    11,    12,  1306,  1046,  1046,  1046,  1046,  1046,    13,
      14,     0,     0,     0,  1307,  1308,  1309,  1310,  1311,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1046,
    1046,  1046,  1046,  1046,  1322,  1323,  1324,  1325,  1326,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    15,     0,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     243,     0,     0,     0,     0,     0,   244
  };

  const short int
   SmaliParser ::yycheck_[] =
  {
      13,    57,    58,    54,    55,    56,    57,    58,    54,    55,
      56,    57,    58,   335,   335,   337,   337,   259,   260,    12,
      54,    55,    56,    57,    58,    54,    55,    56,    57,    58,
      54,    55,    56,    57,    58,    54,    55,    56,    57,    58,
      54,    55,    56,    57,    58,    54,    55,    56,    57,    58,
      54,    55,    56,    57,    58,    54,    55,    56,    57,    58,
      54,    55,    56,    57,    58,  1263,  1264,  1265,  1266,  1267,
      51,    51,   314,   335,    55,   337,    56,    58,     3,    60,
      61,   335,    55,   337,    65,    58,    51,    60,    61,   335,
      56,   337,    65,    39,    40,    41,    42,    43,    54,    55,
      56,    57,    58,    62,  1302,  1303,  1304,  1305,  1306,   379,
     380,   381,   382,   383,    54,    55,    56,   335,    58,   337,
      39,    40,     8,     9,   336,    52,    52,   336,    52,    52,
      52,    52,    52,   336,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,   334,    52,    52,   336,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,   275,
      52,    52,    52,    52,    52,    52,    52,   336,   336,   336,
     336,   336,   336,   336,   336,   336,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,   339,    52,
      52,    52,    52,   339,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,   339,    52,    52,    52,    52,
     339,    52,    52,    52,    52,   339,    52,    52,    52,    52,
     339,    52,    52,    52,    52,   339,    52,    52,    52,    52,
     339,    52,    52,    52,    52,   339,    52,    52,    52,    52,
     339,    52,    52,    52,    52,   339,    52,    52,    52,    52,
      52,   336,   335,   335,    52,    52,   335,   335,   335,   335,
     335,   335,    -1,   335,   335,   335,   335,   335,   335,    -1,
      -1,   335,   335,   335,   335,   335,    -1,   335,   335,    52,
     335,   335,   335,   335,   335,   335,   335,   335,   335,    52,
     335,   335,   335,   335,   335,    52,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,    52,    52,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,   335,    52,   504,    52,
      52,    52,    52,    52,    52,    -1,    52,    52,    62,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   534,    -1,
     536,   537,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   549,   550,   551,   552,   553,   554,    -1,
      -1,    52,   335,    52,    52,    52,    52,    52,   331,   331,
     335,   335,   525,   526,   335,   335,   529,   335,   335,   338,
      52,    52,   515,   516,   517,    52,   519,   520,   521,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,   331,    52,    52,
     583,   584,   585,   586,   587,   588,   589,   590,   591,   592,
     593,   594,   595,   596,    52,    52,    52,    52,   335,    52,
      52,    52,    52,   335,    52,    52,    52,    52,   335,    52,
      52,    52,    52,   335,    52,    52,    52,    52,   335,    52,
      52,    52,    52,   335,    52,    52,    52,    52,   335,    52,
      52,    52,    52,   335,    52,    52,    52,    52,   335,    52,
      52,    52,    52,    52,   335,   335,   335,    52,    52,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   714,   335,
     335,   335,    52,   335,   335,   335,   335,   335,   335,   335,
     335,   335,    52,   335,   335,   335,   335,   335,    52,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,    52,    52,   335,   335,   335,   335,   335,   711,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   970,   971,
     972,   973,   974,   975,   976,   977,   978,   979,   980,   981,
     982,   983,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   334,    52,    52,   331,   331,   331,
     331,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    -1,    -1,    -1,   331,    52,    52,    52,
      52,    52,    52,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,    52,   924,    52,
      52,   335,    52,    52,    52,    52,   335,    52,   332,    52,
     936,   937,   938,   939,   940,   941,   335,    52,    52,    52,
      52,   335,    52,    52,    52,    52,   335,    52,    52,    52,
      52,   335,    52,    52,    52,    52,   335,    52,    52,    52,
     923,   335,    52,   926,   927,    52,   929,   335,   335,   335,
      52,    52,   335,   335,   335,   335,   335,   335,   335,  1171,
    1172,  1173,  1174,  1175,  1176,  1177,  1178,  1179,  1180,  1181,
    1182,  1183,  1184,   956,   957,   958,   959,   960,   961,   962,
     963,   964,   965,   966,   967,   968,   969,  1199,  1200,  1201,
    1202,  1203,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   984,   985,   986,   987,   988,   335,   332,   332,   332,
     332,   332,   332,   332,   332,   332,   332,   332,   332,   332,
      52,    52,  1048,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,  1268,  1269,  1270,  1271,
    1272,   335,  1045,  1026,  1027,  1028,  1029,  1030,  1031,  1032,
    1033,  1034,  1035,  1036,  1037,  1038,  1039,  1040,  1041,  1042,
    1043,  1044,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,    52,    52,
     335,   335,   335,   335,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1168,    -1,    -1,   271,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   335,   335,    -1,    -1,
     337,   337,    -1,    -1,    -1,    -1,    -1,    -1,   337,   337,
     337,   337,   337,   337,   335,   332,   332,   335,   332,   338,
      -1,   332,    -1,    -1,    -1,    -1,   332,  1170,   332,    -1,
     332,   332,   332,   332,   332,   332,   332,    -1,    -1,    -1,
      -1,   332,  1185,  1186,  1187,  1188,  1189,  1190,  1191,  1192,
    1193,  1194,  1195,  1196,  1197,  1198,    -1,   338,   334,    -1,
     332,  1204,  1205,  1206,  1207,  1208,   334,   338,   334,   334,
     334,   334,    -1,    -1,   334,   334,   334,   334,   334,   334,
     334,   334,   332,   332,   332,   332,   338,   338,    -1,   335,
     335,   335,   335,   334,   334,   334,   334,   334,   334,   334,
     334,   334,   334,   334,   334,   334,  1249,  1250,  1251,  1252,
    1253,  1254,  1255,  1256,  1257,  1258,  1259,  1260,  1261,  1262,
     334,   332,     0,     1,   332,     3,   332,   332,     6,     7,
     332,     9,    10,    -1,   338,   338,    -1,   338,   338,    17,
      18,    19,    20,   338,  1287,  1288,  1289,  1290,  1291,    27,
      28,    -1,    -1,    -1,  1297,  1298,  1299,  1300,  1301,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1312,
    1313,  1314,  1315,  1316,  1317,  1318,  1319,  1320,  1321,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    -1,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     328,    -1,    -1,    -1,    -1,    -1,   334
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
     297,   298,   299,   328,   334,   348,   349,   350,   351,   352,
     353,   360,   361,   365,     3,    51,   354,    56,    62,   354,
     354,    39,    40,    41,    42,    43,   363,   363,    54,    55,
      56,    57,    58,   356,   357,   336,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
     336,   336,    52,    52,   334,   362,   362,   362,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,   336,
     336,   336,   336,   336,   336,   336,   336,   336,   336,    52,
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
      52,    52,    52,    55,    58,    60,    61,    65,   355,    51,
      56,   355,   355,   356,   336,   362,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,    52,   359,    52,   335,   355,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   359,   359,   359,
     359,   359,    52,    52,    52,    52,    52,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   334,   338,   362,   331,    52,    52,    52,    52,    52,
      52,    52,    52,    52,   363,   363,   363,    39,    40,   364,
     363,   363,   363,    41,    62,    62,   357,   357,    52,    52,
     357,    52,   335,   337,   331,   362,   362,   362,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,   362,
     362,   362,   362,   362,   362,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,   357,   357,   357,   357,   357,   357,   357,
     357,   357,   357,   357,   357,   357,   357,   337,   337,   337,
     337,   337,   331,   331,   331,   331,   331,    52,    52,    52,
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
      52,   357,   357,   358,   331,   362,   335,   335,    52,   335,
      52,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     332,   332,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   332,   332,   332,   335,   335,   335,   335,   335,    52,
      52,    52,    52,    52,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   339,   357,   362,   337,   357,
     357,   357,   337,    52,    52,    52,    52,    52,   362,   362,
     362,   362,   362,   362,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,   357,   357,
     357,   357,   357,   357,   357,   357,   357,   357,   357,   357,
     357,   357,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   355,   357,   357,   357,   357,
     357,   337,   337,   337,   337,   337,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,   363,   363,
     363,   363,   363,   363,   363,   363,   363,   363,   363,   363,
     363,   363,   363,   363,   363,   363,   363,   357,   337,   362,
     335,   332,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   332,   332,   332,   332,   334,   334,   334,   334,   334,
     334,   334,   334,   334,   334,   334,   334,   334,   334,   332,
     332,   332,   332,   332,   335,   335,   335,   335,   335,   362,
     357,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   357,   357,   357,   357,   357,
     357,   357,   357,   357,   357,   357,   357,   357,   357,   355,
     355,   355,   355,   355,   357,   357,   357,   357,   357,   334,
     334,   334,   334,   334,   334,   334,   334,   334,   334,   334,
     334,   334,   334,   338,   338,   338,   338,   338,   332,   332,
     332,   332,   332,   357,   357,   357,   357,   357,   357,   357,
     357,   357,   357,   357,   357,   357,   357,   358,   358,   358,
     358,   358,   355,   355,   355,   355,   355,   339,   339,   339,
     339,   339,   338,   338,   338,   338,   338,   357,   357,   357,
     357,   357,   358,   358,   358,   358,   358,   339,   339,   339,
     339,   339,   357,   357,   357,   357,   357
  };

  const unsigned short int
   SmaliParser ::yyr1_[] =
  {
       0,   346,   347,   347,   347,   347,   347,   348,   348,   348,
     348,   348,   348,   348,   348,   349,   350,   351,   352,   353,
     354,   354,   354,   355,   355,   355,   355,   355,   356,   356,
     356,   356,   357,   357,   358,   358,   358,   359,   359,   359,
     360,   361,   361,   362,   363,   363,   363,   363,   363,   364,
     364,   365,   365,   365,   365,   365,   365,   365,   365,   365,
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
     365,   365
  };

  const unsigned char
   SmaliParser ::yyr2_[] =
  {
       0,     2,     0,     2,     2,     2,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     2,     2,     5,     7,
       0,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     0,     1,     2,     0,     1,     3,
       1,     2,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     2,     2,     2,     2,     1,     2,     2,     2,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       2,     2,     4,     6,     4,     4,     6,     6,     8,     4,
       2,     2,     2,     2,     4,     4,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     4,     4,     4,
       4,     4,     4,     1,     1,     1,     1,     1,     1,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,    10,    10,    10,    10,    10,    10,    10,
      10,    10,    10,    10,    10,    10,    10,     8,     8,     8,
       8,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,    12,    12,    12,    12,    12,     1,    14,    14,    14,
      14,    14,     1,     1,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     1,     2,
       8,     7
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
     493,   494,   497,   504,   505,   506,   507,   508,   512,   513,
     514,   515,   519,   520,   524,   525,   529,   535,   536,   540,
     546,   552,   555,   562,   566,   569,   572,   575,   578,   584,
     585,   590,   593,   596,   599,   602,   605,   608,   611,   614,
     617,   620,   623,   626,   629,   632,   635,   638,   641,   644,
     647,   650,   653,   659,   662,   665,   668,   673,   676,   679,
     682,   685,   688,   691,   694,   697,   700,   703,   706,   712,
     715,   718,   721,   724,   727,   730,   733,   736,   739,   742,
     745,   748,   751,   754,   757,   760,   763,   766,   769,   772,
     775,   778,   781,   784,   787,   790,   793,   796,   799,   802,
     805,   808,   811,   814,   817,   820,   823,   826,   829,   832,
     835,   838,   841,   844,   847,   850,   853,   856,   859,   862,
     865,   868,   871,   874,   877,   880,   883,   886,   889,   892,
     895,   898,   901,   904,   907,   910,   913,   916,   919,   922,
     925,   928,   931,   934,   937,   940,   943,   946,   949,   952,
     955,   958,   961,   964,   967,   970,   973,   976,   979,   982,
     985,   988,   991,   994,   997,  1000,  1003,  1006,  1009,  1012,
    1015,  1018,  1021,  1024,  1027,  1030,  1033,  1036,  1039,  1042,
    1045,  1048,  1051,  1054,  1057,  1060,  1063,  1066,  1069,  1072,
    1075,  1078,  1081,  1084,  1087,  1090,  1093,  1096,  1099,  1102,
    1105,  1108,  1111,  1114,  1117,  1120,  1123,  1126,  1129,  1132,
    1135,  1138,  1141,  1144,  1147,  1150,  1153,  1156,  1159,  1162,
    1165,  1168,  1171,  1174,  1177,  1180,  1183,  1186,  1189,  1192,
    1195,  1198,  1201,  1204,  1207,  1210,  1213,  1216,  1219,  1222,
    1225,  1228,  1231,  1234,  1237,  1240,  1243,  1246,  1249,  1252,
    1255,  1258,  1261,  1264,  1267,  1270,  1273,  1276,  1307,  1310,
    1313,  1316
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
#line 4134 "SmaliParser.cpp" // lalr1.cc:1167
#line 1321 "SmaliParser.yy" // lalr1.cc:1168


void Analysis::SmaliParser::error(const location &loc, const std::string &message) {
	cout << "Parse error: " << message << endl
	    << "Error location: " << loc << endl << driver.mLexer->text() << endl;
}
