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
      case 306: // instruction
        value.move< OpCode* > (that.value);
        break;

      case 20: // "flag"
      case 21: // "v(p)x"
      case 294: // exp
      case 295: // classdef
      case 296: // superdef
      case 297: // srcdef
      case 298: // fielddef
      case 299: // methoddef
      case 300: // flags
      case 304: // registers
        value.move< int > (that.value);
        break;

      case 4: // "c type string"
      case 5: // "name string"
      case 6: // "comment"
      case 7: // "class name"
      case 8: // "class type"
      case 303: // comment
      case 305: // jmplabel
        value.move< std::string > (that.value);
        break;

      case 302: // regs
        value.move< std::vector<int> > (that.value);
        break;

      case 301: // args
        value.move< std::vector<std::string> > (that.value);
        break;

      case 22: // "number"
        value.move< uint64_t > (that.value);
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
      case 306: // instruction
        value.copy< OpCode* > (that.value);
        break;

      case 20: // "flag"
      case 21: // "v(p)x"
      case 294: // exp
      case 295: // classdef
      case 296: // superdef
      case 297: // srcdef
      case 298: // fielddef
      case 299: // methoddef
      case 300: // flags
      case 304: // registers
        value.copy< int > (that.value);
        break;

      case 4: // "c type string"
      case 5: // "name string"
      case 6: // "comment"
      case 7: // "class name"
      case 8: // "class type"
      case 303: // comment
      case 305: // jmplabel
        value.copy< std::string > (that.value);
        break;

      case 302: // regs
        value.copy< std::vector<int> > (that.value);
        break;

      case 301: // args
        value.copy< std::vector<std::string> > (that.value);
        break;

      case 22: // "number"
        value.copy< uint64_t > (that.value);
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
      case 306: // instruction
        yylhs.value.build< OpCode* > ();
        break;

      case 20: // "flag"
      case 21: // "v(p)x"
      case 294: // exp
      case 295: // classdef
      case 296: // superdef
      case 297: // srcdef
      case 298: // fielddef
      case 299: // methoddef
      case 300: // flags
      case 304: // registers
        yylhs.value.build< int > ();
        break;

      case 4: // "c type string"
      case 5: // "name string"
      case 6: // "comment"
      case 7: // "class name"
      case 8: // "class type"
      case 303: // comment
      case 305: // jmplabel
        yylhs.value.build< std::string > ();
        break;

      case 302: // regs
        yylhs.value.build< std::vector<int> > ();
        break;

      case 301: // args
        yylhs.value.build< std::vector<std::string> > ();
        break;

      case 22: // "number"
        yylhs.value.build< uint64_t > ();
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
#line 392 "Parser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 1; driver.addOpcode(yystack_[0].value.as< OpCode* > ());}
#line 649 "Parser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 393 "Parser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 1; driver.endMethod();}
#line 655 "Parser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 396 "Parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 1;
        driver.setClassDefine(yystack_[1].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 663 "Parser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 400 "Parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 1;
        driver.setSuperDefine(yystack_[0].value.as< std::string > ());
    }
#line 671 "Parser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 404 "Parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 1;
        driver.setSourceDefine(yystack_[0].value.as< std::string > ());
    }
#line 679 "Parser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 408 "Parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 1;
        driver.addField(yystack_[2].value.as< std::string > (), yystack_[3].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 687 "Parser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 412 "Parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 1;
        driver.addMethod(yystack_[4].value.as< std::string > (), yystack_[5].value.as< int > (), yystack_[0].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > ());
    }
#line 695 "Parser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 416 "Parser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = 0;}
#line 701 "Parser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 417 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< int > () = yystack_[0].value.as< int > ();
    }
#line 709 "Parser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 420 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< int > () = yystack_[1].value.as< int > ();
        yylhs.value.as< int > () |= yystack_[0].value.as< int > ();
    }
#line 718 "Parser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 426 "Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();}
#line 724 "Parser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 427 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();
        yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
    }
#line 733 "Parser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 431 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::vector<std::string> > () = yystack_[1].value.as< std::vector<std::string> > ();
        yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
    }
#line 742 "Parser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 437 "Parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<int> > () = std::vector<int>();}
#line 748 "Parser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 438 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::vector<int> > () = std::vector<int>();
        yylhs.value.as< std::vector<int> > ().push_back(yystack_[0].value.as< int > ());
    }
