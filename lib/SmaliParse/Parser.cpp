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
      case 308: // instruction
        value.move< OpCode* > (that.value);
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
        value.move< int > (that.value);
        break;

      case 22: // "number"
        value.move< int64_t > (that.value);
        break;

      case 4: // "c type string"
      case 5: // "name string"
      case 6: // "comment"
      case 7: // "class name"
      case 8: // "class type"
      case 305: // comment
      case 307: // jmplabel
        value.move< std::string > (that.value);
        break;

      case 304: // regs
        value.move< std::vector<int> > (that.value);
        break;

      case 303: // args
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
      case 308: // instruction
        value.copy< OpCode* > (that.value);
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
        value.copy< int > (that.value);
        break;

      case 22: // "number"
        value.copy< int64_t > (that.value);
        break;

      case 4: // "c type string"
      case 5: // "name string"
      case 6: // "comment"
      case 7: // "class name"
      case 8: // "class type"
      case 305: // comment
      case 307: // jmplabel
        value.copy< std::string > (that.value);
        break;

      case 304: // regs
        value.copy< std::vector<int> > (that.value);
        break;

      case 303: // args
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
      case 308: // instruction
        yylhs.value.build< OpCode* > ();
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
        yylhs.value.build< int > ();
        break;

      case 22: // "number"
        yylhs.value.build< int64_t > ();
        break;

      case 4: // "c type string"
      case 5: // "name string"
      case 6: // "comment"
      case 7: // "class name"
      case 8: // "class type"
      case 305: // comment
      case 307: // jmplabel
        yylhs.value.build< std::string > ();
        break;

      case 304: // regs
        yylhs.value.build< std::vector<int> > ();
        break;

      case 303: // args
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
  case 13:
#line 395 "Parser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 1; driver.addOpcode(yystack_[0].value.as< OpCode* > ());}
#line 649 "Parser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 396 "Parser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 1; driver.endMethod();}
#line 655 "Parser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 399 "Parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 1;
        driver.setClassDefine(yystack_[1].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 663 "Parser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 403 "Parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 1;
        driver.setSuperDefine(yystack_[0].value.as< std::string > ());
    }
#line 671 "Parser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 407 "Parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 1;
        driver.setSourceDefine(yystack_[0].value.as< std::string > ());
    }
#line 679 "Parser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 411 "Parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 1;
        driver.addField(yystack_[2].value.as< std::string > (), yystack_[3].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 687 "Parser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 415 "Parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 1;
        driver.addMethod(yystack_[4].value.as< std::string > (), yystack_[5].value.as< int > (), yystack_[0].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > ());
    }
#line 695 "Parser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 419 "Parser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 0;}
#line 701 "Parser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 420 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< int > () = yystack_[0].value.as< int > ();
    }
#line 709 "Parser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 423 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< int > () = yystack_[1].value.as< int > ();
        yylhs.value.as< int > () |= yystack_[0].value.as< int > ();
    }
#line 718 "Parser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 429 "Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();}
#line 724 "Parser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 430 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();
        yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
    }
#line 733 "Parser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 434 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::vector<std::string> > () = yystack_[1].value.as< std::vector<std::string> > ();
        yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
    }
#line 742 "Parser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 440 "Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<int> > () = std::vector<int>();}
#line 748 "Parser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 441 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::vector<int> > () = std::vector<int>();
        yylhs.value.as< std::vector<int> > ().push_back(yystack_[0].value.as< int > ());
    }
#line 757 "Parser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 445 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::vector<int> > () = yystack_[2].value.as< std::vector<int> > ();
        yylhs.value.as< std::vector<int> > ().push_back(yystack_[0].value.as< int > ());
    }
#line 766 "Parser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 451 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();
    }
#line 774 "Parser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 457 "Parser.yy" // lalr1.cc:859
    {
        driver.setCurMethodRegSize(yystack_[0].value.as< int64_t > ());
    }
#line 782 "Parser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 463 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();
    }
#line 790 "Parser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 468 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NOP(OP_NOP, driver.stringPool());
    }
#line 798 "Parser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 471 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 806 "Parser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 474 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_FROM16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 814 "Parser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 477 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 822 "Parser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 480 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_WIDE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 830 "Parser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 483 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_WIDE_FROM16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 838 "Parser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 486 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_WIDE_16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 846 "Parser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 489 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_OBJECT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 854 "Parser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 492 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_OBJECT_FROM16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 862 "Parser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 495 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_OBJECT_16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 870 "Parser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 498 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_MOVE_RESULT(OP_MOVE_RESULT, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 878 "Parser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 501 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_MOVE_RESULT(OP_MOVE_RESULT_WIDE, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 886 "Parser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 504 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_MOVE_RESULT(OP_MOVE_RESULT_OBJECT, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 894 "Parser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 507 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE_EXCEPTION(OP_MOVE_EXCEPTION, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 902 "Parser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 510 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_RETURN_VOID(OP_RETURN_VOID, driver.stringPool());
    }
#line 910 "Parser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 513 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_RETURN(OP_RETURN, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 918 "Parser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 516 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_RETURN(OP_RETURN_WIDE, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 926 "Parser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 519 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_RETURN(OP_RETURN_OBJECT, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 934 "Parser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 522 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_4, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 942 "Parser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 525 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 950 "Parser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 528 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 958 "Parser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 531 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_HIGH16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 966 "Parser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 534 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_WIDE_16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 974 "Parser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 537 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_WIDE_32, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 982 "Parser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 540 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_WIDE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 990 "Parser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 543 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST(OP_CONST_WIDE_HIGH16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 998 "Parser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 546 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CONST_STRING(OP_CONST_STRING, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1006 "Parser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 549 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CONST_STRING(OP_CONST_STRING_JUMBO, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1014 "Parser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 552 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CONST_CLASS(OP_CONST_CLASS, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1022 "Parser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 555 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MONITOR(OP_MONITOR_ENTER, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1030 "Parser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 558 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MONITOR(OP_MONITOR_EXIT, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1038 "Parser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 561 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CHECK_CAST(OP_CHECK_CAST, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1046 "Parser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 564 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INSTANCE_OF(OP_INSTANCE_OF, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
   }
#line 1054 "Parser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 567 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_ARRAY_LENGTH(OP_ARRAY_LENGTH, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1062 "Parser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 570 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_NEW_INSTANCE(OP_NEW_INSTANCE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1070 "Parser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 573 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEW_ARRAY(OP_NEW_ARRAY, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1078 "Parser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 578 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_FILL_ARRAY_DATA(OP_FILL_ARRAY_DATA, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1086 "Parser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 581 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_THROW(OP_THROW, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 1094 "Parser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 584 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_GOTO(OP_GOTO, driver.stringPool(), yystack_[0].value.as< std::string > ());
    }
