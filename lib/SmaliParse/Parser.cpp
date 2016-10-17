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
#line 41 "Parser.yy" // lalr1.cc:397

    #include <iostream>
    #include "Lexer.h"
    #include "Parser.hpp"
    #include "location.hh"
    #include "Interpreter.h"
    #include "Lexer.h"
    #include "utils/Defs.h"

    static Analysis::Parser::symbol_type yylex(Analysis::Lexer &lexer
                                    , Analysis::Interpreter &driver ) {
        return lexer.get_next_token();
    }
    using namespace std;
    using namespace Analysis;

#line 51 "Parser.cpp" // lalr1.cc:397


// First part of user declarations.

#line 56 "Parser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "Parser.hpp"

// User implementation prologue.

#line 70 "Parser.cpp" // lalr1.cc:412


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

#line 9 "Parser.yy" // lalr1.cc:479
namespace  Analysis  {
#line 156 "Parser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
   Parser ::yytnamerr_ (const char *yystr)
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
   Parser :: Parser  (Analysis::Lexer &lexer_yyarg, Analysis::Interpreter &driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      lexer (lexer_yyarg),
      driver (driver_yyarg)
  {}

   Parser ::~ Parser  ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
   Parser ::by_state::by_state ()
    : state (empty_state)
  {}

  inline
   Parser ::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
   Parser ::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
   Parser ::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
   Parser ::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
   Parser ::symbol_number_type
   Parser ::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
   Parser ::stack_symbol_type::stack_symbol_type ()
  {}


  inline
   Parser ::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 311: // instruction
        value.move< OpCode* > (that.value);
        break;

      case 20: // "flag"
      case 21: // "v(p)x"
      case 298: // exp
      case 299: // classdef
      case 300: // superdef
      case 301: // srcdef
      case 302: // fielddef
      case 303: // methoddef
      case 304: // flags
      case 308: // registers
        value.move< int > (that.value);
        break;

      case 295: // "number"
      case 310: // NUMBER
        value.move< long long int > (that.value);
        break;

      case 4: // "c type string"
      case 5: // "name string"
      case 6: // "comment"
      case 7: // "class name"
      case 8: // "class type"
      case 22: // "0xnumber"
      case 23: // HEXNUMBERSTRING
      case 307: // comment
      case 309: // jmplabel
        value.move< std::string > (that.value);
        break;

      case 306: // regs
        value.move< std::vector<int> > (that.value);
        break;

      case 305: // args
        value.move< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
   Parser ::stack_symbol_type&
   Parser ::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 311: // instruction
        value.copy< OpCode* > (that.value);
        break;

      case 20: // "flag"
      case 21: // "v(p)x"
      case 298: // exp
      case 299: // classdef
      case 300: // superdef
      case 301: // srcdef
      case 302: // fielddef
      case 303: // methoddef
      case 304: // flags
      case 308: // registers
        value.copy< int > (that.value);
        break;

      case 295: // "number"
      case 310: // NUMBER
        value.copy< long long int > (that.value);
        break;

      case 4: // "c type string"
      case 5: // "name string"
      case 6: // "comment"
      case 7: // "class name"
      case 8: // "class type"
      case 22: // "0xnumber"
      case 23: // HEXNUMBERSTRING
      case 307: // comment
      case 309: // jmplabel
        value.copy< std::string > (that.value);
        break;

      case 306: // regs
        value.copy< std::vector<int> > (that.value);
        break;

      case 305: // args
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
   Parser ::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
   Parser ::yy_print_ (std::ostream& yyo,
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
   Parser ::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
   Parser ::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
   Parser ::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
   Parser ::debug_stream () const
  {
    return *yycdebug_;
  }

  void
   Parser ::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


   Parser ::debug_level_type
   Parser ::debug_level () const
  {
    return yydebug_;
  }

  void
   Parser ::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline  Parser ::state_type
   Parser ::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
   Parser ::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
   Parser ::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
   Parser ::parse ()
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
      case 311: // instruction
        yylhs.value.build< OpCode* > ();
        break;

      case 20: // "flag"
      case 21: // "v(p)x"
      case 298: // exp
      case 299: // classdef
      case 300: // superdef
      case 301: // srcdef
      case 302: // fielddef
      case 303: // methoddef
      case 304: // flags
      case 308: // registers
        yylhs.value.build< int > ();
        break;

      case 295: // "number"
      case 310: // NUMBER
        yylhs.value.build< long long int > ();
        break;

      case 4: // "c type string"
      case 5: // "name string"
      case 6: // "comment"
      case 7: // "class name"
      case 8: // "class type"
      case 22: // "0xnumber"
      case 23: // HEXNUMBERSTRING
      case 307: // comment
      case 309: // jmplabel
        yylhs.value.build< std::string > ();
        break;

      case 306: // regs
        yylhs.value.build< std::vector<int> > ();
        break;

      case 305: // args
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
#line 389 "Parser.yy" // lalr1.cc:859
    {yyerrok; driver.mLexer->beginInitial();}
#line 658 "Parser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 398 "Parser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 1; driver.addOpcode(yystack_[0].value.as< OpCode* > ());}
#line 664 "Parser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 399 "Parser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 1; driver.endMethod();}
#line 670 "Parser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 402 "Parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 1;
        driver.setClassDefine(yystack_[1].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 678 "Parser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 406 "Parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 1;
        driver.setSuperDefine(yystack_[0].value.as< std::string > ());
    }
#line 686 "Parser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 410 "Parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 1;
        driver.setSourceDefine(yystack_[0].value.as< std::string > ());
    }
#line 694 "Parser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 414 "Parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 1;
        driver.addField(yystack_[2].value.as< std::string > (), yystack_[3].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 702 "Parser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 418 "Parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 1;
        driver.addMethod(yystack_[4].value.as< std::string > (), yystack_[5].value.as< int > (), yystack_[0].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > ());
    }
#line 710 "Parser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 422 "Parser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 0;}
#line 716 "Parser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 423 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< int > () = yystack_[0].value.as< int > ();
    }
#line 724 "Parser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 426 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< int > () = yystack_[1].value.as< int > ();
        yylhs.value.as< int > () |= yystack_[0].value.as< int > ();
    }
#line 733 "Parser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 432 "Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();}
#line 739 "Parser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 433 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();
        yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
    }
#line 748 "Parser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 437 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::vector<std::string> > () = yystack_[1].value.as< std::vector<std::string> > ();
        yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
    }
#line 757 "Parser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 443 "Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<int> > () = std::vector<int>();}
#line 763 "Parser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 444 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::vector<int> > () = std::vector<int>();
        yylhs.value.as< std::vector<int> > ().push_back(yystack_[0].value.as< int > ());
    }
#line 772 "Parser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 448 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::vector<int> > () = yystack_[2].value.as< std::vector<int> > ();
        yylhs.value.as< std::vector<int> > ().push_back(yystack_[0].value.as< int > ());
    }
#line 781 "Parser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 454 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();
    }
#line 789 "Parser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 460 "Parser.yy" // lalr1.cc:859
    {
        driver.setCurMethodRegSize(yystack_[0].value.as< long long int > ());
    }
#line 797 "Parser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 466 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();
    }
#line 805 "Parser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 470 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< long long int > () = strtoll(yystack_[0].value.as< std::string > ().c_str(), 0, 10);
     }
#line 813 "Parser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 473 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< long long int > () = strtoll(yystack_[0].value.as< std::string > ().c_str(), 0, 16);
     }
#line 821 "Parser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 478 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NOP(OP_NOP, driver.stringPool());
    }
#line 829 "Parser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 481 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 837 "Parser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 484 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_FROM16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 845 "Parser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 487 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 853 "Parser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 490 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_WIDE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 861 "Parser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 493 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_WIDE_FROM16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 869 "Parser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 496 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_WIDE_16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 877 "Parser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 499 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_OBJECT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 885 "Parser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 502 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_OBJECT_FROM16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 893 "Parser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 505 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_OBJECT_16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 901 "Parser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 508 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_MOVE_RESULT(OP_MOVE_RESULT, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 909 "Parser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 511 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_MOVE_RESULT(OP_MOVE_RESULT_WIDE, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 917 "Parser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 514 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_MOVE_RESULT(OP_MOVE_RESULT_OBJECT, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 925 "Parser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 517 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE_EXCEPTION(OP_MOVE_EXCEPTION, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 933 "Parser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 520 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_RETURN_VOID(OP_RETURN_VOID, driver.stringPool());
    }