#line 757 "Parser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 442 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::vector<int> > () = yystack_[2].value.as< std::vector<int> > ();
        yylhs.value.as< std::vector<int> > ().push_back(yystack_[0].value.as< int > ());
    }
#line 766 "Parser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 448 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();
    }
#line 774 "Parser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 454 "Parser.yy" // lalr1.cc:859
    {
        driver.setCurMethodRegSize(yystack_[0].value.as< uint64_t > ());
    }
#line 782 "Parser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 460 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();
    }
#line 790 "Parser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 466 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 798 "Parser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 469 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_FROM16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 806 "Parser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 472 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 814 "Parser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 475 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_WIDE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 822 "Parser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 478 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_WIDE_FROM16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 830 "Parser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 481 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_WIDE_16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 838 "Parser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 484 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_OBJECT, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 846 "Parser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 487 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_OBJECT_FROM16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 854 "Parser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 490 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE(OP_MOVE_OBJECT_16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 862 "Parser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 493 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_MOVE_RESULT(OP_MOVE_RESULT, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 870 "Parser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 496 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_MOVE_RESULT(OP_MOVE_RESULT_WIDE, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 878 "Parser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 499 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_MOVE_RESULT(OP_MOVE_RESULT_OBJECT, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 886 "Parser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 502 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_MOVE_EXCEPTION(OP_MOVE_EXCEPTION, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 894 "Parser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 505 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_RETURN_VOID(OP_RETURN_VOID, driver.stringPool());
    }
#line 902 "Parser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 508 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_RETURN(OP_RETURN, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 910 "Parser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 511 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_RETURN(OP_RETURN_WIDE, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 918 "Parser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 514 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_RETURN(OP_RETURN_OBJECT, driver.stringPool(), yystack_[0].value.as< int > ());
    }
#line 926 "Parser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 517 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST_D(OP_CONST_4, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< uint64_t > ());
    }
#line 934 "Parser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 520 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST_D(OP_CONST_16, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< uint64_t > ());
    }
#line 942 "Parser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 529 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST_STRING(OP_CONST_STRING, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 950 "Parser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 532 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_CONST_STRING(OP_CONST_STRING_JUMBO, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 958 "Parser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 540 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_ARRAY_LENGTH(OP_ARRAY_LENGTH, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 966 "Parser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 543 "Parser.yy" // lalr1.cc:859
    {
        yylhs.value.as< OpCode* > () = new Op_NEW_INSTANCE(OP_NEW_INSTANCE, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 974 "Parser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 546 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_NEW_ARRAY(OP_NEW_ARRAY, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 982 "Parser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 553 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_GOTO(OP_GOTO, driver.stringPool(), yystack_[0].value.as< std::string > ());
    }
#line 990 "Parser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 556 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_GOTO(OP_GOTO_16, driver.stringPool(), yystack_[0].value.as< std::string > ());
    }
#line 998 "Parser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 559 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_GOTO(OP_GOTO_32, driver.stringPool(), yystack_[0].value.as< std::string > ());
    }
#line 1006 "Parser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 569 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_EQ, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1014 "Parser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 572 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_NE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1022 "Parser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 575 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_LT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1030 "Parser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 578 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_GE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1038 "Parser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 581 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_GT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1046 "Parser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 584 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_IF_XX(OP_IF_LE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1054 "Parser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 587 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_EQZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1062 "Parser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 590 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_NEZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1070 "Parser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 593 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_LTZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1078 "Parser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 596 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_GEZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1086 "Parser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 599 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_GTZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1094 "Parser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 602 "Parser.yy" // lalr1.cc:859
    {
      yylhs.value.as< OpCode* > () = new Op_IF_XXZ(OP_IF_LEZ, driver.stringPool(), yystack_[2].value.as< int > (), yystack_[0].value.as< std::string > ());
    }
#line 1102 "Parser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 611 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1110 "Parser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 614 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_WIDE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1118 "Parser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 617 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_OBJECT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1126 "Parser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 620 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_BOOLEAN, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1134 "Parser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 623 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_BYTE, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1142 "Parser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 626 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_CHAR, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1150 "Parser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 629 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_AGET(OP_AGET_SHORT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< int > ());
    }