#line 1102 "Parser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 587 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_GOTO(OP_GOTO_16, driver.stringPool(), yystack_[0].value.as< std::string > ());
    }
#line 1110 "Parser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 590 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_GOTO(OP_GOTO_32, driver.stringPool(), yystack_[0].value.as< std::string > ());
    }
#line 1118 "Parser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 593 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_SWITCH(OP_PACKED_SWITCH, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1126 "Parser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 596 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_SWITCH(OP_SPARSE_SWITCH, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1134 "Parser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 599 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CMP(OP_CMPL_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1142 "Parser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 602 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CMP(OP_CMPG_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1150 "Parser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 605 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CMP(OP_CMPL_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1158 "Parser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 608 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CMP(OP_CMPG_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1166 "Parser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 611 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CMP(OP_CMP_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1174 "Parser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 614 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_EQ, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1182 "Parser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 617 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_NE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1190 "Parser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 620 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_LT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1198 "Parser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 623 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_GE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1206 "Parser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 626 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_GT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1214 "Parser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 629 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_LE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1222 "Parser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 632 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_EQZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1230 "Parser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 635 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_NEZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1238 "Parser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 638 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_LTZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1246 "Parser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 641 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_GEZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1254 "Parser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 644 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_GTZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1262 "Parser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 647 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_LEZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1270 "Parser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 656 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1278 "Parser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 659 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_WIDE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1286 "Parser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 662 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_OBJECT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1294 "Parser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 665 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_BOOLEAN, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1302 "Parser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 668 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_BYTE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1310 "Parser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 671 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_CHAR, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1318 "Parser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 674 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_SHORT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1326 "Parser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 677 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1334 "Parser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 680 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT_WIDE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1342 "Parser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 683 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT_OBJECT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1350 "Parser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 686 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT_BOOLEAN, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1358 "Parser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 689 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT_BYTE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1366 "Parser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 692 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT_CHAR, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1374 "Parser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 695 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_APUT(OP_APUT_SHORT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1382 "Parser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 698 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1390 "Parser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 701 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET_WIDE, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1398 "Parser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 704 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET_OBJECT, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1406 "Parser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 707 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET_BOOLEAN, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1414 "Parser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 710 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET_BYTE, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1422 "Parser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 713 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET_CHAR, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1430 "Parser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 716 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IGET(OP_IGET_SHORT, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1438 "Parser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 719 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1446 "Parser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 722 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT_WIDE, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1454 "Parser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 725 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT_OBJECT, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1462 "Parser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 728 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT_BOOLEAN, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1470 "Parser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 731 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT_BYTE, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1478 "Parser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 734 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT_CHAR, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1486 "Parser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 737 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IPUT(OP_IPUT_SHORT, driver.stringPool(), yystack_[8].value.as< int > (), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1494 "Parser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 740 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1502 "Parser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 743 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_WIDE, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1510 "Parser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 746 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_OBJECT, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1518 "Parser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 749 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_BOOLEAN, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1526 "Parser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 752 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_BYTE, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1534 "Parser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 755 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_CHAR, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1542 "Parser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 758 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_SHORT, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1550 "Parser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 761 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1558 "Parser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 764 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_WIDE, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1566 "Parser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 767 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_OBJECT, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1574 "Parser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 770 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_BOOLEAN, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1582 "Parser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 773 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_BYTE, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1590 "Parser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 776 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_CHAR, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1598 "Parser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 779 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_SHORT, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1606 "Parser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 782 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE(OP_INVOKE_VIRTUAL, driver.stringPool(), yystack_[9].value.as< std::vector<int> > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1614 "Parser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 785 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE(OP_INVOKE_SUPER, driver.stringPool(), yystack_[9].value.as< std::vector<int> > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1622 "Parser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 788 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE(OP_INVOKE_DIRECT, driver.stringPool(), yystack_[9].value.as< std::vector<int> > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1630 "Parser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 791 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE(OP_INVOKE_STATIC, driver.stringPool(), yystack_[9].value.as< std::vector<int> > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1638 "Parser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 794 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE(OP_INVOKE_INTERFACE, driver.stringPool(), yystack_[9].value.as< std::vector<int> > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1646 "Parser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 798 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE_X_RANGE(OP_INVOKE_VIRTUAL_RANGE, driver.stringPool(), yystack_[11].value.as< int > (), yystack_[9].value.as< int > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1654 "Parser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 801 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE_X_RANGE(OP_INVOKE_SUPER_RANGE, driver.stringPool(), yystack_[11].value.as< int > (), yystack_[9].value.as< int > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1662 "Parser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 804 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE_X_RANGE(OP_INVOKE_DIRECT_RANGE, driver.stringPool(), yystack_[11].value.as< int > (), yystack_[9].value.as< int > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1670 "Parser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 807 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE_X_RANGE(OP_INVOKE_STATIC_RANGE, driver.stringPool(), yystack_[11].value.as< int > (), yystack_[9].value.as< int > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1678 "Parser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 810 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE_X_RANGE(OP_INVOKE_INTERFACE_RANGE, driver.stringPool(), yystack_[11].value.as< int > (), yystack_[9].value.as< int > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1686 "Parser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 815 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEGNOT_X(OP_NEG_INT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1694 "Parser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 818 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEGNOT_X(OP_NOT_INT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1702 "Parser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 821 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEGNOT_X(OP_NEG_LONG, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1710 "Parser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 824 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEGNOT_X(OP_NOT_LONG, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1718 "Parser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 827 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEGNOT_X(OP_NEG_FLOAT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1726 "Parser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 830 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEGNOT_X(OP_NEG_DOUBLE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1734 "Parser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 833 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_INT_TO_LONG, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1742 "Parser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 836 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_INT_TO_FLOAT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1750 "Parser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 839 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_INT_TO_DOUBLE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1758 "Parser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 842 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_LONG_TO_INT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1766 "Parser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 845 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_LONG_TO_FLOAT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1774 "Parser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 848 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_LONG_TO_DOUBLE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1782 "Parser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 851 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_FLOAT_TO_INT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1790 "Parser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 854 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_FLOAT_TO_LONG, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1798 "Parser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 857 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_FLOAT_TO_DOUBLE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1806 "Parser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 860 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_DOUBLE_TO_INT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1814 "Parser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 863 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_DOUBLE_TO_LONG, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1822 "Parser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 866 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_DOUBLE_TO_FLOAT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1830 "Parser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 869 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_INT_TO_BYTE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1838 "Parser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 872 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_INT_TO_CHAR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1846 "Parser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 875 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_TO_Y(OP_INT_TO_SHORT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1854 "Parser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 878 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_ADD_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1862 "Parser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 881 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_SUB_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1870 "Parser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 884 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_MUL_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1878 "Parser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 887 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_DIV_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1886 "Parser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 890 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_REM_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1894 "Parser.cpp" // lalr1.cc:859
    break;

  case 181:
#line 893 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_AND_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1902 "Parser.cpp" // lalr1.cc:859
    break;

  case 182:
#line 896 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_OR_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1910 "Parser.cpp" // lalr1.cc:859
    break;

  case 183:
#line 899 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_XOR_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1918 "Parser.cpp" // lalr1.cc:859
    break;

  case 184:
#line 902 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_SHL_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1926 "Parser.cpp" // lalr1.cc:859
    break;

  case 185:
#line 905 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_SHR_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1934 "Parser.cpp" // lalr1.cc:859
    break;

  case 186:
#line 908 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT(OP_USHR_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1942 "Parser.cpp" // lalr1.cc:859
    break;

  case 187:
#line 911 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_ADD_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1950 "Parser.cpp" // lalr1.cc:859
    break;

  case 188:
#line 914 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_SUB_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1958 "Parser.cpp" // lalr1.cc:859
    break;

  case 189:
#line 917 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_MUL_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1966 "Parser.cpp" // lalr1.cc:859
    break;

  case 190:
#line 920 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_DIV_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1974 "Parser.cpp" // lalr1.cc:859
    break;

  case 191:
#line 923 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_REM_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1982 "Parser.cpp" // lalr1.cc:859
    break;

  case 192:
#line 926 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_AND_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1990 "Parser.cpp" // lalr1.cc:859
    break;

  case 193:
#line 929 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_OR_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1998 "Parser.cpp" // lalr1.cc:859
    break;

  case 194:
#line 932 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_XOR_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2006 "Parser.cpp" // lalr1.cc:859
    break;

  case 195:
#line 935 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_SHL_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2014 "Parser.cpp" // lalr1.cc:859
    break;

  case 196:
#line 938 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_SHR_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2022 "Parser.cpp" // lalr1.cc:859
    break;

  case 197:
#line 941 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG(OP_USHR_LONG, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2030 "Parser.cpp" // lalr1.cc:859
    break;

  case 198:
#line 944 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT(OP_ADD_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2038 "Parser.cpp" // lalr1.cc:859
    break;

  case 199:
#line 947 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT(OP_SUB_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2046 "Parser.cpp" // lalr1.cc:859
    break;

  case 200:
#line 950 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT(OP_MUL_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2054 "Parser.cpp" // lalr1.cc:859
    break;

  case 201:
#line 953 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT(OP_DIV_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2062 "Parser.cpp" // lalr1.cc:859
    break;

  case 202:
#line 956 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT(OP_REM_FLOAT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2070 "Parser.cpp" // lalr1.cc:859
    break;

  case 203:
#line 959 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE(OP_ADD_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2078 "Parser.cpp" // lalr1.cc:859
    break;

  case 204:
#line 962 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE(OP_SUB_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2086 "Parser.cpp" // lalr1.cc:859
    break;

  case 205:
#line 965 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE(OP_MUL_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2094 "Parser.cpp" // lalr1.cc:859
    break;

  case 206:
#line 968 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE(OP_DIV_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2102 "Parser.cpp" // lalr1.cc:859
    break;

  case 207:
#line 971 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE(OP_REM_DOUBLE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2110 "Parser.cpp" // lalr1.cc:859
    break;

  case 208:
#line 974 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_ADD_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2118 "Parser.cpp" // lalr1.cc:859
    break;

  case 209:
#line 977 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_SUB_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2126 "Parser.cpp" // lalr1.cc:859
    break;

  case 210:
#line 980 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_MUL_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2134 "Parser.cpp" // lalr1.cc:859
    break;

  case 211:
#line 983 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_DIV_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2142 "Parser.cpp" // lalr1.cc:859
    break;

  case 212:
#line 986 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_REM_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2150 "Parser.cpp" // lalr1.cc:859
    break;

  case 213:
#line 989 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_AND_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2158 "Parser.cpp" // lalr1.cc:859
    break;

  case 214:
#line 992 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_OR_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2166 "Parser.cpp" // lalr1.cc:859
    break;

  case 215:
#line 995 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_XOR_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2174 "Parser.cpp" // lalr1.cc:859
    break;

  case 216:
#line 998 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_SHL_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2182 "Parser.cpp" // lalr1.cc:859
    break;

  case 217:
#line 1001 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_SHR_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2190 "Parser.cpp" // lalr1.cc:859
    break;

  case 218:
#line 1004 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_2ADDR(OP_USHR_INT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2198 "Parser.cpp" // lalr1.cc:859
    break;

  case 219:
#line 1007 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_ADD_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2206 "Parser.cpp" // lalr1.cc:859
    break;

  case 220:
#line 1010 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_SUB_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2214 "Parser.cpp" // lalr1.cc:859
    break;

  case 221:
#line 1013 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_MUL_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2222 "Parser.cpp" // lalr1.cc:859
    break;

  case 222:
#line 1016 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_DIV_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2230 "Parser.cpp" // lalr1.cc:859
    break;

  case 223:
#line 1019 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_REM_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2238 "Parser.cpp" // lalr1.cc:859
    break;

  case 224:
#line 1022 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_AND_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2246 "Parser.cpp" // lalr1.cc:859
    break;

  case 225:
#line 1025 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_OR_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2254 "Parser.cpp" // lalr1.cc:859
    break;

  case 226:
#line 1028 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_XOR_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2262 "Parser.cpp" // lalr1.cc:859
    break;

  case 227:
#line 1031 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_SHL_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2270 "Parser.cpp" // lalr1.cc:859
    break;

  case 228:
#line 1034 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_SHR_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2278 "Parser.cpp" // lalr1.cc:859
    break;

  case 229:
#line 1037 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_LONG_2ADDR(OP_USHR_LONG_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2286 "Parser.cpp" // lalr1.cc:859
    break;

  case 230:
#line 1040 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT_2ADDR(OP_ADD_FLOAT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2294 "Parser.cpp" // lalr1.cc:859
    break;

  case 231:
#line 1043 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT_2ADDR(OP_SUB_FLOAT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2302 "Parser.cpp" // lalr1.cc:859
    break;

  case 232:
#line 1046 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT_2ADDR(OP_MUL_FLOAT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2310 "Parser.cpp" // lalr1.cc:859
    break;

  case 233:
#line 1049 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT_2ADDR(OP_DIV_FLOAT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2318 "Parser.cpp" // lalr1.cc:859
    break;

  case 234:
#line 1052 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_FLOAT_2ADDR(OP_REM_FLOAT_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2326 "Parser.cpp" // lalr1.cc:859
    break;

  case 235:
#line 1055 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE_2ADDR(OP_ADD_DOUBLE_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2334 "Parser.cpp" // lalr1.cc:859
    break;

  case 236:
#line 1058 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE_2ADDR(OP_SUB_DOUBLE_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2342 "Parser.cpp" // lalr1.cc:859
    break;

  case 237:
#line 1061 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE_2ADDR(OP_MUL_DOUBLE_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2350 "Parser.cpp" // lalr1.cc:859
    break;

  case 238:
#line 1064 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE_2ADDR(OP_DIV_DOUBLE_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2358 "Parser.cpp" // lalr1.cc:859
    break;

  case 239:
#line 1067 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_DOUBLE_2ADDR(OP_REM_DOUBLE_2ADDR, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 2366 "Parser.cpp" // lalr1.cc:859
    break;

  case 240:
#line 1070 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_ADD_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 2374 "Parser.cpp" // lalr1.cc:859
    break;

  case 241:
#line 1073 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_RSUB_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 2382 "Parser.cpp" // lalr1.cc:859
    break;

  case 242:
#line 1076 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_MUL_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 2390 "Parser.cpp" // lalr1.cc:859
    break;

  case 243:
#line 1079 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_DIV_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 2398 "Parser.cpp" // lalr1.cc:859
    break;

  case 244:
#line 1082 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_REM_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 2406 "Parser.cpp" // lalr1.cc:859
    break;

  case 245:
#line 1085 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_AND_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 2414 "Parser.cpp" // lalr1.cc:859
    break;

  case 246:
#line 1088 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_OR_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 2422 "Parser.cpp" // lalr1.cc:859
    break;

  case 247:
#line 1091 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_XOR_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 2430 "Parser.cpp" // lalr1.cc:859
    break;

  case 248:
#line 1094 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_ADD_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 2438 "Parser.cpp" // lalr1.cc:859
    break;

  case 249:
#line 1097 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_RSUB_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 2446 "Parser.cpp" // lalr1.cc:859
    break;

  case 250:
#line 1100 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_MUL_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 2454 "Parser.cpp" // lalr1.cc:859
    break;

  case 251:
#line 1103 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_DIV_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 2462 "Parser.cpp" // lalr1.cc:859
    break;

  case 252:
#line 1106 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_REM_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 2470 "Parser.cpp" // lalr1.cc:859
    break;

  case 253:
#line 1109 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_AND_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 2478 "Parser.cpp" // lalr1.cc:859
    break;

  case 254:
#line 1112 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_OR_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 2486 "Parser.cpp" // lalr1.cc:859
    break;

  case 255:
#line 1115 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_XOR_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 2494 "Parser.cpp" // lalr1.cc:859
    break;

  case 256:
#line 1118 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_SHL_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 2502 "Parser.cpp" // lalr1.cc:859
    break;

  case 257:
#line 1121 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_SHR_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 2510 "Parser.cpp" // lalr1.cc:859
    break;

  case 258:
#line 1124 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_USHR_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int64_t > ());
    }
#line 2518 "Parser.cpp" // lalr1.cc:859
    break;

  case 288:
#line 1156 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_JmpLabel(OP_JMPLABEL, driver.stringPool(), yystack_[0].value.as< std::string > ());
    }
#line 2526 "Parser.cpp" // lalr1.cc:859
    break;

  case 289:
#line 1159 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CATCH(OP_CATCH, driver.stringPool(), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 2534 "Parser.cpp" // lalr1.cc:859
    break;


