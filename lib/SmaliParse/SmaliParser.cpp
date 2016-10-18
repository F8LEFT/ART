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
    //#include "Interpreter.h"
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
      case 48: // "true|false"
      case 51: // "flag"
      case 52: // "v(p)x"
        value.move< int > (that.value);
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
        value.move< std::string > (that.value);
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
      case 48: // "true|false"
      case 51: // "flag"
      case 52: // "v(p)x"
        value.copy< int > (that.value);
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
        value.copy< std::string > (that.value);
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
      case 48: // "true|false"
      case 51: // "flag"
      case 52: // "v(p)x"
        yylhs.value.build< int > ();
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
        yylhs.value.build< std::string > ();
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

#line 628 "SmaliParser.cpp" // lalr1.cc:859
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


  const signed char  SmaliParser ::yypact_ninf_ = -1;

  const signed char  SmaliParser ::yytable_ninf_ = -1;

  const signed char
   SmaliParser ::yypact_[] =
  {
      -1,     0,    -1
  };

  const unsigned char
   SmaliParser ::yydefact_[] =
  {
       2,     0,     1
  };

  const signed char
   SmaliParser ::yypgoto_[] =
  {
      -1,    -1
  };

  const signed char
   SmaliParser ::yydefgoto_[] =
  {
      -1,     1
  };

  const unsigned char
   SmaliParser ::yytable_[] =
  {
       2
  };

  const unsigned char
   SmaliParser ::yycheck_[] =
  {
       0
  };

  const unsigned short int
   SmaliParser ::yystos_[] =
  {
       0,   338,     0
  };

  const unsigned short int
   SmaliParser ::yyr1_[] =
  {
       0,   337,   338
  };

  const unsigned char
   SmaliParser ::yyr2_[] =
  {
       0,     2,     0
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
  "\".epilogue\"", "\"end of keywords\"", "NUMBER_BEGIN", "\"Integer\"",
  "\"- Integer\"", "\"- Integer L\"", "\"- Integer S\"", "\"- Integer T\"",
  "\"FloatOrID F\"", "\"FloatOrID D\"", "\"Float F\"", "\"Float D\"",
  "\"true|false\"", "\"null\"", "NUMBER_END", "\"flag\"", "\"v(p)x\"",
  "\"ZBSCIJFDLIT\"", "\"ZBSCIJFD\"", "\"Lxxx;\"", "\"[[\"", "\"V\"",
  "\"simple name\"", "\"member name\"", "\"string\"", "\"char\"",
  "\"build runtime system\"", "\"ver type error\"", "\"inline@0x\"",
  "\"vtable@0x\"", "\"field@0x\"", "\"#xxx\"", "\"begin of opcodes\"",
  "\"nop\"", "\"move\"", "\"move/from16\"", "\"move/16\"", "\"move-wide\"",
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
  "\"end of symbol\"", "$accept", "program", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
   SmaliParser ::yyrline_[] =
  {
       0,   430,   430
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
#line 1087 "SmaliParser.cpp" // lalr1.cc:1167
#line 432 "SmaliParser.yy" // lalr1.cc:1168


void Analysis::SmaliParser::error(const location &loc, const std::string &message) {
	//cout << "Parse error: " << message << endl
	//    << "Error location: " << loc << endl << driver.mLexer->text() << endl;
}