#line 1158 "Parser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 653 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1166 "Parser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 656 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_WIDE, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1174 "Parser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 659 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_OBJECT, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1182 "Parser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 662 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_BOOLEAN, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1190 "Parser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 665 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_BYTE, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1198 "Parser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 668 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_CHAR, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1206 "Parser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 671 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SGET(OP_SGET_SHORT, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1214 "Parser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 674 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1222 "Parser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 677 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_WIDE, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1230 "Parser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 680 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_OBJECT, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1238 "Parser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 683 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_BOOLEAN, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1246 "Parser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 686 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_BYTE, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1254 "Parser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 689 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_CHAR, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1262 "Parser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 692 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_SPUT(OP_SPUT_SHORT, driver.stringPool(), yystack_[6].value.as< int > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
    }
#line 1270 "Parser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 695 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE(OP_INVOKE_VIRTUAL, driver.stringPool(), yystack_[9].value.as< std::vector<int> > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1278 "Parser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 698 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE(OP_INVOKE_SUPER, driver.stringPool(), yystack_[9].value.as< std::vector<int> > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1286 "Parser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 701 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE(OP_INVOKE_DIRECT, driver.stringPool(), yystack_[9].value.as< std::vector<int> > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1294 "Parser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 704 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE(OP_INVOKE_STATIC, driver.stringPool(), yystack_[9].value.as< std::vector<int> > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1302 "Parser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 707 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_INVOKE(OP_INVOKE_INTERFACE, driver.stringPool(), yystack_[9].value.as< std::vector<int> > (), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::string > ());
    }
#line 1310 "Parser.cpp" // lalr1.cc:859
    break;

  case 240:
#line 803 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_ADD_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< uint64_t > ());
    }
#line 1318 "Parser.cpp" // lalr1.cc:859
    break;

  case 241:
#line 806 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_RSUB_INT, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< uint64_t > ());
    }
#line 1326 "Parser.cpp" // lalr1.cc:859
    break;

  case 242:
#line 809 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_MUL_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< uint64_t > ());
    }
#line 1334 "Parser.cpp" // lalr1.cc:859
    break;

  case 243:
#line 812 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_DIV_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< uint64_t > ());
    }
#line 1342 "Parser.cpp" // lalr1.cc:859
    break;

  case 244:
#line 815 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_REM_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< uint64_t > ());
    }
#line 1350 "Parser.cpp" // lalr1.cc:859
    break;

  case 245:
#line 818 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_AND_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< uint64_t > ());
    }
#line 1358 "Parser.cpp" // lalr1.cc:859
    break;

  case 246:
#line 821 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_OR_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< uint64_t > ());
    }
#line 1366 "Parser.cpp" // lalr1.cc:859
    break;

  case 247:
#line 824 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_XOR_INT_LIT16, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< uint64_t > ());
    }
#line 1374 "Parser.cpp" // lalr1.cc:859
    break;

  case 248:
#line 827 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_ADD_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< uint64_t > ());
    }
#line 1382 "Parser.cpp" // lalr1.cc:859
    break;

  case 249:
#line 830 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_RSUB_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< uint64_t > ());
    }
#line 1390 "Parser.cpp" // lalr1.cc:859
    break;

  case 250:
#line 833 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_MUL_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< uint64_t > ());
    }
#line 1398 "Parser.cpp" // lalr1.cc:859
    break;

  case 251:
#line 836 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_DIV_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< uint64_t > ());
    }
#line 1406 "Parser.cpp" // lalr1.cc:859
    break;

  case 252:
#line 839 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_REM_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< uint64_t > ());
    }
#line 1414 "Parser.cpp" // lalr1.cc:859
    break;

  case 253:
#line 842 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_AND_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< uint64_t > ());
    }
#line 1422 "Parser.cpp" // lalr1.cc:859
    break;

  case 254:
#line 845 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_OR_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< uint64_t > ());
    }
#line 1430 "Parser.cpp" // lalr1.cc:859
    break;

  case 255:
#line 848 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_XOR_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< uint64_t > ());
    }
#line 1438 "Parser.cpp" // lalr1.cc:859
    break;

  case 256:
#line 851 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_SHL_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< uint64_t > ());
    }
#line 1446 "Parser.cpp" // lalr1.cc:859
    break;

  case 257:
#line 854 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_SHR_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< uint64_t > ());
    }
#line 1454 "Parser.cpp" // lalr1.cc:859
    break;

  case 258:
#line 857 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_X_INT_LIT(OP_USHR_INT_LIT8, driver.stringPool(), yystack_[4].value.as< int > (), yystack_[2].value.as< int > (), yystack_[0].value.as< uint64_t > ());
    }