#line 941 "Parser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 523 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_RETURN(OP_RETURN, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 949 "Parser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 526 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_RETURN(OP_RETURN_WIDE, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 957 "Parser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 529 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_RETURN(OP_RETURN_OBJECT, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 965 "Parser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 532 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_4, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 973 "Parser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 535 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 981 "Parser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 538 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 989 "Parser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 541 "Parser.yy" // lalr1.cc:859
    {
        auto number = yystack_[0].value.as< std::string > ().substr (0, yystack_[0].value.as< std::string > ().length () - 4);
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_HIGH16, driver.stringPool(), yystack_[2].value.as< int > (),
                         strtoll(number.c_str(), 0, 16));

    }
#line 1000 "Parser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 547 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_WIDE_16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 1008 "Parser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 550 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_WIDE_32, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 1016 "Parser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 553 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_WIDE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 1024 "Parser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 556 "Parser.yy" // lalr1.cc:859
    {
        auto number = yystack_[0].value.as< std::string > ().substr (0, yystack_[0].value.as< std::string > ().length () - 12);
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_WIDE_HIGH16, driver.stringPool(), yystack_[2].value.as< int > (),
                        strtoll(number.c_str(), 0, 16));
    }
#line 1034 "Parser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 561 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CONST_STRING(OP_CONST_STRING, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1042 "Parser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 564 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CONST_STRING(OP_CONST_STRING_JUMBO, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1050 "Parser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 567 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CONST_CLASS(OP_CONST_CLASS, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1058 "Parser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 570 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MONITOR(OP_MONITOR_ENTER, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1066 "Parser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 573 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MONITOR(OP_MONITOR_EXIT, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1074 "Parser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 576 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CHECK_CAST(OP_CHECK_CAST, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1082 "Parser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 579 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INSTANCE_OF(OP_INSTANCE_OF, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
   }
#line 1090 "Parser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 582 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_ARRAY_LENGTH(OP_ARRAY_LENGTH, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1098 "Parser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 585 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_NEW_INSTANCE(OP_NEW_INSTANCE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1106 "Parser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 588 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEW_ARRAY(OP_NEW_ARRAY, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1114 "Parser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 591 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_FILLED_NEW_ARRAY(OP_FILLED_NEW_ARRAY, driver.stringPool(), yystack_[3].value.as< std::vector<int> > (), yystack_[0].value.as< std::string > ());
    }
#line 1122 "Parser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 594 "Parser.yy" // lalr1.cc:859
    {
       std::vector<int> regs;
       regs.push_back(yystack_[5].value.as< int > ());
       regs.push_back(yystack_[3].value.as< int > ());
       yylhs.value.as< OpCode* > () = new Op_FILLED_NEW_ARRAY(OP_FILLED_NEW_ARRAY_RANGE, driver.stringPool(), regs, yystack_[0].value.as< std::string > ());
    }
#line 1133 "Parser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 600 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_FILL_ARRAY_DATA(OP_FILL_ARRAY_DATA, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1141 "Parser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 603 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_THROW(OP_THROW, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1149 "Parser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 606 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_GOTO(OP_GOTO, driver.stringPool(), yystack_[0].value.as< std::string > ());
    }
#line 1157 "Parser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 609 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_GOTO(OP_GOTO_16, driver.stringPool(), yystack_[0].value.as< std::string > ());
    }
#line 1165 "Parser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 612 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_GOTO(OP_GOTO_32, driver.stringPool(), yystack_[0].value.as< std::string > ());
    }
#line 1173 "Parser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 615 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_SWITCH(OP_PACKED_SWITCH, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1181 "Parser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 618 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_SWITCH(OP_SPARSE_SWITCH, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1189 "Parser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 621 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CMP(OP_CMPL_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1197 "Parser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 624 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CMP(OP_CMPG_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1205 "Parser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 627 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CMP(OP_CMPL_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1213 "Parser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 630 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CMP(OP_CMPG_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1221 "Parser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 633 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CMP(OP_CMP_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1229 "Parser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 636 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_EQ, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1237 "Parser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 639 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_NE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1245 "Parser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 642 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_LT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1253 "Parser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 645 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_GE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1261 "Parser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 648 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_GT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1269 "Parser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 651 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_LE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1277 "Parser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 654 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_EQZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1285 "Parser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 657 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_NEZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1293 "Parser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 660 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_LTZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1301 "Parser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 663 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_GEZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1309 "Parser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 666 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_GTZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1317 "Parser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 669 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_LEZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1325 "Parser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 678 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1333 "Parser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 681 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_WIDE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1341 "Parser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 684 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_OBJECT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1349 "Parser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 687 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_BOOLEAN, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1357 "Parser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 690 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_BYTE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1365 "Parser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 693 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_CHAR, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1373 "Parser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 696 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_SHORT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1381 "Parser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 699 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1389 "Parser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 702 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT_WIDE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1397 "Parser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 705 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT_OBJECT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1405 "Parser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 708 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT_BOOLEAN, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1413 "Parser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 711 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT_BYTE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1421 "Parser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 714 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT_CHAR, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1429 "Parser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 717 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT_SHORT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1437 "Parser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 720 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1445 "Parser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 723 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET_WIDE, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1453 "Parser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 726 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET_OBJECT, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1461 "Parser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 729 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET_BOOLEAN, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1469 "Parser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 732 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET_BYTE, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1477 "Parser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 735 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET_CHAR, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1485 "Parser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 738 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET_SHORT, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1493 "Parser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 741 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1501 "Parser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 744 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT_WIDE, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1509 "Parser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 747 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT_OBJECT, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1517 "Parser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 750 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT_BOOLEAN, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1525 "Parser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 753 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT_BYTE, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1533 "Parser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 756 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT_CHAR, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1541 "Parser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 759 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT_SHORT, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1549 "Parser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 762 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1557 "Parser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 765 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_WIDE, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1565 "Parser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 768 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_OBJECT, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1573 "Parser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 771 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_BOOLEAN, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1581 "Parser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 774 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_BYTE, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1589 "Parser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 777 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_CHAR, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1597 "Parser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 780 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_SHORT, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1605 "Parser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 783 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1613 "Parser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 786 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_WIDE, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1621 "Parser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 789 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_OBJECT, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1629 "Parser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 792 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_BOOLEAN, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1637 "Parser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 795 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_BYTE, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1645 "Parser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 798 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_CHAR, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1653 "Parser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 801 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_SHORT, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1661 "Parser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 804 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE(OP_INVOKE_VIRTUAL, driver.stringPool(), yystack_[9].value.as< std::vector<int> > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1669 "Parser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 807 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE(OP_INVOKE_SUPER, driver.stringPool(), yystack_[9].value.as< std::vector<int> > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1677 "Parser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 810 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE(OP_INVOKE_DIRECT, driver.stringPool(), yystack_[9].value.as< std::vector<int> > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1685 "Parser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 813 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE(OP_INVOKE_STATIC, driver.stringPool(), yystack_[9].value.as< std::vector<int> > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1693 "Parser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 816 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE(OP_INVOKE_INTERFACE, driver.stringPool(), yystack_[9].value.as< std::vector<int> > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1701 "Parser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 820 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE_X_RANGE(OP_INVOKE_VIRTUAL_RANGE, driver.stringPool(), yystack_[11].value.as< int > (), yystack_[9].value.as< int > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1709 "Parser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 823 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE_X_RANGE(OP_INVOKE_SUPER_RANGE, driver.stringPool(), yystack_[11].value.as< int > (), yystack_[9].value.as< int > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1717 "Parser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 826 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE_X_RANGE(OP_INVOKE_DIRECT_RANGE, driver.stringPool(), yystack_[11].value.as< int > (), yystack_[9].value.as< int > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1725 "Parser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 829 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE_X_RANGE(OP_INVOKE_STATIC_RANGE, driver.stringPool(), yystack_[11].value.as< int > (), yystack_[9].value.as< int > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1733 "Parser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 832 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE_X_RANGE(OP_INVOKE_INTERFACE_RANGE, driver.stringPool(), yystack_[11].value.as< int > (), yystack_[9].value.as< int > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1741 "Parser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 837 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEGNOT_X(OP_NEG_INT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1749 "Parser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 840 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEGNOT_X(OP_NOT_INT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1757 "Parser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 843 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEGNOT_X(OP_NEG_LONG, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1765 "Parser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 846 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEGNOT_X(OP_NOT_LONG, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1773 "Parser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 849 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEGNOT_X(OP_NEG_FLOAT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1781 "Parser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 852 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEGNOT_X(OP_NEG_DOUBLE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1789 "Parser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 855 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_INT_TO_LONG, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1797 "Parser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 858 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_INT_TO_FLOAT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1805 "Parser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 861 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_INT_TO_DOUBLE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1813 "Parser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 864 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_LONG_TO_INT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1821 "Parser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 867 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_LONG_TO_FLOAT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1829 "Parser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 870 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_LONG_TO_DOUBLE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1837 "Parser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 873 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_FLOAT_TO_INT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1845 "Parser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 876 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_FLOAT_TO_LONG, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1853 "Parser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 879 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_FLOAT_TO_DOUBLE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1861 "Parser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 882 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_DOUBLE_TO_INT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1869 "Parser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 885 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_DOUBLE_TO_LONG, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1877 "Parser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 888 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_DOUBLE_TO_FLOAT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1885 "Parser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 891 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_INT_TO_BYTE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1893 "Parser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 894 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_INT_TO_CHAR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1901 "Parser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 897 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_INT_TO_SHORT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1909 "Parser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 900 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_ADD_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1917 "Parser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 903 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_SUB_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1925 "Parser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 906 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_MUL_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1933 "Parser.cpp" // lalr1.cc:859
    break;

  case 181:
#line 909 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_DIV_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1941 "Parser.cpp" // lalr1.cc:859
    break;

  case 182:
#line 912 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_REM_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1949 "Parser.cpp" // lalr1.cc:859
    break;

  case 183:
#line 915 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_AND_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1957 "Parser.cpp" // lalr1.cc:859
    break;

  case 184:
#line 918 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_OR_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1965 "Parser.cpp" // lalr1.cc:859
    break;

  case 185:
#line 921 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_XOR_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1973 "Parser.cpp" // lalr1.cc:859
    break;

  case 186:
#line 924 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_SHL_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1981 "Parser.cpp" // lalr1.cc:859
    break;

  case 187:
#line 927 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_SHR_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1989 "Parser.cpp" // lalr1.cc:859
    break;

  case 188:
#line 930 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_USHR_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1997 "Parser.cpp" // lalr1.cc:859
    break;

  case 189:
#line 933 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_ADD_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2005 "Parser.cpp" // lalr1.cc:859
    break;

  case 190:
#line 936 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_SUB_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2013 "Parser.cpp" // lalr1.cc:859
    break;

  case 191:
#line 939 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_MUL_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2021 "Parser.cpp" // lalr1.cc:859
    break;

  case 192:
#line 942 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_DIV_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2029 "Parser.cpp" // lalr1.cc:859
    break;

  case 193:
#line 945 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_REM_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2037 "Parser.cpp" // lalr1.cc:859
    break;

  case 194:
#line 948 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_AND_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2045 "Parser.cpp" // lalr1.cc:859
    break;

  case 195:
#line 951 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_OR_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2053 "Parser.cpp" // lalr1.cc:859
    break;

  case 196:
#line 954 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_XOR_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2061 "Parser.cpp" // lalr1.cc:859
    break;

  case 197:
#line 957 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_SHL_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2069 "Parser.cpp" // lalr1.cc:859
    break;

  case 198:
#line 960 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_SHR_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2077 "Parser.cpp" // lalr1.cc:859
    break;

  case 199:
#line 963 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_USHR_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2085 "Parser.cpp" // lalr1.cc:859
    break;

  case 200:
#line 966 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT(OP_ADD_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2093 "Parser.cpp" // lalr1.cc:859
    break;

  case 201:
#line 969 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT(OP_SUB_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2101 "Parser.cpp" // lalr1.cc:859
    break;

  case 202:
#line 972 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT(OP_MUL_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2109 "Parser.cpp" // lalr1.cc:859
    break;

  case 203:
#line 975 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT(OP_DIV_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2117 "Parser.cpp" // lalr1.cc:859
    break;

  case 204:
#line 978 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT(OP_REM_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2125 "Parser.cpp" // lalr1.cc:859
    break;

  case 205:
#line 981 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE(OP_ADD_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2133 "Parser.cpp" // lalr1.cc:859
    break;

  case 206:
#line 984 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE(OP_SUB_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2141 "Parser.cpp" // lalr1.cc:859
    break;

  case 207:
#line 987 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE(OP_MUL_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2149 "Parser.cpp" // lalr1.cc:859
    break;

  case 208:
#line 990 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE(OP_DIV_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2157 "Parser.cpp" // lalr1.cc:859
    break;

  case 209:
#line 993 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE(OP_REM_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2165 "Parser.cpp" // lalr1.cc:859
    break;

  case 210:
#line 996 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_ADD_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2173 "Parser.cpp" // lalr1.cc:859
    break;

  case 211:
#line 999 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_SUB_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2181 "Parser.cpp" // lalr1.cc:859
    break;

  case 212:
#line 1002 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_MUL_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2189 "Parser.cpp" // lalr1.cc:859
    break;

  case 213:
#line 1005 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_DIV_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2197 "Parser.cpp" // lalr1.cc:859
    break;

  case 214:
#line 1008 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_REM_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2205 "Parser.cpp" // lalr1.cc:859
    break;

  case 215:
#line 1011 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_AND_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2213 "Parser.cpp" // lalr1.cc:859
    break;

  case 216:
#line 1014 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_OR_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2221 "Parser.cpp" // lalr1.cc:859
    break;

  case 217:
#line 1017 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_XOR_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2229 "Parser.cpp" // lalr1.cc:859
    break;

  case 218:
#line 1020 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_SHL_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2237 "Parser.cpp" // lalr1.cc:859
    break;

  case 219:
#line 1023 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_SHR_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2245 "Parser.cpp" // lalr1.cc:859
    break;

  case 220:
#line 1026 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_USHR_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2253 "Parser.cpp" // lalr1.cc:859
    break;

  case 221:
#line 1029 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_ADD_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2261 "Parser.cpp" // lalr1.cc:859
    break;

  case 222:
#line 1032 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_SUB_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2269 "Parser.cpp" // lalr1.cc:859
    break;

  case 223:
#line 1035 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_MUL_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2277 "Parser.cpp" // lalr1.cc:859
    break;

  case 224:
#line 1038 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_DIV_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2285 "Parser.cpp" // lalr1.cc:859
    break;

  case 225:
#line 1041 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_REM_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2293 "Parser.cpp" // lalr1.cc:859
    break;

  case 226:
#line 1044 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_AND_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2301 "Parser.cpp" // lalr1.cc:859
    break;

  case 227:
#line 1047 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_OR_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2309 "Parser.cpp" // lalr1.cc:859
    break;

  case 228:
#line 1050 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_XOR_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2317 "Parser.cpp" // lalr1.cc:859
    break;

  case 229:
#line 1053 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_SHL_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2325 "Parser.cpp" // lalr1.cc:859
    break;

  case 230:
#line 1056 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_SHR_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2333 "Parser.cpp" // lalr1.cc:859
    break;

  case 231:
#line 1059 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_USHR_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2341 "Parser.cpp" // lalr1.cc:859
    break;

  case 232:
#line 1062 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT_2ADDR(OP_ADD_FLOAT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2349 "Parser.cpp" // lalr1.cc:859
    break;

  case 233:
#line 1065 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT_2ADDR(OP_SUB_FLOAT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2357 "Parser.cpp" // lalr1.cc:859
    break;

  case 234:
#line 1068 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT_2ADDR(OP_MUL_FLOAT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2365 "Parser.cpp" // lalr1.cc:859
    break;

  case 235:
#line 1071 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT_2ADDR(OP_DIV_FLOAT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2373 "Parser.cpp" // lalr1.cc:859
    break;

  case 236:
#line 1074 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT_2ADDR(OP_REM_FLOAT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2381 "Parser.cpp" // lalr1.cc:859
    break;

  case 237:
#line 1077 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE_2ADDR(OP_ADD_DOUBLE_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2389 "Parser.cpp" // lalr1.cc:859
    break;

  case 238:
#line 1080 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE_2ADDR(OP_SUB_DOUBLE_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2397 "Parser.cpp" // lalr1.cc:859
    break;

  case 239:
#line 1083 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE_2ADDR(OP_MUL_DOUBLE_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2405 "Parser.cpp" // lalr1.cc:859
    break;

  case 240:
#line 1086 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE_2ADDR(OP_DIV_DOUBLE_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2413 "Parser.cpp" // lalr1.cc:859
    break;

  case 241:
#line 1089 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE_2ADDR(OP_REM_DOUBLE_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2421 "Parser.cpp" // lalr1.cc:859
    break;

  case 242:
#line 1092 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_ADD_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2429 "Parser.cpp" // lalr1.cc:859
    break;

  case 243:
#line 1095 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_RSUB_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2437 "Parser.cpp" // lalr1.cc:859
    break;

  case 244:
#line 1098 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_MUL_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2445 "Parser.cpp" // lalr1.cc:859
    break;

  case 245:
#line 1101 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_DIV_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2453 "Parser.cpp" // lalr1.cc:859
    break;

  case 246:
#line 1104 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_REM_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2461 "Parser.cpp" // lalr1.cc:859
    break;

  case 247:
#line 1107 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_AND_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2469 "Parser.cpp" // lalr1.cc:859
    break;

  case 248:
#line 1110 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_OR_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2477 "Parser.cpp" // lalr1.cc:859
    break;

  case 249:
#line 1113 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_XOR_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2485 "Parser.cpp" // lalr1.cc:859
    break;

  case 250:
#line 1116 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_ADD_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2493 "Parser.cpp" // lalr1.cc:859
    break;

  case 251:
#line 1119 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_RSUB_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2501 "Parser.cpp" // lalr1.cc:859
    break;

  case 252:
#line 1122 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_MUL_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2509 "Parser.cpp" // lalr1.cc:859
    break;

  case 253:
#line 1125 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_DIV_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2517 "Parser.cpp" // lalr1.cc:859
    break;

  case 254:
#line 1128 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_REM_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2525 "Parser.cpp" // lalr1.cc:859
    break;

  case 255:
#line 1131 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_AND_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2533 "Parser.cpp" // lalr1.cc:859
    break;

  case 256:
#line 1134 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_OR_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2541 "Parser.cpp" // lalr1.cc:859
    break;

  case 257:
#line 1137 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_XOR_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2549 "Parser.cpp" // lalr1.cc:859
    break;

  case 258:
#line 1140 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_SHL_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2557 "Parser.cpp" // lalr1.cc:859
    break;

  case 259:
#line 1143 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_SHR_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2565 "Parser.cpp" // lalr1.cc:859
    break;

  case 260:
#line 1146 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_USHR_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< long long int > ());
    }
#line 2573 "Parser.cpp" // lalr1.cc:859
    break;

  case 290:
#line 1178 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_JmpLabel(OP_JMPLABEL, driver.stringPool(), yystack_[0].value.as< std::string > ());
    }
#line 2581 "Parser.cpp" // lalr1.cc:859
    break;

  case 291:
#line 1181 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CATCH(OP_CATCH, driver.stringPool(), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 2589 "Parser.cpp" // lalr1.cc:859
    break;