#line 2538 "Parser.cpp" // lalr1.cc:859
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


  const short int  Parser ::yypact_ninf_ = -961;

  const signed char  Parser ::yytable_ninf_ = -1;

  const short int
   Parser ::yypact_[] =
  {
    -961,     2,  -961,   294,  -961,  -961,   297,   314,   319,   297,
     297,  -961,   302,  -961,   304,   305,   306,   307,   308,   315,
     316,   317,   318,   320,   321,   322,   323,  -961,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,  -961,
    -961,   345,   346,    50,    50,    50,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   356,   357,   358,   359,   360,
     361,   362,   363,   364,   365,  -961,  -961,  -961,  -961,  -961,
    -961,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   139,   140,   141,   142,   143,  -961,   144,
     145,   146,   147,   148,  -961,  -961,   418,   419,   420,   421,
     422,   423,   424,   425,   426,   427,   428,   429,   430,   431,
     432,   433,   434,   435,   436,   437,   438,   439,   440,   441,
     442,   443,   444,   445,   446,   447,   448,   449,   450,   451,
     452,   453,   454,   455,   456,   457,   458,   460,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   480,
     481,   482,   483,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   506,   507,   508,   509,   510,
     511,   512,   513,   514,   515,   516,   517,   518,   519,   520,
     521,   522,   523,   524,   525,   526,   527,   528,   529,   530,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,   544,
     548,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,   276,  -961,  -961,     5,   284,  -961,    52,   266,
     267,   268,   269,   270,   271,   272,   273,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,   274,   275,   277,   278,   279,   280,
     281,   282,   283,   285,   286,  -961,  -961,   287,   288,   289,
     290,   291,   292,  -961,   559,  -961,  -961,  -961,   293,   295,
     296,   298,   299,   300,   301,   303,   309,   310,   312,   313,
     408,   409,   410,   411,   412,   413,   414,   415,   416,   417,
     459,   461,   462,   474,   475,   476,   477,   478,   479,   531,
     532,   533,   534,   535,   536,   537,   538,   539,   540,   541,
     542,   543,   545,   546,   547,   549,   550,   551,   552,   553,
     554,   555,   556,   557,   558,   560,   561,   562,   563,   564,
     564,   564,   564,   564,   569,   571,   572,   573,   574,   565,
     566,   567,   568,   570,   575,   576,   577,   578,   579,   580,
     581,   582,   583,   584,   585,   592,   593,   594,   595,   596,
     597,   598,   599,   600,   601,   602,   603,   604,   605,   606,
     607,   608,   609,   610,   611,   612,   613,   614,   615,   616,
     617,   618,   619,   620,   621,   622,   623,   624,   625,   626,
     627,   628,   629,   630,   631,   632,   633,   634,   635,   636,
     637,   638,   639,   640,   641,   642,   643,   644,   645,   646,
     647,   648,   649,   650,   651,   652,   653,   654,   655,   656,
     657,   658,   659,   660,   661,   662,   663,   664,   665,   666,
     667,   668,   669,   670,   671,   672,   673,   674,   675,   676,
     677,   678,   679,   680,  -961,  -961,  -961,   683,   685,   586,
     587,   588,   589,   590,   591,   686,   687,   688,   684,   689,
     690,   691,   692,   693,   694,   695,   681,   682,   702,   710,
     698,   699,   713,   701,    50,  -961,    50,    50,   703,   704,
     705,   706,   707,   708,   709,   711,   712,   714,   715,    50,
      50,    50,    50,    50,    50,   716,   717,   718,   719,   720,
     721,   722,   723,   724,   725,   727,   730,   731,   732,   733,
     734,   735,   736,   737,   738,   739,   740,   747,   748,   749,
     750,   751,   752,   726,   766,   767,   768,   769,   770,   771,
     772,   773,   774,   775,   776,   777,   778,  -961,    21,    22,
      23,    27,    28,   696,   697,   700,   728,   729,   779,   780,
     781,   782,   783,   784,   785,   786,   787,   788,   789,   790,
     791,   792,   793,   794,   795,   796,   797,   811,   815,   826,
     831,   836,   838,   839,   840,   841,   948,   951,   952,   953,
     954,   955,   956,   957,   958,   959,   960,   961,   962,   964,
     965,   966,   969,   970,   972,   973,   974,   975,   976,   977,
     978,   979,   980,   981,   982,   983,   984,   985,   986,   987,
     988,   989,   990,   991,   992,   993,   994,   995,   996,   997,
     998,  1001,  1002,  1003,  1004,  1005,  1006,  1007,  1008,  1009,
    1010,  1011,  1012,  1013,  1014,  1015,  1016,  1017,  1018,  1019,
    1020,  1021,  1022,  1023,  1024,  1025,  1026,  1027,  1028,  1029,
    1030,  1031,    50,  1045,  1046,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,   798,  -961,  -961,   799,
    -961,  -961,  -961,   800,   801,   802,   803,   804,   805,   806,
     807,   808,   809,   810,  -961,  -961,  -961,  -961,  -961,  -961,
     812,   813,   814,   816,   817,   818,   819,   820,   821,   822,
     823,   824,   825,   827,   828,   829,   830,   832,   833,   834,
     835,   837,   842,   843,   844,   845,   846,   847,   848,   849,
     850,   851,   852,   853,   855,   856,   857,   858,   859,   860,
     861,   862,  1034,   864,   865,   866,   867,   868,  1035,  1036,
    1037,  1038,  1039,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,   869,   870,   871,   872,   873,   874,
     875,   876,   877,   878,   879,   880,   881,   882,   883,   884,
     885,   886,   887,   888,   889,   890,   891,   892,   893,   894,
     895,   896,   897,   898,   899,   900,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,   901,   902,
     903,   904,   905,   906,   907,   908,   909,   910,   911,   912,
     913,   914,   915,   916,   917,   918,   919,   920,  -961,  -961,
      -4,  1053,  1054,  1042,  1043,  1044,  1047,  1048,    50,    50,
      50,    50,    50,    50,  1049,  1050,  1051,  1052,  1055,  1056,
    1057,  1058,  1059,  1060,  1061,  1062,  1063,  1064,  1066,  1067,
    1091,  1095,  1106,  1111,  1116,  1118,  1119,  1120,  1121,  1128,
    1200,  1201,  1205,  1206,  1208,  1209,  1210,  1211,  1212,  1213,
    1214,  1215,  1216,  1217,  1218,  1219,  -961,  1220,  1221,  1222,
    1223,  1224,   934,   935,   936,   942,   943,  1225,  1226,  1227,
    1228,  1229,  1230,  1231,  1232,  1233,  1234,  1235,  1236,  1237,
    1238,  1239,  1240,  1241,  1242,  1243,  1244,  1245,  1246,  1247,
    1248,  1249,  1250,  1251,  1252,  1253,  1254,  1255,  1256,   765,
    1257,  1258,  1259,  1260,  1261,  1262,  1263,  1264,  1265,  1266,
    1267,  1268,  1269,  1270,  1271,  1272,  1273,  1274,    50,  -961,
    1289,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,   946,   947,
     949,   950,  1032,  1033,  1040,  1041,  1065,  1068,  1069,  1070,
    1071,  1072,  1077,  1078,  1079,  1080,  1081,  1082,  1083,  1084,
    1085,  1086,  1087,  1088,  1089,  1090,  1092,  1093,  1094,  1096,
    1097,  1099,  1100,  1101,  1102,  1103,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  1104,  -961,  1293,
    1294,  1295,  1296,  1297,  1298,  1299,  1300,  1301,  1302,  1303,
    1304,  1305,  1306,  1307,  1308,  1309,  1310,  1311,  1312,  1315,
    1316,  1317,  1318,  1319,  1320,  1323,  1324,  1328,  1329,  1330,
    1331,  1332,  1333,  1334,  1335,  1336,  1337,    50,  1107,  1108,
    1109,  1112,  1113,  1114,  1115,  1117,  1122,  1123,  1124,  1125,
    1126,  1127,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,  -961,  1098,  1110,  1129,  1130,
    1131,  1132,  1133,  1134,  1135,  1136,  -961,  1338,  1339,  1340,
    1341,  1342,  1343,  1344,  1345,  1347,  1348,  1368,  1369,  1370,
    1371,  1046,  1046,  1046,  1046,  1046,  1375,  1396,  1398,  1399,
    1400,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,
    -961,  -961,  -961,  -961,  -961,    -2,    -1,     1,     3,    11,
    1140,  1141,  1142,  1143,  1144,  1405,  1406,  1410,  1411,  1412,
    1046,  1046,  1046,  1046,  1046,  -961,  -961,  -961,  -961,  -961,
      12,    13,    14,    15,    16,  1423,  1424,  1425,  1426,  1427,
    -961,  -961,  -961,  -961,  -961
  };

  const unsigned short int
   Parser ::yydefact_[] =
  {
       2,     0,     1,     0,     3,    29,    20,     0,     0,    20,
      20,    14,     0,    32,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    46,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    68,
      69,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    94,    95,    96,    97,    98,
      99,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   147,     0,
       0,     0,     0,     0,   153,   154,     0,     0,     0,     0,
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
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,     0,
       0,     5,     7,     8,     9,    10,    11,     4,    12,    13,
       6,    21,     0,    16,    17,     0,     0,    30,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    42,    43,    44,
      45,    47,    48,    49,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    61,    62,     0,     0,     0,
       0,     0,     0,    71,     0,    72,    73,    74,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    26,
      26,    26,    26,    26,     0,     0,     0,     0,     0,     0,
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
       0,     0,     0,     0,   288,    15,    22,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    31,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    27,     0,     0,
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
       0,     0,     0,     0,    23,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    63,     0,    65,    66,     0,
      70,    75,    76,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    88,    89,    90,    91,    92,    93,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    18,    24,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    28,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    25,
       0,    64,    67,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,     0,    19,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   289,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    23,    23,    23,    23,    23,     0,     0,     0,     0,
       0,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      23,    23,    23,    23,    23,   142,   143,   144,   145,   146,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     148,   149,   150,   151,   152
  };

  const short int
   Parser ::yypgoto_[] =
  {
    -961,  -961,  -961,  -961,  -961,  -961,  -961,  -961,   311,  -960,
     -85,  -961,  -961,   -54,  -961
  };

  const short int
   Parser ::yydefgoto_[] =
  {
      -1,     1,   271,   272,   273,   274,   275,   276,   282,   920,
     598,   277,   278,   325,   279
  };

  const unsigned short int
   Parser ::yytable_[] =
  {
     326,   327,     2,     3,  1039,     4,  1039,  1039,     5,  1039,
     507,  1039,     6,     7,     8,     9,    10,    11,    12,  1039,
    1039,  1039,  1039,  1039,  1039,   506,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
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
     267,   268,   269,  1040,   505,  1285,  1286,   270,  1287,   508,
    1288,  1275,  1276,  1277,  1278,  1279,   506,   280,  1289,  1305,
    1306,  1307,  1308,  1309,   506,   599,   600,   601,   602,   802,
     802,   802,   803,   804,   805,   802,   802,   281,   806,   807,
     285,   286,   283,   284,   287,   288,   289,   290,   291,   292,
    1300,  1301,  1302,  1303,  1304,   324,   293,   294,   295,   296,
     509,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   366,   367,   368,   369,
     370,   371,   372,   373,   374,   375,   376,   377,   378,   379,
     380,   381,   382,   383,   384,   385,   386,   387,   388,   389,
     390,   391,   392,   393,   394,   395,   396,   397,   398,   399,
     400,   401,   402,   403,   404,   405,   406,   407,   408,   409,
     410,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     420,   421,   422,   423,   424,   425,   426,   427,   428,   429,
     430,   431,   432,   433,   434,   435,   436,   437,   438,   439,
     740,   440,   741,   742,   441,   442,   443,   444,   445,   446,
     447,   448,   449,   450,   451,   754,   755,   756,   757,   758,
     759,   452,   453,   454,   455,   456,   457,   458,   459,   460,
     461,   462,   463,   464,   465,   466,   467,   468,   469,   470,
     471,   472,   473,   474,   475,   476,   477,   478,   479,   480,
     481,   482,   483,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   510,   511,   512,   513,   514,   515,
     516,   517,   518,   519,   535,   520,   521,   522,   523,   524,
     525,   526,     0,   527,   528,   529,   530,   531,   532,   533,
     534,   536,     0,   537,   538,   597,   539,   540,   541,   542,
     603,   543,   604,   605,   606,   607,     0,   544,   545,     0,
     546,   547,     0,     0,     0,     0,     0,   715,   716,   717,
     718,   719,   720,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   917,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   732,   733,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   548,   549,   550,   551,
     552,   553,   554,   555,   556,   557,   724,   721,   722,   723,
     734,   725,   726,   727,   728,   729,   730,   731,   735,   736,
     737,   738,   739,     0,   743,   744,   745,   746,   747,   748,
     749,     0,   750,   751,   788,   752,   753,   760,   761,   762,
     763,   764,   765,   766,   767,   768,   769,   558,   770,   559,
     560,   771,   772,   773,   774,   775,   776,   777,   778,   779,
     780,   781,   561,   562,   563,   564,   565,   566,   782,   783,
     784,   785,   786,   787,   789,   790,   791,   792,   793,   794,
     795,   796,   797,   798,   799,   800,   801,  1138,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     813,   814,   815,   816,   817,   818,   819,   820,   821,   822,
     823,   824,   825,   826,   827,   828,   829,   830,   831,   567,
     568,   569,   570,   571,   572,   573,   574,   575,   576,   577,
     578,   579,   832,   580,   581,   582,   833,   583,   584,   585,
     586,   587,   588,   589,   590,   591,   592,   834,   593,   594,
     595,   596,   835,   608,   609,   610,   611,   836,   612,   837,
     838,   839,   840,   613,   614,   615,   616,   617,   618,   619,
     620,   621,   622,   623,  1048,  1049,  1050,  1051,  1052,  1053,
     624,   625,   626,   627,   628,   629,   630,   631,   632,   633,
     634,   635,   636,   637,   638,   639,   640,   641,   642,   643,
     644,   645,   646,   647,   648,   649,   650,   651,   652,   653,
     654,   655,   656,   657,   658,   659,   660,   661,   662,   663,
     664,   665,   666,   667,   668,   669,   670,   671,   672,   673,
     674,   675,   676,   677,   678,   679,   680,   681,   682,   683,
     684,   685,   686,   687,   688,   689,   690,   691,   692,   693,
     694,   695,   696,   697,   698,   699,   700,   701,   702,   703,
     704,   705,   706,   707,   708,   709,   710,   711,   713,   841,
     712,   714,   842,   843,   844,   845,   846,   847,   848,   849,
     850,   851,   852,   853,  1157,   854,   855,   856,   808,   809,
     857,   858,   810,   859,   860,   861,   862,   863,   864,   865,
     866,   867,   868,   869,   870,   871,   872,   873,   874,   875,
     876,   877,   878,   879,   880,   881,   882,   883,   884,   885,
     811,   812,   886,   887,   888,   889,   890,   891,   892,   893,
     894,   895,   896,   897,   898,   899,   900,   901,   902,   903,
     904,   905,   906,   907,   908,   909,   910,   911,   912,   913,
     914,   915,   916,   918,   919,   976,   982,   983,   984,   985,
     986,  1041,  1042,  1043,  1044,  1045,     0,     0,  1046,  1047,
    1054,  1055,  1056,  1057,  1068,  1069,  1058,  1059,  1060,  1061,
    1062,  1063,  1064,  1065,  1066,  1067,   921,   922,   923,   924,
     925,   926,   927,   928,   929,   930,   931,   932,   933,  1070,
     934,   935,   936,  1071,   937,   938,   939,   940,   941,   942,
     943,   944,   945,   946,  1072,   947,   948,   949,   950,  1073,
     951,   952,   953,   954,  1074,   955,  1075,  1076,  1077,  1078,
     956,   957,   958,   959,   960,   961,  1079,   962,   963,   964,
     965,   966,   967,  1236,   968,   969,   970,   971,   972,   973,
     974,   975,   977,   978,   979,   980,   981,   987,   988,   989,
     990,   991,   992,   993,   994,   995,   996,   997,   998,   999,
    1000,  1001,  1002,  1003,  1004,  1005,  1006,  1007,  1008,  1009,
    1010,  1011,  1012,  1013,  1014,  1015,  1016,  1017,  1018,  1019,
    1020,  1021,  1022,  1023,  1024,  1025,  1026,  1027,  1028,  1029,
    1030,  1031,  1032,  1033,  1034,  1035,  1036,  1037,  1080,  1081,
    1082,  1083,  1038,  1084,  1085,  1086,  1087,  1088,  1089,  1090,
    1091,  1092,  1093,  1094,  1095,  1101,  1102,  1103,  1096,  1097,
    1098,  1099,  1100,  1104,  1105,  1159,  1160,     0,  1161,  1162,
       0,     0,     0,     0,     0,     0,  1106,  1107,  1108,  1109,
    1110,  1111,  1112,  1113,  1114,  1115,  1116,  1117,  1118,  1119,
    1120,  1121,  1122,  1123,  1124,  1125,  1126,  1127,  1128,  1129,
    1130,  1131,  1132,  1133,  1134,  1135,  1136,  1137,     0,  1139,
    1140,  1141,  1142,  1143,  1144,  1145,  1146,  1147,  1148,  1149,
    1150,  1151,  1152,  1153,  1154,  1155,  1156,  1158,  1198,  1199,
    1200,  1201,  1202,  1203,  1204,  1205,  1206,  1207,  1208,  1209,
    1210,  1211,     0,     0,     0,  1212,  1213,  1214,  1215,  1216,
    1217,  1163,  1164,  1218,  1219,  1220,  1221,  1222,  1223,  1165,
    1166,  1224,  1225,  1226,  1227,  1228,  1229,  1230,     0,     0,
       0,  1231,  1232,  1233,  1234,  1235,  1261,  1262,  1263,  1264,
    1265,  1266,  1267,  1268,  1167,  1269,  1270,  1168,  1169,  1170,
    1171,  1172,  1173,  1174,  1175,  1176,  1177,  1178,  1179,  1180,
    1181,  1182,  1183,  1184,  1185,  1186,  1271,  1272,  1273,  1274,
    1280,  1187,  1188,  1189,  1251,  1190,  1191,  1192,  1193,  1194,
    1195,  1196,  1237,  1238,  1239,  1197,  1252,  1240,  1241,  1242,
    1243,  1281,  1244,  1282,  1283,  1284,     0,  1245,  1246,  1247,
    1248,  1249,  1250,  1295,  1296,  1253,  1254,  1255,  1297,  1298,
    1299,  1256,  1257,  1258,  1259,  1260,  1290,  1291,  1292,  1293,
    1294,  1310,  1311,  1312,  1313,  1314
  };

  const short int
   Parser ::yycheck_[] =
  {
      54,    55,     0,     1,     8,     3,     8,     8,     6,     8,
       5,     8,    10,    11,    12,    13,    14,    15,    16,     8,
       8,     8,     8,     8,     8,    20,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
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
     278,   279,   280,   287,     8,   287,   287,   285,   287,     5,
     287,  1251,  1252,  1253,  1254,  1255,    20,     3,   287,   287,
     287,   287,   287,   287,    20,   390,   391,   392,   393,   288,
     288,   288,   291,   291,   291,   288,   288,    20,   291,   291,
       9,    10,     8,     4,    22,    21,    21,    21,    21,    21,
    1290,  1291,  1292,  1293,  1294,   285,    21,    21,    21,    21,
     288,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
     534,    21,   536,   537,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,   549,   550,   551,   552,   553,
     554,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,     8,     5,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,     5,   288,   288,   288,   288,   288,
     288,   288,    -1,   288,   288,   288,   288,   288,   288,   288,
     288,   288,    -1,   288,   288,    21,   288,   288,   288,   288,
      21,   288,    21,    21,    21,    21,    -1,   288,   288,    -1,
     288,   288,    -1,    -1,    -1,    -1,    -1,    21,    21,    21,
      21,    21,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   712,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     4,     4,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,    22,    21,    21,    21,
       8,    22,    22,    22,    22,    22,    22,    22,     8,    21,
      21,     8,    21,    -1,    21,    21,    21,    21,    21,    21,
      21,    -1,    21,    21,     8,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,   288,    21,   288,
     288,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,   288,   288,   288,   288,   288,   288,    21,    21,
      21,    21,    21,    21,     8,     8,     8,     8,     8,     8,
       8,     8,     8,     8,     8,     8,     8,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,    21,   288,   288,   288,    21,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,    21,   288,   288,
     288,   288,    21,   288,   288,   288,   288,    21,   288,    21,
      21,    21,    21,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   928,   929,   930,   931,   932,   933,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   285,    21,
     290,   286,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,  1038,    21,    21,    21,   292,   292,
      21,    21,   292,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
     292,   292,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,     8,     8,    21,    21,    21,    21,    21,
      21,     8,     8,    21,    21,    21,    -1,    -1,    21,    21,
      21,    21,    21,    21,     8,     8,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,     8,
     288,   288,   288,     8,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,     8,   288,   288,   288,   288,     8,
     288,   288,   288,   288,     8,   288,     8,     8,     8,     8,
     288,   288,   288,   288,   288,   288,     8,   289,   289,   289,
     289,   289,   289,  1197,   289,   289,   289,   289,   289,   289,
     289,   289,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,     8,     8,
       5,     5,   292,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     5,   291,   291,   291,     8,     8,
       8,     8,     8,   291,   291,   289,   289,    -1,   289,   289,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    -1,    22,
      22,    22,    22,    22,    22,    22,    22,    22,    22,    22,
      22,    22,    22,    22,    22,    22,    22,     8,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,    -1,    -1,    -1,     8,     8,     8,     8,     8,
       8,   289,   289,     8,     8,     8,     8,     8,     8,   289,
     289,     8,     8,     5,     5,     5,     5,     5,    -1,    -1,
      -1,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,     8,     8,     8,   289,     8,     8,   289,   289,   289,
     289,   289,   285,   285,   285,   285,   285,   285,   285,   285,
     285,   285,   285,   285,   285,   285,     8,     8,     8,     8,
       5,   289,   289,   289,   286,   289,   289,   288,   288,   288,
     288,   288,   285,   285,   285,   291,   286,   285,   285,   285,
     285,     5,   285,     5,     5,     5,    -1,   285,   285,   285,
     285,   285,   285,     8,     8,   286,   286,   286,     8,     8,
       8,   289,   289,   289,   289,   289,   286,   286,   286,   286,
     286,     8,     8,     8,     8,     8
  };

  const unsigned short int
   Parser ::yystos_[] =
  {
       0,   295,     0,     1,     3,     6,    10,    11,    12,    13,
      14,    15,    16,    24,    25,    26,    27,    28,    29,    30,
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
     285,   296,   297,   298,   299,   300,   301,   305,   306,   308,
       3,    20,   302,     8,     4,   302,   302,    22,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,   285,   307,   307,   307,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,     8,     5,     8,    20,     5,     5,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,     5,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,    21,   304,   304,
     304,   304,   304,    21,    21,    21,    21,    21,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   290,   285,   286,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    22,    22,    22,    22,    22,    22,
      22,    22,     4,     4,     8,     8,    21,    21,     8,    21,
     307,   307,   307,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,   307,   307,   307,   307,   307,   307,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,     8,     8,
       8,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,     8,   288,   291,   291,   291,   291,   291,   292,   292,
     292,   292,   292,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,   307,     8,     8,
     303,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,    21,   288,   288,   288,
     288,   288,    21,    21,    21,    21,    21,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   292,     8,
     287,     8,     8,    21,    21,    21,    21,    21,   307,   307,
     307,   307,   307,   307,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,     8,     8,
       8,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,     8,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     8,     8,     8,     8,
       8,   291,   291,   291,   291,   291,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    22,    22,
      22,    22,    22,    22,    22,    22,    22,    22,    22,    22,
      22,    22,    22,    22,    22,    22,    22,   307,     8,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   285,   285,   285,   285,   285,   285,   285,
     285,   285,   285,   285,   285,   285,   285,   289,   289,   289,
     289,   289,   288,   288,   288,   288,   288,   291,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     8,     8,     8,     8,     8,     8,     8,     8,
       8,     8,     8,     8,     8,     8,     5,     5,     5,     5,
       5,     8,     8,     8,     8,     8,   307,   285,   285,   285,
     285,   285,   285,   285,   285,   285,   285,   285,   285,   285,
     285,   286,   286,   286,   286,   286,   289,   289,   289,   289,
     289,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,     8,     8,     8,     8,   303,   303,   303,   303,   303,
       5,     5,     5,     5,     5,   287,   287,   287,   287,   287,
     286,   286,   286,   286,   286,     8,     8,     8,     8,     8,
     303,   303,   303,   303,   303,   287,   287,   287,   287,   287,
       8,     8,     8,     8,     8
  };

  const unsigned short int
   Parser ::yyr1_[] =
  {
       0,   294,   295,   295,   295,   295,   295,   296,   296,   296,
     296,   296,   296,   296,   296,   297,   298,   299,   300,   301,
     302,   302,   302,   303,   303,   303,   304,   304,   304,   305,
     306,   307,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308
  };

  const unsigned char
   Parser ::yyr2_[] =
  {
       0,     2,     0,     2,     2,     2,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     2,     2,     5,     7,
       0,     1,     2,     0,     1,     2,     0,     1,     3,     1,
       2,     2,     1,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     2,     2,     2,     2,     1,     2,     2,     2,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     2,     2,     4,     6,     4,     4,     6,     1,     1,
       4,     2,     2,     2,     2,     4,     4,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     4,     4,
       4,     4,     4,     4,     1,     1,     1,     1,     1,     1,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,    10,    10,    10,    10,    10,    10,
      10,    10,    10,    10,    10,    10,    10,    10,     8,     8,
       8,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,     8,    12,    12,    12,    12,    12,     1,    14,    14,
      14,    14,    14,     1,     1,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     8
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
  "\"flag\"", "\"v(p)x\"", "\"number\"", "\"begin of opcodes\"", "\"nop\"",
  "\"move\"", "\"move/from16\"", "\"move/16\"", "\"move-wide\"",
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
  "\"unused-ff\"", "\".catch\"", "\"end of opcodes\"",
  "\".packed-switch\"", "\".end packed-switch\"", "\"begin of symbol\"",
  "\":\"", "\"(\"", "\")\"", "\",\"", "\"->\"", "\"{\"", "\"}\"", "\"..\"",
  "\"end of symbol\"", "$accept", "program", "exp", "classdef", "superdef",
  "srcdef", "fielddef", "methoddef", "flags", "args", "regs", "comment",
  "registers", "jmplabel", "instruction", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
   Parser ::yyrline_[] =
  {
       0,   382,   382,   383,   384,   385,   386,   389,   390,   391,
     392,   393,   394,   395,   396,   399,   403,   407,   411,   415,
     419,   420,   423,   429,   430,   434,   440,   441,   445,   451,
     457,   463,   468,   471,   474,   477,   480,   483,   486,   489,
     492,   495,   498,   501,   504,   507,   510,   513,   516,   519,
     522,   525,   528,   531,   534,   537,   540,   543,   546,   549,
     552,   555,   558,   561,   564,   567,   570,   573,   576,   577,
     578,   581,   584,   587,   590,   593,   596,   599,   602,   605,
     608,   611,   614,   617,   620,   623,   626,   629,   632,   635,
     638,   641,   644,   647,   650,   651,   652,   653,   654,   655,
     656,   659,   662,   665,   668,   671,   674,   677,   680,   683,
     686,   689,   692,   695,   698,   701,   704,   707,   710,   713,
     716,   719,   722,   725,   728,   731,   734,   737,   740,   743,
     746,   749,   752,   755,   758,   761,   764,   767,   770,   773,
     776,   779,   782,   785,   788,   791,   794,   797,   798,   801,
     804,   807,   810,   813,   814,   815,   818,   821,   824,   827,
     830,   833,   836,   839,   842,   845,   848,   851,   854,   857,
     860,   863,   866,   869,   872,   875,   878,   881,   884,   887,
     890,   893,   896,   899,   902,   905,   908,   911,   914,   917,
     920,   923,   926,   929,   932,   935,   938,   941,   944,   947,
     950,   953,   956,   959,   962,   965,   968,   971,   974,   977,
     980,   983,   986,   989,   992,   995,   998,  1001,  1004,  1007,
    1010,  1013,  1016,  1019,  1022,  1025,  1028,  1031,  1034,  1037,
    1040,  1043,  1046,  1049,  1052,  1055,  1058,  1061,  1064,  1067,
    1070,  1073,  1076,  1079,  1082,  1085,  1088,  1091,  1094,  1097,
    1100,  1103,  1106,  1109,  1112,  1115,  1118,  1121,  1124,  1127,
    1128,  1129,  1130,  1131,  1132,  1133,  1134,  1135,  1136,  1137,
    1138,  1139,  1140,  1141,  1142,  1143,  1144,  1145,  1146,  1147,
    1148,  1149,  1150,  1151,  1152,  1153,  1154,  1155,  1156,  1159
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
#line 3753 "Parser.cpp" // lalr1.cc:1167
#line 1163 "Parser.yy" // lalr1.cc:1168


void Analysis::Parser::error(const location &loc, const std::string &message) {
	cout << "Parse error: " << message << endl
	    << "Error location: " << loc << endl << driver.mLexer.text() << endl;
}