#line 1462 "Parser.cpp" // lalr1.cc:859
    break;

  case 288:
#line 889 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_JmpLabel(OP_UNUSED_FF, driver.stringPool(), yystack_[0].value.as< std::string > ());
    }
#line 1470 "Parser.cpp" // lalr1.cc:859
    break;

  case 289:
#line 892 "Parser.yy" // lalr1.cc:859
    {
       yylhs.value.as< OpCode* > () = new Op_CATCH(OP_UNUSED_FF, driver.stringPool(), yystack_[6].value.as< std::string > (), yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());
   }
#line 1478 "Parser.cpp" // lalr1.cc:859
    break;


#line 1482 "Parser.cpp" // lalr1.cc:859
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


  const short int  Parser ::yypact_ninf_ = -395;

  const signed char  Parser ::yytable_ninf_ = -1;

  const short int
   Parser ::yypact_[] =
  {
    -395,     2,  -395,   296,  -395,  -395,   -16,   304,   309,   -16,
     -16,  -395,   292,  -395,   294,   295,   297,   298,   299,   300,
     302,   303,   305,   306,   307,   308,   310,  -395,   311,   312,
     313,   314,   315,  -395,  -395,  -395,  -395,  -395,  -395,   316,
     317,  -395,  -395,  -395,  -395,  -395,   318,   319,   320,  -395,
    -395,  -395,  -395,    34,    34,    34,  -395,  -395,  -395,  -395,
    -395,  -395,  -395,   321,   322,   323,   324,   325,   332,   333,
     334,   335,   336,   337,   338,  -395,  -395,  -395,  -395,  -395,
    -395,   339,   340,   341,   342,   343,   344,   345,  -395,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,    37,    42,    93,    94,    95,  -395,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,   363,   364,   365,   366,   367,   368,   369,   370,   371,
     372,   373,   374,   375,   376,   377,   379,   380,   381,   382,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,   396,
     400,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,  -395,   281,  -395,  -395,     5,   282,  -395,    36,   120,
     121,   122,   123,   124,   125,   126,   127,  -395,  -395,  -395,
    -395,  -395,  -395,  -395,   128,   129,   130,   131,   132,   133,
     134,   416,  -395,  -395,  -395,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   434,   434,
     434,   434,   434,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,  -395,  -395,  -395,   192,   194,   455,   458,
     459,   466,   467,   468,   469,   470,   471,   472,   473,   489,
     492,   476,   490,   478,  -395,   479,   480,   481,   482,   483,
     484,    34,    34,    34,    34,    34,    34,   485,   486,   487,
     488,   491,   493,   494,   502,   503,   505,   508,   509,   510,
     511,   512,   513,   514,   515,   516,   517,   518,  -395,     9,
      14,    18,    19,    20,   506,   507,   519,   520,   521,   522,
     523,   524,   525,   526,   527,   528,   529,   530,   531,   532,
     533,   534,   535,    34,   549,   550,  -395,  -395,  -395,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,   243,   244,   245,   246,   248,   249,   250,  -395,  -395,
    -395,  -395,  -395,  -395,   251,   252,   253,   273,   274,   275,
     276,   277,   278,   279,   280,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   293,   542,   326,   327,   328,   329,
     330,   331,   360,   361,   362,   378,   383,   384,   385,   386,
     387,   388,   389,   390,   391,   392,   393,   394,   395,   397,
     398,  -395,  -395,    -2,   560,    34,    34,    34,    34,    34,
      34,   548,   558,   561,   562,   563,   564,   565,   576,   582,
     583,   584,   585,   586,   587,   588,   589,   590,   591,   592,
     593,   594,  -395,   595,   596,   597,   598,   599,   578,   579,
     580,   600,   601,   602,   603,   604,   605,   606,   607,   608,
     609,   610,   611,   612,   613,   614,   615,    34,  -395,   630,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,  -395,  -395,  -395,   399,   401,   402,   403,   404,   406,
     407,   408,   409,   410,   411,   412,   413,   414,   415,   417,
     418,   419,   420,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,  -395,   421,  -395,   631,   632,   633,   634,   635,   636,
     637,   641,   642,   643,   644,   645,   646,   647,   616,   651,
     652,   653,   654,    34,  -395,  -395,  -395,  -395,  -395,  -395,
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,   424,   425,
     427,   428,   429,  -395,   550,   550,   550,   550,   550,    -1,
       1,     3,    11,    12,   655,   657,   658,   659,   660,  -395,
    -395,  -395,  -395,  -395
  };

  const unsigned short int
   Parser ::yydefact_[] =
  {
       2,     0,     1,     0,     3,    29,    20,     0,     0,    20,
      20,    14,     0,    32,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    46,     0,     0,
       0,     0,     0,    52,    53,    54,    55,    56,    57,     0,
       0,    60,    61,    62,    63,    64,     0,     0,     0,    68,
      69,    70,    71,     0,     0,     0,    75,    76,    77,    78,
      79,    80,    81,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    94,    95,    96,    97,    98,
      99,     0,     0,     0,     0,     0,     0,     0,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,     0,
       0,     5,     7,     8,     9,    10,    11,     4,    12,    13,
       6,    21,     0,    16,    17,     0,     0,    30,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    42,    43,    44,
      45,    47,    48,    49,     0,     0,     0,     0,     0,     0,
       0,     0,    72,    73,    74,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    26,    26,
      26,    26,    26,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   288,    15,    22,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    31,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    23,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    50,    51,    58,    59,    65,
      66,     0,     0,     0,     0,     0,     0,     0,    88,    89,
      90,    91,    92,    93,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    18,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    28,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    25,     0,
      67,    82,    83,    84,    85,    86,    87,   100,   101,   102,
     103,   104,   105,   106,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,     0,    19,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,     0,     0,
       0,     0,     0,   289,    23,    23,    23,    23,    23,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   142,
     143,   144,   145,   146
  };

  const short int
   Parser ::yypgoto_[] =
  {
    -395,  -395,  -395,  -395,  -395,  -395,  -395,  -395,   301,  -394,
    -328,  -395,  -395,   -54,  -395
  };

  const short int
   Parser ::yydefgoto_[] =
  {
      -1,     1,   271,   272,   273,   274,   275,   276,   282,   533,
     429,   277,   278,   312,   279
  };

  const unsigned short int
   Parser ::yytable_[] =
  {
     313,   314,     2,     3,   281,     4,   588,   588,     5,   588,
     376,   588,     6,     7,     8,     9,    10,    11,    12,   588,
     588,   430,   431,   432,   433,   375,    13,    14,    15,    16,
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
     267,   268,   269,   589,   694,   270,   695,   377,   696,   374,
     689,   690,   691,   692,   693,   505,   697,   698,   506,   280,
     505,   375,   375,   507,   505,   505,   505,   508,   509,   510,
     285,   286,   283,   284,   287,   288,   289,   311,   290,   291,
     292,   293,   378,   294,   295,   348,   296,   297,   298,   299,
     349,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   315,   316,   317,   318,   319,   478,   479,   480,
     481,   482,   483,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   362,   363,   364,   365,   366,   367,   530,
     368,   369,   370,   371,   372,   373,   379,   380,   381,   382,
     383,   384,   385,   386,   387,   388,   389,   390,   391,   392,
     393,   394,   395,   396,   397,   398,   399,   400,   401,   402,
     403,   404,   405,   406,   407,   408,   409,   410,   411,   412,
     413,   414,   415,   416,   417,   418,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   428,   434,   435,   436,   437,
     438,   439,   440,   441,   442,   443,   444,   445,   446,   447,
     448,   449,   450,   451,   452,   454,   456,   453,   455,   457,
     458,   591,   592,   593,   594,   595,   596,   459,   460,   461,
     462,   463,   464,   467,   465,   466,   468,   469,   470,   471,
     472,   473,   474,   475,   476,   477,   484,   485,   486,   487,
     491,   492,   488,   493,   489,   490,   494,   495,   496,   497,
     498,   499,   500,   501,   502,   503,   504,   511,   512,   534,
     535,   536,   537,   642,   538,   539,   540,   541,   542,   543,
     513,   514,   515,   516,   517,   518,   519,   520,   521,   522,
     523,   524,   525,   526,   527,   528,   529,   531,   532,   544,
     545,   546,   547,   562,   548,   549,   550,   551,   590,   597,
     552,   553,   554,   555,   556,   557,   558,   559,   560,   598,
     561,   604,   599,   600,   601,   602,   603,   605,   606,   607,
     608,   609,   610,   611,   612,   613,   614,   615,   616,   617,
     623,   624,   625,   618,   619,   620,   621,   622,     0,   683,
       0,     0,   563,   564,   565,   566,   567,   568,     0,     0,
       0,   678,   626,   627,   628,   629,   630,   631,   632,   633,
     634,   635,   636,   637,   638,   639,   640,   641,   643,   664,
     665,   666,   667,   668,   669,   670,   569,   570,   571,   671,
     672,   673,   674,   675,   676,   677,   679,   680,   681,   682,
       0,     0,     0,   699,   572,   700,   701,   702,   703,   573,
     574,   575,   576,   577,   578,   579,   580,   581,   582,   583,
     584,   585,   644,   586,   645,   646,   647,   648,   587,   649,
     650,   651,   652,   653,   654,   655,   656,   657,     0,     0,
       0,     0,   658,     0,   659,   660,   661,   662,   684,   685,
     663,   686,   687,   688
  };

  const short int
   Parser ::yycheck_[] =
  {
      54,    55,     0,     1,    20,     3,     8,     8,     6,     8,
       5,     8,    10,    11,    12,    13,    14,    15,    16,     8,
       8,   349,   350,   351,   352,    20,    24,    25,    26,    27,
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
     278,   279,   280,   285,   285,   283,   285,     5,   285,     8,
     684,   685,   686,   687,   688,   286,   285,   285,   289,     3,
     286,    20,    20,   289,   286,   286,   286,   289,   289,   289,
       9,    10,     8,     4,    22,    21,    21,   283,    21,    21,
      21,    21,   286,    21,    21,   288,    21,    21,    21,    21,
     288,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,   401,   402,   403,
     404,   405,   406,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,   288,   288,   288,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,   453,
      21,    21,    21,    21,     8,     5,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,     5,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,    21,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   283,    21,   288,   284,    21,
      21,   535,   536,   537,   538,   539,   540,    21,    21,    21,
      21,    21,    21,     4,    22,    22,     4,    21,     8,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
       8,     8,    21,     8,    21,    21,     8,     8,     8,     8,
       8,     8,     8,     8,     8,     8,     8,    21,    21,   286,
     286,   286,   286,   587,   286,   286,   286,   286,   286,   286,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,     8,     8,   286,
     286,   286,   286,    21,   287,   287,   287,   287,     8,    21,
     287,   287,   287,   287,   287,   287,   287,   287,   287,    21,
     287,     5,    21,    21,    21,    21,    21,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
      22,    22,    22,     8,     8,     8,     8,     8,    -1,   663,
      -1,    -1,   286,   286,   286,   286,   286,   286,    -1,    -1,
      -1,     5,    22,    22,    22,    22,    22,    22,    22,    22,
      22,    22,    22,    22,    22,    22,    22,    22,     8,     8,
       8,     8,     8,     8,     8,     8,   286,   286,   286,     8,
       8,     8,     8,     8,     8,     8,     5,     5,     5,     5,
      -1,    -1,    -1,     8,   286,     8,     8,     8,     8,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   283,   286,   283,   283,   283,   283,   290,   283,
     283,   283,   283,   283,   283,   283,   283,   283,    -1,    -1,
      -1,    -1,   287,    -1,   287,   287,   287,   287,   284,   284,
     289,   284,   284,   284
  };

  const unsigned short int
   Parser ::yystos_[] =
  {
       0,   293,     0,     1,     3,     6,    10,    11,    12,    13,
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
     283,   294,   295,   296,   297,   298,   299,   303,   304,   306,
       3,    20,   300,     8,     4,   300,   300,    22,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,   283,   305,   305,   305,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,   288,   288,
     288,   288,   288,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,     8,     5,     8,    20,     5,     5,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,     5,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,    21,   302,
     302,   302,   302,   302,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   288,   283,   284,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    22,    22,     4,     4,    21,
       8,    21,    21,    21,    21,    21,    21,    21,   305,   305,
     305,   305,   305,   305,    21,    21,    21,    21,    21,    21,
      21,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,     8,     8,     8,     8,   286,   289,   289,   289,   289,
     289,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
     305,     8,     8,   301,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,    21,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   290,     8,   285,
       8,   305,   305,   305,   305,   305,   305,    21,    21,    21,
      21,    21,    21,    21,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     8,     8,
       8,     8,     8,    22,    22,    22,    22,    22,    22,    22,
      22,    22,    22,    22,    22,    22,    22,    22,    22,    22,
      22,    22,   305,     8,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   287,   287,
     287,   287,   287,   289,     8,     8,     8,     8,     8,     8,
       8,     8,     8,     8,     8,     8,     8,     8,     5,     5,
       5,     5,     5,   305,   284,   284,   284,   284,   284,   301,
     301,   301,   301,   301,   285,   285,   285,   285,   285,     8,
       8,     8,     8,     8
  };

  const unsigned short int
   Parser ::yyr1_[] =
  {
       0,   292,   293,   293,   293,   293,   293,   294,   294,   294,
     294,   294,   294,   294,   294,   295,   296,   297,   298,   299,
     300,   300,   300,   301,   301,   301,   302,   302,   302,   303,
     304,   305,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306
  };

  const unsigned char
   Parser ::yyr2_[] =
  {
       0,     2,     0,     2,     2,     2,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     2,     2,     5,     7,
       0,     1,     2,     0,     1,     2,     0,     1,     3,     1,
       2,     2,     1,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     2,     2,     2,     2,     1,     2,     2,     2,
       4,     4,     1,     1,     1,     1,     1,     1,     4,     4,
       1,     1,     1,     1,     1,     4,     4,     6,     1,     1,
       1,     1,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     6,     6,     6,     6,     6,     6,     4,     4,
       4,     4,     4,     4,     1,     1,     1,     1,     1,     1,
       6,     6,     6,     6,     6,     6,     6,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     8,     8,
       8,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,     8,    12,    12,    12,    12,    12,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
  "\"begin of symbol\"", "\":\"", "\"(\"", "\")\"", "\",\"", "\"->\"",
  "\"{\"", "\"}\"", "\"..\"", "\"end of symbol\"", "$accept", "program",
  "exp", "classdef", "superdef", "srcdef", "fielddef", "methoddef",
  "flags", "args", "regs", "comment", "registers", "jmplabel",
  "instruction", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
   Parser ::yyrline_[] =
  {
       0,   379,   379,   380,   381,   382,   383,   386,   387,   388,
     389,   390,   391,   392,   393,   396,   400,   404,   408,   412,
     416,   417,   420,   426,   427,   431,   437,   438,   442,   448,
     454,   460,   465,   466,   469,   472,   475,   478,   481,   484,
     487,   490,   493,   496,   499,   502,   505,   508,   511,   514,
     517,   520,   523,   524,   525,   526,   527,   528,   529,   532,
     535,   536,   537,   538,   539,   540,   543,   546,   549,   550,
     551,   552,   553,   556,   559,   562,   563,   564,   565,   566,
     567,   568,   569,   572,   575,   578,   581,   584,   587,   590,
     593,   596,   599,   602,   605,   606,   607,   608,   609,   610,
     611,   614,   617,   620,   623,   626,   629,   632,   633,   634,
     635,   636,   637,   638,   639,   640,   641,   642,   643,   644,
     645,   646,   647,   648,   649,   650,   651,   652,   653,   656,
     659,   662,   665,   668,   671,   674,   677,   680,   683,   686,
     689,   692,   695,   698,   701,   704,   707,   710,   711,   712,
     713,   714,   715,   716,   717,   718,   719,   720,   721,   722,
     723,   724,   725,   726,   727,   728,   729,   730,   731,   732,
     733,   734,   735,   736,   737,   738,   739,   740,   741,   742,
     743,   744,   745,   746,   747,   748,   749,   750,   751,   752,
     753,   754,   755,   756,   757,   758,   759,   760,   761,   762,
     763,   764,   765,   766,   767,   768,   769,   770,   771,   772,
     773,   774,   775,   776,   777,   778,   779,   780,   781,   782,
     783,   784,   785,   786,   787,   788,   789,   790,   791,   792,
     793,   794,   795,   796,   797,   798,   799,   800,   801,   802,
     803,   806,   809,   812,   815,   818,   821,   824,   827,   830,
     833,   836,   839,   842,   845,   848,   851,   854,   857,   860,
     861,   862,   863,   864,   865,   866,   867,   868,   869,   870,
     871,   872,   873,   874,   875,   876,   877,   878,   879,   880,
     881,   882,   883,   884,   885,   886,   887,   888,   889,   892
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
#line 2370 "Parser.cpp" // lalr1.cc:1167
#line 896 "Parser.yy" // lalr1.cc:1168


void Analysis::Parser::error(const location &loc, const std::string &message) {
	cout << "Parse error: " << message << endl
	    << "Error location: " << loc << endl << driver.mLexer.text() << endl;
}