#line 2593 "Parser.cpp" // lalr1.cc:859
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
   Parser ::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
   Parser ::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const short int  Parser ::yypact_ninf_ = -967;

  const signed char  Parser ::yytable_ninf_ = -1;

  const short int
   Parser ::yypact_[] =
  {
    -967,     9,  -967,     2,  -967,  -967,    13,   297,   330,    13,
      13,  -967,   308,  -967,   314,   315,   316,   322,   324,   325,
     326,   327,   328,   329,   331,   332,   333,  -967,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,    53,
      60,   355,   356,    92,    92,    92,   358,   359,   360,   361,
     362,   363,   364,   365,   366,   367,   368,   369,   370,   371,
     372,   373,   374,   375,   376,  -967,  -967,  -967,  -967,  -967,
    -967,   377,   378,   379,   380,   381,   382,   383,   384,   385,
     386,   387,   388,   389,   390,   391,   392,   393,   394,   395,
     396,   397,   398,   399,   400,   401,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,   412,   413,   414,   415,
     416,   417,   418,   149,   150,   151,   152,   153,  -967,   154,
     155,   156,   157,   158,  -967,  -967,   429,   430,   431,   432,
     433,   434,   435,   436,   437,   438,   439,   440,   441,   442,
     443,   444,   445,   446,   447,   448,   449,   450,   451,   452,
     453,   454,   455,   456,   457,   458,   459,   460,   461,   462,
     463,   464,   465,   467,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   479,   480,   487,   507,   508,   509,   510,
     511,   512,   513,   514,   515,   516,   517,   518,   519,   520,
     521,   522,   523,   524,   525,   526,   527,   528,   529,   530,
     531,   532,   533,   534,   535,   536,   537,   538,   539,   540,
     541,   542,   543,   544,   545,   546,   547,   548,   549,   550,
     551,   552,   553,   554,   555,   556,   557,   558,   559,   560,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,   574,
     578,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,   284,  -967,  -967,    12,   292,  -967,  -967,  -967,
     295,   296,   298,   299,   300,   301,   302,   303,   304,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,   305,   306,   307,   309,
     310,   311,   312,   313,   317,   318,   319,  -967,  -967,   320,
     321,   357,   419,   420,   565,   576,   421,  -967,   598,  -967,
    -967,  -967,   422,   423,   424,   425,   426,   427,   428,   466,
     468,   469,   481,   482,   483,   484,   485,   486,   488,   489,
     490,   491,   492,   493,   494,   495,   496,   497,   498,   499,
     500,   501,   502,   503,   504,   505,   506,   561,   562,   563,
     564,   566,   567,   568,   569,   570,   571,   572,   573,   575,
     577,   579,   580,   581,   582,   583,   584,   585,   586,   587,
     588,   589,   590,   565,   565,   565,   565,   565,   591,   592,
     593,   594,   595,   602,   603,   604,   605,   606,   607,   608,
     609,   610,   611,   612,   613,   614,   615,   616,   617,   618,
     619,   620,   621,   622,   623,   624,   625,   626,   627,   628,
     629,   630,   631,   632,   633,   634,   635,   636,   637,   638,
     639,   640,   641,   642,   643,   644,   645,   646,   647,   648,
     649,   650,   651,   652,   653,   654,   655,   656,   657,   658,
     659,   660,   661,   662,   663,   664,   665,   666,   667,   668,
     669,   670,   671,   672,   673,   674,   675,   676,   677,   678,
     679,   680,   681,   682,   683,   684,   685,   686,   687,   688,
     689,   690,   691,   692,   693,   694,   695,   696,   697,   698,
     699,   700,   701,   702,   703,   704,   706,   705,  -967,  -967,
    -967,   596,   597,   599,   600,   601,   707,   708,   709,   710,
     711,   712,   308,   308,   308,   713,   308,   308,   308,   714,
     715,   716,   717,   718,   719,   720,   726,   721,  -967,    29,
     722,    92,  -967,    92,    92,   723,   724,   725,   727,   728,
     729,   730,   731,   732,   733,   735,    92,    92,    92,    92,
      92,    92,   738,   739,   740,   741,   742,   743,   744,   745,
     746,   747,   748,   755,   775,   776,   777,   778,   779,   780,
     781,   782,   783,   784,   785,   786,   787,   788,   789,   790,
     804,   805,   806,   807,   808,   809,   810,   811,   812,   813,
     814,   815,   816,   817,    30,    31,    35,    36,    37,   734,
     736,   737,   749,   750,   818,   819,   820,   821,   822,   823,
     824,   825,   826,   827,   828,   833,   842,   844,   846,   859,
     860,   862,   976,   977,   978,   979,   980,   981,   982,   983,
     984,   985,   986,   987,   988,   989,   990,   991,   992,   993,
     995,   996,   997,   998,   999,  1000,  1001,  1002,  1003,  1004,
    1005,  1007,  1010,  1011,  1012,  1013,  1014,  1015,  1016,  1017,
    1018,  1019,  1020,  1023,  1024,  1025,  1026,  1027,  1028,  1029,
    1030,  1031,  1032,  1033,  1034,  1035,  1036,  1037,  1038,  1039,
    1040,  1041,  1042,  1043,  1044,  1045,  1046,  1047,  1048,  1049,
    1050,  1051,  1052,  1053,  1054,  1055,  1056,  1057,  1058,  1059,
    1060,  1061,  1062,  1063,  1064,  1065,  1066,  1067,    92,   829,
     830,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,   800,  -967,  -967,   801,  1070,   803,  1072,  -967,
    -967,  -967,   831,   832,   834,   835,   836,   837,   838,   839,
     840,   841,   843,  -967,  -967,  -967,  -967,  -967,  -967,   845,
     847,   848,   849,   850,   851,   852,   853,   854,   855,   856,
     857,   858,   861,   863,   864,   865,   866,   868,   869,   870,
     871,   872,   873,   874,   875,   876,   877,   878,   879,   880,
     881,   882,   883,   884,   885,   886,   887,   888,   889,   890,
     891,   893,   894,   895,   896,   897,  1073,  1074,  1075,  1076,
    1077,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,   898,   899,   900,   901,   902,   903,   904,   905,
     906,   907,   908,   909,   910,   911,   912,   913,   914,   915,
     916,   917,   918,   919,   920,   921,   922,   923,   924,   925,
     926,   927,   928,   929,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,   930,   931,   932,   933,
     934,   935,   936,   937,   938,   939,   940,   941,   942,   943,
     944,   945,   946,   947,   948,   949,  -967,  -967,     3,  1091,
    1092,  -967,  1093,   951,  1081,  1082,  1083,  1084,  1085,    92,
      92,    92,    92,    92,    92,  1086,  1087,  1088,  1089,  1090,
    1094,  1095,  1096,  1097,  1098,  1101,  1110,  1112,  1114,  1104,
    1105,  1106,  1140,  1141,  1143,  1159,  1230,  1231,  1232,  1233,
    1236,  1237,  1238,  1242,  1243,  1244,  1245,  1246,  1247,  1248,
    1249,  1250,  1251,  1252,  1253,  1254,  1255,  1256,  1257,  1258,
    1259,  1260,   969,   970,   971,   994,  1006,  1261,  1262,  1263,
    1264,  1266,  1267,  1268,  1269,  1270,  1271,  1272,  1273,  1274,
    1275,  1276,  1278,  1279,  1280,  1281,  1282,  1283,  1284,  1285,
    1286,  1287,  1288,  1289,  1290,  1291,  1292,  1293,  1294,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,    92,  -967,
    1265,  -967,  -967,  -967,  1068,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    1069,  1071,  1078,  1079,  1080,  1099,  1100,  1102,  1103,  1107,
    1108,  1109,  1111,  1113,  1116,  1118,  1119,  1120,  1121,  1122,
    1123,  1124,  1125,  1126,  1127,  1128,  1129,  1130,  1131,  1132,
    1133,  1134,  1135,  1137,  1138,  1139,  1142,  1144,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  1145,
    -967,  1308,  1312,  1313,  1314,  1315,  1316,  1317,  1318,  1319,
    1320,  1321,  1322,  1323,  1324,  1325,  1326,  1327,  1328,  1329,
    1330,  1331,  1332,  1333,  1334,  1335,  1336,  1337,  1338,  1339,
    1343,  1344,  1345,  1346,  1347,  1348,  1350,  1352,  1354,  1355,
      92,  -967,  1146,  1148,  1149,  1150,  1152,  1153,  1154,  1155,
    1156,  1157,  1158,  1160,  1161,  1162,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    1163,  1164,  1165,  1166,  1167,  1168,  1169,  1170,  1171,  1172,
    -967,  1356,  1357,  1358,  1359,  1363,  1364,  1365,  1366,  1367,
    1368,  1369,  1370,  1371,  1372,   830,   830,   830,   830,   830,
    1349,  1376,  1377,  1378,  1379,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,     5,
       6,     8,    10,    18,  1176,  1177,  1178,  1179,  1180,  1380,
    1383,  1386,  1387,  1388,   830,   830,   830,   830,   830,  -967,
    -967,  -967,  -967,  -967,    19,    20,    21,    22,    23,  1392,
    1409,  1410,  1411,  1412,  -967,  -967,  -967,  -967,  -967
  };

  const unsigned short int
   Parser ::yydefact_[] =
  {
       2,     0,     1,     0,     3,    29,    20,     0,     0,    20,
      20,    14,     0,    34,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    48,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    96,    97,    98,    99,   100,
     101,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   149,     0,
       0,     0,     0,     0,   155,   156,     0,     0,     0,     0,
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
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,     0,
       0,     5,     7,     8,     9,    10,    11,     4,    12,    13,
       6,    21,     0,    16,    17,     0,     0,    32,    33,    30,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    44,
      45,    46,    47,    49,    50,    51,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    63,    64,     0,
       0,     0,     0,     0,    26,     0,     0,    73,     0,    74,
      75,    76,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    26,    26,    26,    26,    26,     0,     0,
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
       0,     0,     0,     0,     0,     0,     0,     0,   290,    15,
      22,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    27,     0,
       0,     0,    31,     0,     0,     0,     0,     0,     0,     0,
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
      23,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    65,     0,    67,    68,     0,     0,     0,     0,    72,
      77,    78,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    90,    91,    92,    93,    94,    95,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    18,    24,     0,     0,
       0,    28,     0,     0,     0,     0,     0,     0,     0,     0,
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
       0,     0,     0,     0,     0,     0,     0,     0,     0,    25,
       0,    66,    69,    70,     0,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,     0,
      19,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    71,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     291,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    23,    23,    23,    23,    23,
       0,     0,     0,     0,     0,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    23,    23,    23,    23,    23,   144,
     145,   146,   147,   148,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   150,   151,   152,   153,   154
  };

  const short int
   Parser ::yypgoto_[] =
  {
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,   323,  -966,
     -80,  -967,  -967,   -54,  -520,  -967
  };

  const short int
   Parser ::yydefgoto_[] =
  {
      -1,     1,   271,   272,   273,   274,   275,   276,   282,   928,
     539,   277,   278,   329,   289,   279
  };

  const unsigned short int
   Parser ::yytable_[] =
  {
     330,   331,   730,   731,   732,   280,   734,   735,   736,     2,
       3,  1049,     4,  1049,  1049,     5,  1049,   511,  1049,     6,
       7,     8,     9,    10,    11,    12,  1049,  1049,  1049,  1049,
    1049,  1049,   510,   281,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,  1050,   509,  1299,  1300,   270,  1301,   512,  1302,  1289,
    1290,  1291,  1292,  1293,   510,   283,  1303,  1319,  1320,  1321,
    1322,  1323,   510,   604,   605,   606,   607,   608,   746,   746,
     746,   747,   811,   812,   746,   746,   746,   813,   814,   815,
     287,   288,   285,   286,   284,   290,   291,   292,  1314,  1315,
    1316,  1317,  1318,   293,   324,   294,   295,   296,   297,   298,
     299,   325,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   326,   327,   328,   332,
     333,   334,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   356,   357,   358,   359,   360,   361,   362,
     363,   364,   365,   366,   367,   368,   369,   370,   371,   372,
     373,   374,   375,   376,   377,   378,   379,   380,   381,   382,
     383,   384,   385,   386,   387,   388,   389,   390,   391,   392,
     393,   394,   395,   396,   397,   398,   399,   400,   401,   402,
     403,   404,   405,   406,   407,   408,   409,   410,   411,   412,
     413,   414,   415,   416,   417,   418,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   428,   429,   430,   431,   432,
     433,   434,   435,   436,   437,   438,   439,   749,   440,   750,
     751,   441,   442,   443,   444,   445,   446,   447,   448,   449,
     450,   451,   763,   764,   765,   766,   767,   768,   452,  1150,
    1151,  1152,  1153,  1154,  1155,  1156,  1157,  1158,  1159,  1160,
    1161,  1162,  1163,  1164,  1165,  1166,  1167,  1168,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   513,   514,   538,   515,   516,   517,
     518,   519,   520,   521,   522,   523,   524,   540,   525,   526,
     527,   528,   529,   542,     0,     0,   530,   531,   532,   533,
     534,     0,   609,   610,   611,   612,   613,     0,     0,     0,
     721,   722,   723,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   535,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   925,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   536,   537,
     541,   543,   544,   545,   546,   547,   548,   549,     0,   738,
     739,     0,     0,     0,     0,   740,   741,     0,   724,   725,
     726,   727,   728,   729,   744,     0,   733,   737,     0,     0,
     742,   743,   745,     0,   752,   753,   754,     0,   755,   756,
     757,   758,   759,   760,   761,   550,   762,   551,   552,   769,
     770,   771,   772,   773,   774,   775,   776,   777,   778,   779,
     553,   554,   555,   556,   557,   558,   780,   559,   560,   561,
     562,   563,   564,   565,   566,   567,   568,   569,   570,   571,
     572,   573,   574,   575,   576,   577,   781,   782,   783,   784,
     785,   786,   787,   788,   789,   790,   791,   792,   793,   794,
     795,   796,   797,   798,   799,   800,   801,   802,   803,   804,
     805,   806,   807,   808,   809,   810,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   926,   927,   821,
     822,   823,   824,   825,   826,   827,   828,   829,   830,   831,
     578,   579,   580,   581,   832,   582,   583,   584,   585,   586,
     587,   588,   589,   833,   590,   834,   591,   835,   592,   593,
     594,   595,   596,   597,   598,   599,   600,   601,   602,   603,
     836,   837,   719,   838,   720,  1060,  1061,  1062,  1063,  1064,
    1065,   614,   615,   616,   617,   618,   619,   620,   621,   622,
     623,   624,   625,   626,   627,   628,   629,   630,   631,   632,
     633,   634,   635,   636,   637,   638,   639,   640,   641,   642,
     643,   644,   645,   646,   647,   648,   649,   650,   651,   652,
     653,   654,   655,   656,   657,   658,   659,   660,   661,   662,
     663,   664,   665,   666,   667,   668,   669,   670,   671,   672,
     673,   674,   675,   676,   677,   678,   679,   680,   681,   682,
     683,   684,   685,   686,   687,   688,   689,   690,   691,   692,
     693,   694,   695,   696,   697,   698,   699,   700,   701,   702,
     703,   704,   705,   706,   707,   708,   709,   710,   711,   712,
     713,   714,   715,   716,  1169,   717,   718,   839,   840,   841,
     842,   843,   844,   845,   846,   847,   848,   849,   850,   851,
     852,   853,   854,   855,   856,   748,   857,   858,   859,   860,
     861,   862,   863,   864,   865,   866,   867,   816,   868,   817,
     818,   869,   870,   871,   872,   873,   874,   875,   876,   877,
     878,   879,   819,   820,   880,   881,   882,   883,   884,   885,
     886,   887,   888,   889,   890,   891,   892,   893,   894,   895,
     896,   897,   898,   899,   900,   901,   902,   903,   904,   905,
     906,   907,   908,   909,   910,   911,   912,   913,   914,   915,
     916,   917,   918,   919,   920,   921,   922,   923,   924,   929,
     930,   931,   932,   933,   992,   993,   994,   995,   996,  1051,
    1052,  1053,  1055,  1056,  1057,  1058,  1059,  1066,  1067,  1068,
    1069,  1070,  1080,  1081,  1082,  1071,  1072,  1073,  1074,  1075,
     934,   935,  1076,   936,   937,   938,   939,   940,   941,   942,
     943,  1077,   944,  1078,   945,  1079,   946,   947,   948,   949,
     950,   951,   952,   953,   954,   955,   956,   957,  1083,  1084,
     958,  1085,   959,   960,   961,   962,  1250,   963,   964,   965,
     966,   967,   968,   969,   970,   971,   972,  1086,   973,   974,
     975,   976,   977,   978,   979,   980,   981,   982,   983,   984,
     985,   986,   987,   988,   989,   990,   991,   997,   998,   999,
    1000,  1001,  1002,  1003,  1004,  1005,  1006,  1007,  1008,  1009,
    1010,  1011,  1012,  1013,  1014,  1015,  1016,  1017,  1018,  1019,
    1020,  1021,  1022,  1023,  1024,  1025,  1026,  1027,  1028,  1029,
    1030,  1031,  1032,  1033,  1034,  1035,  1036,  1037,  1038,  1039,
    1040,  1041,  1042,  1043,  1044,  1045,  1046,  1047,  1087,  1088,
    1089,  1090,  1048,  1054,  1091,  1092,  1093,  1094,  1095,  1096,
    1097,  1098,  1099,  1100,  1101,  1102,  1103,  1104,  1105,  1106,
    1107,  1113,  1114,  1115,  1108,  1109,  1110,  1111,  1112,     0,
       0,     0,     0,  1170,     0,     0,     0,     0,     0,     0,
       0,     0,  1118,  1119,  1120,  1121,  1116,  1122,  1123,  1124,
    1125,  1126,  1127,  1128,  1129,  1130,  1131,  1132,  1117,  1133,
    1134,  1135,  1136,  1137,  1138,  1139,  1140,  1141,  1142,  1143,
    1144,  1145,  1146,  1147,  1148,  1149,  1211,  1212,  1213,  1214,
    1215,  1216,  1217,  1218,  1219,  1220,  1221,  1222,  1223,  1224,
    1225,     0,     0,     0,  1226,  1227,  1228,  1229,  1230,  1231,
    1232,  1233,  1234,  1235,  1236,  1237,  1238,  1239,  1240,  1241,
    1242,  1243,  1244,     0,  1294,     0,  1245,  1171,  1246,  1172,
    1247,  1173,  1248,  1249,  1275,  1276,  1277,  1278,  1174,  1175,
    1176,  1279,  1280,  1281,  1282,  1283,  1284,  1285,  1286,  1287,
    1288,  1295,  1296,  1297,  1298,     0,     0,     0,  1309,  1177,
    1178,  1310,  1179,  1180,  1311,  1312,  1313,  1181,  1182,  1183,
    1324,  1184,  1186,  1185,  1187,  1188,  1189,  1190,  1191,  1192,
    1193,  1194,  1195,  1196,  1197,  1198,  1199,  1325,  1326,  1327,
    1328,  1200,  1201,  1202,  1203,  1204,  1205,  1206,  1207,     0,
       0,  1208,  1251,  1209,  1252,  1253,  1254,  1210,  1255,  1256,
    1257,  1258,  1259,  1260,  1261,     0,  1262,  1263,  1264,     0,
    1265,  1266,  1267,  1268,  1269,     0,     0,     0,  1270,  1271,
    1272,  1273,  1274,  1304,  1305,  1306,  1307,  1308
  };

  const short int
   Parser ::yycheck_[] =
  {
      54,    55,   522,   523,   524,     3,   526,   527,   528,     0,
       1,     8,     3,     8,     8,     6,     8,     5,     8,    10,
      11,    12,    13,    14,    15,    16,     8,     8,     8,     8,
       8,     8,    20,    20,    25,    26,    27,    28,    29,    30,
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
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   288,     8,   288,   288,   286,   288,     5,   288,  1265,
    1266,  1267,  1268,  1269,    20,     8,   288,   288,   288,   288,
     288,   288,    20,   393,   394,   395,   396,   397,   289,   289,
     289,   292,   292,   292,   289,   289,   289,   292,   292,   292,
      22,    23,     9,    10,     4,    21,    21,    21,  1304,  1305,
    1306,  1307,  1308,    21,   291,    21,    21,    21,    21,    21,
      21,   291,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,   286,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
     291,   291,   291,   291,   291,   291,   291,   291,   291,   291,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,   541,    21,   543,
     544,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,   556,   557,   558,   559,   560,   561,    21,  1029,
    1030,  1031,  1032,  1033,  1034,  1035,  1036,  1037,  1038,  1039,
    1040,  1041,  1042,  1043,  1044,  1045,  1046,  1047,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,     8,     5,   289,   289,    21,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,    21,   289,   289,
     289,   289,   289,     5,    -1,    -1,   289,   289,   289,   289,
     289,    -1,    21,    21,    21,    21,    21,    -1,    -1,    -1,
      21,    21,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   289,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   718,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,    -1,     4,
       4,    -1,    -1,    -1,    -1,     8,     8,    -1,    21,    21,
      21,    21,    21,    21,     8,    -1,    23,    23,    -1,    -1,
      21,    21,    21,    -1,    21,    21,    21,    -1,    21,    21,
      21,    21,    21,    21,    21,   289,    21,   289,   289,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
     289,   289,   289,   289,   289,   289,    21,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,     8,     8,     8,     8,     8,     8,     8,     8,
       8,     8,     8,     8,     8,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,     8,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
     289,   289,   289,   289,    21,   289,   289,   289,   289,   289,
     289,   289,   289,    21,   289,    21,   289,    21,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
      21,    21,   286,    21,   287,   939,   940,   941,   942,   943,
     944,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,  1048,   289,   291,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,   293,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,   293,    21,   293,
     293,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,   293,   293,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,   289,
     289,    21,   289,    21,    21,    21,    21,    21,    21,     8,
       8,     8,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,     8,     8,     8,    21,    21,    21,    21,    21,
     289,   289,    21,   289,   289,   289,   289,   289,   289,   289,
     289,    21,   289,    21,   289,    21,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,     8,     8,
     289,     8,   289,   289,   289,   289,  1210,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,     8,   290,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   290,
     290,   290,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,     8,     8,
       8,     8,   293,   292,     8,     8,     8,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       5,   292,   292,   292,     8,     8,     8,     8,     8,    -1,
      -1,    -1,    -1,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    21,    21,    21,   292,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,   292,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,     8,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       5,    -1,    -1,    -1,     8,     8,     8,     8,     8,     8,
       8,     8,     8,     8,     8,     8,     8,     8,     5,     5,
       5,     5,     5,    -1,     5,    -1,     8,   289,     8,   290,
       8,   290,     8,     8,     8,     8,     8,     8,   290,   290,
     290,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,     5,     5,     5,     5,    -1,    -1,    -1,     8,   290,
     290,     8,   290,   290,     8,     8,     8,   290,   290,   290,
       8,   290,   286,   290,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,     8,     8,     8,
       8,   290,   290,   290,   290,   290,   289,   289,   289,    -1,
      -1,   289,   286,   289,   286,   286,   286,   292,   286,   286,
     286,   286,   286,   286,   286,    -1,   286,   286,   286,    -1,
     287,   287,   287,   287,   287,    -1,    -1,    -1,   290,   290,
     290,   290,   290,   287,   287,   287,   287,   287
  };

  const unsigned short int
   Parser ::yystos_[] =
  {
       0,   297,     0,     1,     3,     6,    10,    11,    12,    13,
      14,    15,    16,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     286,   298,   299,   300,   301,   302,   303,   307,   308,   311,
       3,    20,   304,     8,     4,   304,   304,    22,    23,   310,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,   291,   291,    21,    21,   286,   309,
     309,   309,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,   291,   291,   291,   291,   291,   291,   291,
     291,   291,   291,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,     8,     5,     8,
      20,     5,     5,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,    21,   306,
      21,   289,     5,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   306,   306,   306,   306,   306,    21,
      21,    21,    21,    21,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   291,   286,
     287,    21,    21,    21,    21,    21,    21,    21,    21,    21,
     310,   310,   310,    23,   310,   310,   310,    23,     4,     4,
       8,     8,    21,    21,     8,    21,   289,   292,   293,   309,
     309,   309,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,   309,   309,   309,   309,   309,   309,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,     8,     8,     8,
       8,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,   292,   292,   292,   292,   292,   293,   293,   293,   293,
     293,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,   309,     8,     8,   305,   289,
     289,    21,   289,    21,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   290,   290,   290,   290,   290,   290,   290,
     290,   290,   290,   290,   290,   290,   290,   289,   289,   289,
     289,   289,    21,    21,    21,    21,    21,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   293,     8,
     288,     8,     8,     8,   292,    21,    21,    21,    21,    21,
     309,   309,   309,   309,   309,   309,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
       8,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,     8,     8,     8,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     8,     8,
       8,     8,     8,   292,   292,   292,   292,   292,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
     310,   310,   310,   310,   310,   310,   310,   310,   310,   310,
     310,   310,   310,   310,   310,   310,   310,   310,   310,   309,
       8,   289,   290,   290,   290,   290,   290,   290,   290,   290,
     290,   290,   290,   290,   290,   290,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     290,   290,   290,   290,   290,   289,   289,   289,   289,   289,
     292,     8,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     8,     8,     8,     8,
       8,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       5,     5,     5,     5,     5,     8,     8,     8,     8,     8,
     309,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   287,   287,   287,   287,   287,
     290,   290,   290,   290,   290,     8,     8,     8,     8,     8,
       8,     8,     8,     8,     8,     8,     8,     8,     8,   305,
     305,   305,   305,   305,     5,     5,     5,     5,     5,   288,
     288,   288,   288,   288,   287,   287,   287,   287,   287,     8,
       8,     8,     8,     8,   305,   305,   305,   305,   305,   288,
     288,   288,   288,   288,     8,     8,     8,     8,     8
  };

  const unsigned short int
   Parser ::yyr1_[] =
  {
       0,   296,   297,   297,   297,   297,   297,   298,   298,   298,
     298,   298,   298,   298,   298,   299,   300,   301,   302,   303,
     304,   304,   304,   305,   305,   305,   306,   306,   306,   307,
     308,   309,   310,   310,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311
  };

  const unsigned char
   Parser ::yyr2_[] =
  {
       0,     2,     0,     2,     2,     2,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     2,     2,     5,     7,
       0,     1,     2,     0,     1,     2,     0,     1,     3,     1,
       2,     2,     1,     1,     1,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     2,     2,     2,     2,     1,     2,
       2,     2,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     2,     2,     4,     6,     4,     4,     6,
       6,     8,     4,     2,     2,     2,     2,     4,     4,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       4,     4,     4,     4,     4,     4,     1,     1,     1,     1,
       1,     1,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,    10,    10,    10,    10,
      10,    10,    10,    10,    10,    10,    10,    10,    10,    10,
       8,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,     8,     8,     8,    12,    12,    12,    12,    12,     1,
      14,    14,    14,    14,    14,     1,     1,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     8
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const  Parser ::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"end of line\"",
  "\"c type string\"", "\"name string\"", "\"comment\"", "\"class name\"",
  "\"class type\"", "\"begin of keywords\"", "\".class\"", "\".super\"",
  "\".source\"", "\".field\"", "\".method\"", "\".endmethod\"",
  "\".registers\"", "\".prologue\"", "\".line\"", "\"end of keywords\"",
  "\"flag\"", "\"v(p)x\"", "\"0xnumber\"", "HEXNUMBERSTRING",
  "\"begin of opcodes\"", "\"nop\"", "\"move\"", "\"move/from16\"",
  "\"move/16\"", "\"move-wide\"", "\"move-wide/from16\"",
  "\"move-wide/16\"", "\"move-object\"", "\"move-object/from16\"",
  "\"move-object/16\"", "\"move-result\"", "\"move-result-wide\"",
  "\"move-result-object\"", "\"move-exception\"", "\"return-void\"",
  "\"return\"", "\"return-wide\"", "\"return-object\"", "\"const/4\"",
  "\"const/16\"", "\"const\"", "\"const/high16\"", "\"const-wide/16\"",
  "\"const-wide/32\"", "\"const-wide\"", "\"const-wide/high16\"",
  "\"const-string\"", "\"const-string/jumbo\"", "\"const-class\"",
  "\"monitor-enter\"", "\"monitor-exit\"", "\"check-cast\"",
  "\"instance-of\"", "\"array-length\"", "\"new-instance\"",
  "\"new-array\"", "\"filled-new-array\"", "\"filled-new-array/range\"",
  "\"fill-array-data\"", "\"throw\"", "\"goto\"", "\"goto/16\"",
  "\"goto/32\"", "\"packed-switch\"", "\"sparse-switch\"",
  "\"cmpl-float\"", "\"cmpg-float\"", "\"cmpl-double\"", "\"cmpg-double\"",
  "\"cmp-long\"", "\"if-eq\"", "\"if-ne\"", "\"if-lt\"", "\"if-ge\"",
  "\"if-gt\"", "\"if-le\"", "\"if-eqz\"", "\"if-nez\"", "\"if-ltz\"",
  "\"if-gez\"", "\"if-gtz\"", "\"if-lez\"", "\"unused-3e\"",
  "\"unused-3f\"", "\"unused-40\"", "\"unused-41\"", "\"unused-42\"",
  "\"unused-43\"", "\"aget\"", "\"aget-wide\"", "\"aget-object\"",
  "\"aget-boolean\"", "\"aget-byte\"", "\"aget-char\"", "\"aget-short\"",
  "\"aput\"", "\"aput-wide\"", "\"aput-object\"", "\"aput-boolean\"",
  "\"aput-byte\"", "\"aput-char\"", "\"aput-short\"", "\"iget\"",
  "\"iget-wide\"", "\"iget-object\"", "\"iget-boolean\"", "\"iget-byte\"",
  "\"iget-char\"", "\"iget-short\"", "\"iput\"", "\"iput-wide\"",
  "\"iput-object\"", "\"iput-boolean\"", "\"iput-byte\"", "\"iput-char\"",
  "\"iput-short\"", "\"sget\"", "\"sget-wide\"", "\"sget-object\"",
  "\"sget-boolean\"", "\"sget-byte\"", "\"sget-char\"", "\"sget-short\"",
  "\"sput\"", "\"sput-wide\"", "\"sput-object\"", "\"sput-boolean\"",
  "\"sput-byte\"", "\"sput-char\"", "\"sput-short\"", "\"invoke-virtual\"",
  "\"invoke-super\"", "\"invoke-direct\"", "\"invoke-static\"",
  "\"invoke-interface\"", "\"unused-73\"", "\"invoke-virtual/range\"",
  "\"invoke-super/range\"", "\"invoke-direct/range\"",
  "\"invoke-static/range\"", "\"invoke-interface/range\"", "\"unused-79\"",
  "\"unused-7a\"", "\"neg-int\"", "\"not-int\"", "\"neg-long\"",
  "\"not-long\"", "\"neg-float\"", "\"neg-double\"", "\"int-to-long\"",
  "\"int-to-float\"", "\"int-to-double\"", "\"long-to-int\"",
  "\"long-to-float\"", "\"long-to-double\"", "\"float-to-int\"",
  "\"float-to-long\"", "\"float-to-double\"", "\"double-to-int\"",
  "\"double-to-long\"", "\"double-to-float\"", "\"int-to-byte\"",
  "\"int-to-char\"", "\"int-to-short\"", "\"add-int\"", "\"sub-int\"",
  "\"mul-int\"", "\"div-int\"", "\"rem-int\"", "\"and-int\"", "\"or-int\"",
  "\"xor-int\"", "\"shl-int\"", "\"shr-int\"", "\"ushr-int\"",
  "\"add-long\"", "\"sub-long\"", "\"mul-long\"", "\"div-long\"",
  "\"rem-long\"", "\"and-long\"", "\"or-long\"", "\"xor-long\"",
  "\"shl-long\"", "\"shr-long\"", "\"ushr-long\"", "\"add-float\"",
  "\"sub-float\"", "\"mul-float\"", "\"div-float\"", "\"rem-float\"",
  "\"add-double\"", "\"sub-double\"", "\"mul-double\"", "\"div-double\"",
  "\"rem-double\"", "\"add-int/2addr\"", "\"sub-int/2addr\"",
  "\"mul-int/2addr\"", "\"div-int/2addr\"", "\"rem-int/2addr\"",
  "\"and-int/2addr\"", "\"or-int/2addr\"", "\"xor-int/2addr\"",
  "\"shl-int/2addr\"", "\"shr-int/2addr\"", "\"ushr-int/2addr\"",
  "\"add-long/2addr\"", "\"sub-long/2addr\"", "\"mul-long/2addr\"",
  "\"div-long/2addr\"", "\"rem-long/2addr\"", "\"and-long/2addr\"",
  "\"or-long/2addr\"", "\"xor-long/2addr\"", "\"shl-long/2addr\"",
  "\"shr-long/2addr\"", "\"ushr-long/2addr\"", "\"add-float/2addr\"",
  "\"sub-float/2addr\"", "\"mul-float/2addr\"", "\"div-float/2addr\"",
  "\"rem-float/2addr\"", "\"add-double/2addr\"", "\"sub-double/2addr\"",
  "\"mul-double/2addr\"", "\"div-double/2addr\"", "\"rem-double/2addr\"",
  "\"add-int/lit16\"", "\"rsub-int\"", "\"mul-int/lit16\"",
  "\"div-int/lit16\"", "\"rem-int/lit16\"", "\"and-int/lit16\"",
  "\"or-int/lit16\"", "\"xor-int/lit16\"", "\"add-int/lit8\"",
  "\"rsub-int/lit8\"", "\"mul-int/lit8\"", "\"div-int/lit8\"",
  "\"rem-int/lit8\"", "\"and-int/lit8\"", "\"or-int/lit8\"",
  "\"xor-int/lit8\"", "\"shl-int/lit8\"", "\"shr-int/lit8\"",
  "\"ushr-int/lit8\"", "\"+iget-volatile\"", "\"+iput-volatile\"",
  "\"+sget-volatile\"", "\"+sput-volatile\"", "\"+iget-object-volatile\"",
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
  "\"unused-ff\"", "\".catch\"", "\"end of opcodes\"",
  "\".packed-switch\"", "\".end packed-switch\"", "\"begin of symbol\"",
  "\":\"", "\"(\"", "\")\"", "\",\"", "\"->\"", "\"{\"", "\"}\"", "\"..\"",
  "\"end of symbol\"", "\"number\"", "$accept", "program", "exp",
  "classdef", "superdef", "srcdef", "fielddef", "methoddef", "flags",
  "args", "regs", "comment", "registers", "jmplabel", "NUMBER",
  "instruction", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
   Parser ::yyrline_[] =
  {
       0,   385,   385,   386,   387,   388,   389,   392,   393,   394,
     395,   396,   397,   398,   399,   402,   406,   410,   414,   418,
     422,   423,   426,   432,   433,   437,   443,   444,   448,   454,
     460,   466,   470,   473,   478,   481,   484,   487,   490,   493,
     496,   499,   502,   505,   508,   511,   514,   517,   520,   523,
     526,   529,   532,   535,   538,   541,   547,   550,   553,   556,
     561,   564,   567,   570,   573,   576,   579,   582,   585,   588,
     591,   594,   600,   603,   606,   609,   612,   615,   618,   621,
     624,   627,   630,   633,   636,   639,   642,   645,   648,   651,
     654,   657,   660,   663,   666,   669,   672,   673,   674,   675,
     676,   677,   678,   681,   684,   687,   690,   693,   696,   699,
     702,   705,   708,   711,   714,   717,   720,   723,   726,   729,
     732,   735,   738,   741,   744,   747,   750,   753,   756,   759,
     762,   765,   768,   771,   774,   777,   780,   783,   786,   789,
     792,   795,   798,   801,   804,   807,   810,   813,   816,   819,
     820,   823,   826,   829,   832,   835,   836,   837,   840,   843,
     846,   849,   852,   855,   858,   861,   864,   867,   870,   873,
     876,   879,   882,   885,   888,   891,   894,   897,   900,   903,
     906,   909,   912,   915,   918,   921,   924,   927,   930,   933,
     936,   939,   942,   945,   948,   951,   954,   957,   960,   963,
     966,   969,   972,   975,   978,   981,   984,   987,   990,   993,
     996,   999,  1002,  1005,  1008,  1011,  1014,  1017,  1020,  1023,
    1026,  1029,  1032,  1035,  1038,  1041,  1044,  1047,  1050,  1053,
    1056,  1059,  1062,  1065,  1068,  1071,  1074,  1077,  1080,  1083,
    1086,  1089,  1092,  1095,  1098,  1101,  1104,  1107,  1110,  1113,
    1116,  1119,  1122,  1125,  1128,  1131,  1134,  1137,  1140,  1143,
    1146,  1149,  1150,  1151,  1152,  1153,  1154,  1155,  1156,  1157,
    1158,  1159,  1160,  1161,  1162,  1163,  1164,  1165,  1166,  1167,
    1168,  1169,  1170,  1171,  1172,  1173,  1174,  1175,  1176,  1177,
    1178,  1181
  };

  // Print the state stack on the debug stream.
  void
   Parser ::yystack_print_ ()
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
   Parser ::yy_reduce_print_ (int yyrule)
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


#line 9 "Parser.yy" // lalr1.cc:1167
} //  Analysis 
#line 3821 "Parser.cpp" // lalr1.cc:1167
#line 1185 "Parser.yy" // lalr1.cc:1168


void Analysis::Parser::error(const location &loc, const std::string &message) {
	//cout << "Parse error: " << message << endl
	//    << "Error location: " << loc << endl << driver.mLexer->text() << endl;
}
