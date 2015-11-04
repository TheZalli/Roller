/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "Roller.y" /* yacc.c:339  */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include "Absyn.H"
typedef struct yy_buffer_state *YY_BUFFER_STATE;
int yyparse(void);
int yylex(void);
YY_BUFFER_STATE yy_scan_string(const char *str);
void yy_delete_buffer(YY_BUFFER_STATE buf);
int yy_mylinenumber;
int initialize_lexer(FILE * inp);
int yywrap(void)
{
  return 1;
}
void yyerror(const char *str)
{
  extern char *yytext;
  fprintf(stderr,"error: line %d: %s at %s\n", 
    yy_mylinenumber, str, yytext);
}



static Cmd* YY_RESULT_Cmd_ = 0;
Cmd* pCmd(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Cmd_;
  }
}
Cmd* pCmd(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Cmd_;
  }
}

static Exp* YY_RESULT_Exp_ = 0;
Exp* pExp(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}
Exp* pExp(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}

static ListExp* YY_RESULT_ListExp_ = 0;
ListExp* pListExp(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListExp_;
  }
}
ListExp* pListExp(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListExp_;
  }
}

static Numeral* YY_RESULT_Numeral_ = 0;
Numeral* pNumeral(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Numeral_;
  }
}
Numeral* pNumeral(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Numeral_;
  }
}

static Val* YY_RESULT_Val_ = 0;
Val* pVal(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Val_;
  }
}
Val* pVal(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Val_;
  }
}

static Range* YY_RESULT_Range_ = 0;
Range* pRange(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Range_;
  }
}
Range* pRange(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Range_;
  }
}

static ExpD* YY_RESULT_ExpD_ = 0;
ExpD* pExpD(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ExpD_;
  }
}
ExpD* pExpD(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ExpD_;
  }
}

static ExpKW* YY_RESULT_ExpKW_ = 0;
ExpKW* pExpKW(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ExpKW_;
  }
}
ExpKW* pExpKW(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ExpKW_;
  }
}

static Pred* YY_RESULT_Pred_ = 0;
Pred* pPred(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Pred_;
  }
}
Pred* pPred(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Pred_;
  }
}

static ListPred* YY_RESULT_ListPred_ = 0;
ListPred* pListPred(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListPred_;
  }
}
ListPred* pListPred(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListPred_;
  }
}

static Stmt* YY_RESULT_Stmt_ = 0;
Stmt* pStmt(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Stmt_;
  }
}
Stmt* pStmt(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Stmt_;
  }
}




#line 460 "Parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    _ERROR_ = 258,
    _SYMB_0 = 259,
    _SYMB_1 = 260,
    _SYMB_2 = 261,
    _SYMB_3 = 262,
    _SYMB_4 = 263,
    _SYMB_5 = 264,
    _SYMB_6 = 265,
    _SYMB_7 = 266,
    _SYMB_8 = 267,
    _SYMB_9 = 268,
    _SYMB_10 = 269,
    _SYMB_11 = 270,
    _SYMB_12 = 271,
    _SYMB_13 = 272,
    _SYMB_14 = 273,
    _SYMB_15 = 274,
    _SYMB_16 = 275,
    _SYMB_17 = 276,
    _SYMB_18 = 277,
    _SYMB_19 = 278,
    _SYMB_20 = 279,
    _SYMB_21 = 280,
    _SYMB_22 = 281,
    _SYMB_23 = 282,
    _SYMB_24 = 283,
    _SYMB_25 = 284,
    _SYMB_26 = 285,
    _SYMB_27 = 286,
    _SYMB_28 = 287,
    _SYMB_29 = 288,
    _SYMB_30 = 289,
    _SYMB_31 = 290,
    _SYMB_32 = 291,
    _SYMB_33 = 292,
    _SYMB_34 = 293,
    _SYMB_35 = 294,
    _SYMB_36 = 295,
    _SYMB_37 = 296,
    _SYMB_38 = 297,
    _SYMB_39 = 298,
    _STRING_ = 299,
    _INTEGER_ = 300,
    _DOUBLE_ = 301
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 397 "Roller.y" /* yacc.c:355  */

  int int_;
  char char_;
  double double_;
  char* string_;
  Cmd* cmd_;
  Exp* exp_;
  ListExp* listexp_;
  Numeral* numeral_;
  Val* val_;
  Range* range_;
  ExpD* expd_;
  ExpKW* expkw_;
  Pred* pred_;
  ListPred* listpred_;
  Stmt* stmt_;

#line 562 "Parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 579 "Parser.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
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


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  53
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   232

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  129

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      45,    46
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   482,   482,   483,   485,   486,   487,   489,   490,   491,
     493,   494,   495,   496,   498,   499,   500,   501,   502,   503,
     504,   506,   508,   509,   510,   512,   513,   515,   516,   517,
     519,   520,   521,   522,   524,   525,   526,   527,   529,   530,
     531,   532,   533,   534,   535,   536,   537,   538,   540,   542,
     543,   544,   545,   547,   548,   549,   550,   551,   552,   554,
     555,   556,   557,   558,   559,   561,   562,   563,   565,   566,
     567,   568,   569,   570
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "_ERROR_", "_SYMB_0", "_SYMB_1",
  "_SYMB_2", "_SYMB_3", "_SYMB_4", "_SYMB_5", "_SYMB_6", "_SYMB_7",
  "_SYMB_8", "_SYMB_9", "_SYMB_10", "_SYMB_11", "_SYMB_12", "_SYMB_13",
  "_SYMB_14", "_SYMB_15", "_SYMB_16", "_SYMB_17", "_SYMB_18", "_SYMB_19",
  "_SYMB_20", "_SYMB_21", "_SYMB_22", "_SYMB_23", "_SYMB_24", "_SYMB_25",
  "_SYMB_26", "_SYMB_27", "_SYMB_28", "_SYMB_29", "_SYMB_30", "_SYMB_31",
  "_SYMB_32", "_SYMB_33", "_SYMB_34", "_SYMB_35", "_SYMB_36", "_SYMB_37",
  "_SYMB_38", "_SYMB_39", "_STRING_", "_INTEGER_", "_DOUBLE_", "$accept",
  "Cmd", "Exp1", "Exp2", "Exp3", "Exp4", "Exp", "ListExp", "Numeral",
  "Val", "Range", "ExpD", "ExpKW", "Pred", "Pred1", "Pred2", "Pred3",
  "ListPred", "Stmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301
};
# endif

#define YYPACT_NINF -64

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-64)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     129,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   186,     7,   -64,   -64,   -64,    31,
      17,    12,    20,   -64,    27,   -64,   -64,   -64,   -64,   -64,
      24,    27,    13,    16,    30,    52,    -9,    27,    27,    27,
      27,   114,    27,    27,    27,    27,   -64,   171,   171,   171,
     171,   171,   171,   -64,   171,   171,   171,   171,   186,   186,
      72,   171,   -64,   171,   171,   -64,   -64,   -64,    27,    14,
      88,    27,    27,    27,    27,    27,    12,    27,    12,    20,
      20,   -64,   -64,    72,    42,    42,    42,    42,    42,    72,
     -64,   -64,   -64,    27,    71,    58,   -64,   -64,    73,    89,
      18,   -64,    27,   171,    84,    13,    92,   -64,   -64,   -64,
     -64,   -64,   -64,   -64,    72,    72,    72,    72,   -64,   -64,
     171,   171,   -64,   -64,   -64,   -64,   -64,    27,    27
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    22,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    34,    28,    29,    25,    26,     0,
      21,     6,     9,    11,     2,    27,    16,    12,    19,     3,
      28,    14,     0,    23,     0,     0,     0,    44,    39,    43,
      41,     0,    45,    42,    40,    46,    35,    22,     0,     0,
       0,     0,     0,     1,     0,     0,     0,     0,     0,    36,
      65,    22,    15,    22,    32,    17,    18,    47,    38,    23,
       0,    68,    69,    70,    71,    72,     4,     0,     5,     7,
       8,    10,    37,     0,     0,     0,     0,     0,     0,     0,
      61,    62,    63,    64,    66,    48,    49,    53,     0,     0,
      23,    24,    30,    22,    20,    64,     0,    28,    54,    55,
      56,    57,    58,    60,    65,     0,     0,     0,    13,    20,
      33,     0,    59,    67,    52,    50,    51,    31,    73
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -64,   -64,   -64,    21,   -11,     1,     0,    11,   -64,   -17,
     -64,   -64,   -64,   -63,   -64,   -37,   -64,     8,   -64
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    93,   101,    25,    26,
      35,    27,    28,    94,    95,    96,    97,    98,    29
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      24,    31,    32,    33,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    34,    46,    47,    60,    56,    57,
     106,    54,    55,    62,    48,   103,   113,    63,    58,   103,
      64,    53,   120,    61,    67,    49,    50,    51,    52,    60,
      60,    68,    60,    65,    60,    79,    80,    69,    71,    72,
      73,    74,    75,    60,    77,    77,    77,    77,    70,    81,
      82,    69,    59,   100,   102,    66,   115,   108,   109,   110,
     111,   112,    99,   116,   117,    76,    78,     1,   124,   125,
     126,    83,   114,   105,     3,   107,    16,    17,    18,    84,
      85,    86,    87,    88,    89,    90,    91,    92,   104,   119,
     118,   121,   122,    69,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    30,    16,    17,    18,     1,
     127,   128,   123,     2,     0,     0,     3,     0,     0,     0,
       0,     0,     0,     0,     1,     0,     0,     0,     2,     0,
      60,     3,     0,     0,     0,     0,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    30,    16,    17,
      18,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,     1,     0,     0,     0,
       2,     0,     0,     3,     0,     0,     0,     0,     0,     0,
       0,     1,     0,     0,     0,     2,     0,     0,     3,     0,
       0,     0,     0,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    30,    16,    17,    18,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,     0,    30,
      16,    17,    18
};

static const yytype_int8 yycheck[] =
{
       0,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     3,    14,     9,    26,     6,     7,
      83,     4,     5,    10,    17,    11,    89,    11,     8,    11,
      14,     0,    14,     9,    43,    28,    29,    30,    31,    26,
      26,    41,    26,    13,    26,    56,    57,    47,    48,    49,
      50,    51,    52,    26,    54,    55,    56,    57,    47,    58,
      59,    61,    42,    63,    64,    13,     8,    84,    85,    86,
      87,    88,    61,    15,    16,    54,    55,     5,   115,   116,
     117,     9,    11,    83,    12,    43,    44,    45,    46,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    10,    10,
      27,    17,    10,   103,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,     5,
     120,   121,   114,     9,    -1,    -1,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     5,    -1,    -1,    -1,     9,    -1,
      26,    12,    -1,    -1,    -1,    -1,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,     5,    -1,    -1,    -1,
       9,    -1,    -1,    12,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     5,    -1,    -1,    -1,     9,    -1,    -1,    12,    -1,
      -1,    -1,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    -1,    43,
      44,    45,    46
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     9,    12,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    48,
      49,    50,    51,    52,    53,    55,    56,    58,    59,    65,
      43,    53,    53,    53,    54,    57,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    52,     9,    17,    28,
      29,    30,    31,     0,     4,     5,     6,     7,     8,    42,
      26,     9,    10,    11,    14,    13,    13,    43,    53,    53,
      54,    53,    53,    53,    53,    53,    50,    53,    50,    51,
      51,    52,    52,     9,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    53,    60,    61,    62,    63,    64,    54,
      53,    54,    53,    11,    10,    53,    60,    43,    56,    56,
      56,    56,    56,    60,    11,     8,    15,    16,    27,    10,
      14,    17,    10,    64,    62,    62,    62,    53,    53
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    48,    49,    49,    49,    50,    50,    50,
      51,    51,    51,    51,    52,    52,    52,    52,    52,    52,
      52,    53,    54,    54,    54,    55,    55,    56,    56,    56,
      57,    57,    57,    57,    58,    58,    58,    58,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    60,    61,
      61,    61,    61,    62,    62,    62,    62,    62,    62,    63,
      63,    63,    63,    63,    63,    64,    64,    64,    65,    65,
      65,    65,    65,    65
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     3,     3,     1,     3,     3,     1,
       3,     1,     1,     4,     2,     3,     1,     3,     3,     1,
       4,     1,     0,     1,     3,     1,     1,     1,     1,     1,
       3,     5,     2,     4,     1,     2,     2,     3,     3,     2,
       2,     2,     2,     2,     2,     2,     2,     3,     1,     1,
       3,     3,     3,     1,     2,     2,     2,     2,     2,     3,
       2,     1,     1,     1,     1,     0,     1,     3,     3,     3,
       3,     3,     3,     6
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 482 "Roller.y" /* yacc.c:1646  */
    {  (yyval.cmd_) = new ExpCmd((yyvsp[0].exp_)); YY_RESULT_Cmd_= (yyval.cmd_); }
#line 1767 "Parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 483 "Roller.y" /* yacc.c:1646  */
    {  (yyval.cmd_) = new StmtCmd((yyvsp[0].stmt_)); YY_RESULT_Cmd_= (yyval.cmd_); }
#line 1773 "Parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 485 "Roller.y" /* yacc.c:1646  */
    {  (yyval.exp_) = new EAdd((yyvsp[-2].exp_), (yyvsp[0].exp_)); YY_RESULT_Exp_= (yyval.exp_); }
#line 1779 "Parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 486 "Roller.y" /* yacc.c:1646  */
    {  (yyval.exp_) = new ESub((yyvsp[-2].exp_), (yyvsp[0].exp_)); YY_RESULT_Exp_= (yyval.exp_); }
#line 1785 "Parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 487 "Roller.y" /* yacc.c:1646  */
    {  (yyval.exp_) = (yyvsp[0].exp_); YY_RESULT_Exp_= (yyval.exp_); }
#line 1791 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 7:
#line 489 "Roller.y" /* yacc.c:1646  */
    {  (yyval.exp_) = new EMul((yyvsp[-2].exp_), (yyvsp[0].exp_)); YY_RESULT_Exp_= (yyval.exp_); }
#line 1797 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 8:
#line 490 "Roller.y" /* yacc.c:1646  */
    {  (yyval.exp_) = new EDiv((yyvsp[-2].exp_), (yyvsp[0].exp_)); YY_RESULT_Exp_= (yyval.exp_); }
#line 1803 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 9:
#line 491 "Roller.y" /* yacc.c:1646  */
    {  (yyval.exp_) = (yyvsp[0].exp_); YY_RESULT_Exp_= (yyval.exp_); }
#line 1809 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 10:
#line 493 "Roller.y" /* yacc.c:1646  */
    {  (yyval.exp_) = new EPow((yyvsp[-2].exp_), (yyvsp[0].exp_)); YY_RESULT_Exp_= (yyval.exp_); }
#line 1815 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 11:
#line 494 "Roller.y" /* yacc.c:1646  */
    {  (yyval.exp_) = (yyvsp[0].exp_); YY_RESULT_Exp_= (yyval.exp_); }
#line 1821 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 12:
#line 495 "Roller.y" /* yacc.c:1646  */
    {  (yyval.exp_) = new EDice((yyvsp[0].expd_)); YY_RESULT_Exp_= (yyval.exp_); }
#line 1827 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 13:
#line 496 "Roller.y" /* yacc.c:1646  */
    {  std::reverse((yyvsp[-1].listpred_)->begin(),(yyvsp[-1].listpred_)->end()) ;(yyval.exp_) = new ESeqFilt((yyvsp[-3].exp_), (yyvsp[-1].listpred_)); YY_RESULT_Exp_= (yyval.exp_); }
#line 1833 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 14:
#line 498 "Roller.y" /* yacc.c:1646  */
    {  (yyval.exp_) = new ENeg((yyvsp[0].exp_)); YY_RESULT_Exp_= (yyval.exp_); }
#line 1839 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 15:
#line 499 "Roller.y" /* yacc.c:1646  */
    {  (yyval.exp_) = (yyvsp[-1].exp_); YY_RESULT_Exp_= (yyval.exp_); }
#line 1845 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 16:
#line 500 "Roller.y" /* yacc.c:1646  */
    {  (yyval.exp_) = new EVal((yyvsp[0].val_)); YY_RESULT_Exp_= (yyval.exp_); }
#line 1851 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 17:
#line 501 "Roller.y" /* yacc.c:1646  */
    {  std::reverse((yyvsp[-1].listexp_)->begin(),(yyvsp[-1].listexp_)->end()) ;(yyval.exp_) = new EList((yyvsp[-1].listexp_)); YY_RESULT_Exp_= (yyval.exp_); }
#line 1857 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 18:
#line 502 "Roller.y" /* yacc.c:1646  */
    {  (yyval.exp_) = new ERange((yyvsp[-1].range_)); YY_RESULT_Exp_= (yyval.exp_); }
#line 1863 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 19:
#line 503 "Roller.y" /* yacc.c:1646  */
    {  (yyval.exp_) = new EKeyW((yyvsp[0].expkw_)); YY_RESULT_Exp_= (yyval.exp_); }
#line 1869 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 20:
#line 504 "Roller.y" /* yacc.c:1646  */
    {  std::reverse((yyvsp[-1].listexp_)->begin(),(yyvsp[-1].listexp_)->end()) ;(yyval.exp_) = new ECall((yyvsp[-3].string_), (yyvsp[-1].listexp_)); YY_RESULT_Exp_= (yyval.exp_); }
#line 1875 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 21:
#line 506 "Roller.y" /* yacc.c:1646  */
    {  (yyval.exp_) = (yyvsp[0].exp_); YY_RESULT_Exp_= (yyval.exp_); }
#line 1881 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 22:
#line 508 "Roller.y" /* yacc.c:1646  */
    {  (yyval.listexp_) = new ListExp(); YY_RESULT_ListExp_= (yyval.listexp_); }
#line 1887 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 23:
#line 509 "Roller.y" /* yacc.c:1646  */
    {  (yyval.listexp_) = new ListExp() ; (yyval.listexp_)->push_back((yyvsp[0].exp_)); YY_RESULT_ListExp_= (yyval.listexp_); }
#line 1893 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 24:
#line 510 "Roller.y" /* yacc.c:1646  */
    {  (yyvsp[0].listexp_)->push_back((yyvsp[-2].exp_)) ; (yyval.listexp_) = (yyvsp[0].listexp_) ; YY_RESULT_ListExp_= (yyval.listexp_); }
#line 1899 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 25:
#line 512 "Roller.y" /* yacc.c:1646  */
    {  (yyval.numeral_) = new NumInt((yyvsp[0].int_)); YY_RESULT_Numeral_= (yyval.numeral_); }
#line 1905 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 26:
#line 513 "Roller.y" /* yacc.c:1646  */
    {  (yyval.numeral_) = new NumFloat((yyvsp[0].double_)); YY_RESULT_Numeral_= (yyval.numeral_); }
#line 1911 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 27:
#line 515 "Roller.y" /* yacc.c:1646  */
    {  (yyval.val_) = new ValNum((yyvsp[0].numeral_)); YY_RESULT_Val_= (yyval.val_); }
#line 1917 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 28:
#line 516 "Roller.y" /* yacc.c:1646  */
    {  (yyval.val_) = new ValVar((yyvsp[0].string_)); YY_RESULT_Val_= (yyval.val_); }
#line 1923 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 29:
#line 517 "Roller.y" /* yacc.c:1646  */
    {  (yyval.val_) = new ValStr((yyvsp[0].string_)); YY_RESULT_Val_= (yyval.val_); }
#line 1929 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 30:
#line 519 "Roller.y" /* yacc.c:1646  */
    {  (yyval.range_) = new RSimple((yyvsp[-2].exp_), (yyvsp[0].exp_)); YY_RESULT_Range_= (yyval.range_); }
#line 1935 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 31:
#line 520 "Roller.y" /* yacc.c:1646  */
    {  (yyval.range_) = new RStep((yyvsp[-4].exp_), (yyvsp[-2].exp_), (yyvsp[0].exp_)); YY_RESULT_Range_= (yyval.range_); }
#line 1941 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 32:
#line 521 "Roller.y" /* yacc.c:1646  */
    {  (yyval.range_) = new RInf((yyvsp[-1].exp_)); YY_RESULT_Range_= (yyval.range_); }
#line 1947 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 33:
#line 522 "Roller.y" /* yacc.c:1646  */
    {  (yyval.range_) = new RStepInf((yyvsp[-3].exp_), (yyvsp[-1].exp_)); YY_RESULT_Range_= (yyval.range_); }
#line 1953 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 34:
#line 524 "Roller.y" /* yacc.c:1646  */
    {  (yyval.expd_) = new E1d6(); YY_RESULT_ExpD_= (yyval.expd_); }
#line 1959 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 35:
#line 525 "Roller.y" /* yacc.c:1646  */
    {  (yyval.expd_) = new E1dN((yyvsp[0].exp_)); YY_RESULT_ExpD_= (yyval.expd_); }
#line 1965 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 36:
#line 526 "Roller.y" /* yacc.c:1646  */
    {  (yyval.expd_) = new ENd6((yyvsp[-1].exp_)); YY_RESULT_ExpD_= (yyval.expd_); }
#line 1971 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 37:
#line 527 "Roller.y" /* yacc.c:1646  */
    {  (yyval.expd_) = new ENdN((yyvsp[-2].exp_), (yyvsp[0].exp_)); YY_RESULT_ExpD_= (yyval.expd_); }
#line 1977 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 38:
#line 529 "Roller.y" /* yacc.c:1646  */
    {  (yyval.expkw_) = new EKWRepeat((yyvsp[-1].exp_), (yyvsp[0].exp_)); YY_RESULT_ExpKW_= (yyval.expkw_); }
#line 1983 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 39:
#line 530 "Roller.y" /* yacc.c:1646  */
    {  (yyval.expkw_) = new EKWCount((yyvsp[0].exp_)); YY_RESULT_ExpKW_= (yyval.expkw_); }
#line 1989 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 40:
#line 531 "Roller.y" /* yacc.c:1646  */
    {  (yyval.expkw_) = new EKWSum((yyvsp[0].exp_)); YY_RESULT_ExpKW_= (yyval.expkw_); }
#line 1995 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 41:
#line 532 "Roller.y" /* yacc.c:1646  */
    {  (yyval.expkw_) = new EKWMean((yyvsp[0].exp_)); YY_RESULT_ExpKW_= (yyval.expkw_); }
#line 2001 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 42:
#line 533 "Roller.y" /* yacc.c:1646  */
    {  (yyval.expkw_) = new EKWSqrt((yyvsp[0].exp_)); YY_RESULT_ExpKW_= (yyval.expkw_); }
#line 2007 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 43:
#line 534 "Roller.y" /* yacc.c:1646  */
    {  (yyval.expkw_) = new EKWFloor((yyvsp[0].exp_)); YY_RESULT_ExpKW_= (yyval.expkw_); }
#line 2013 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 44:
#line 535 "Roller.y" /* yacc.c:1646  */
    {  (yyval.expkw_) = new EKWCeil((yyvsp[0].exp_)); YY_RESULT_ExpKW_= (yyval.expkw_); }
#line 2019 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 45:
#line 536 "Roller.y" /* yacc.c:1646  */
    {  (yyval.expkw_) = new EKWRound((yyvsp[0].exp_)); YY_RESULT_ExpKW_= (yyval.expkw_); }
#line 2025 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 46:
#line 537 "Roller.y" /* yacc.c:1646  */
    {  (yyval.expkw_) = new EKWTrunc((yyvsp[0].exp_)); YY_RESULT_ExpKW_= (yyval.expkw_); }
#line 2031 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 47:
#line 538 "Roller.y" /* yacc.c:1646  */
    {  (yyval.expkw_) = new EKWAcc((yyvsp[-1].exp_), (yyvsp[0].string_)); YY_RESULT_ExpKW_= (yyval.expkw_); }
#line 2037 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 48:
#line 540 "Roller.y" /* yacc.c:1646  */
    {  (yyval.pred_) = (yyvsp[0].pred_); YY_RESULT_Pred_= (yyval.pred_); }
#line 2043 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 49:
#line 542 "Roller.y" /* yacc.c:1646  */
    {  (yyval.pred_) = (yyvsp[0].pred_); YY_RESULT_Pred_= (yyval.pred_); }
#line 2049 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 50:
#line 543 "Roller.y" /* yacc.c:1646  */
    {  (yyval.pred_) = new PredAnd((yyvsp[-2].pred_), (yyvsp[0].pred_)); YY_RESULT_Pred_= (yyval.pred_); }
#line 2055 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 51:
#line 544 "Roller.y" /* yacc.c:1646  */
    {  (yyval.pred_) = new PredOr((yyvsp[-2].pred_), (yyvsp[0].pred_)); YY_RESULT_Pred_= (yyval.pred_); }
#line 2061 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 52:
#line 545 "Roller.y" /* yacc.c:1646  */
    {  (yyval.pred_) = new PredXOr((yyvsp[-2].pred_), (yyvsp[0].pred_)); YY_RESULT_Pred_= (yyval.pred_); }
#line 2067 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 53:
#line 547 "Roller.y" /* yacc.c:1646  */
    {  (yyval.pred_) = (yyvsp[0].pred_); YY_RESULT_Pred_= (yyval.pred_); }
#line 2073 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 54:
#line 548 "Roller.y" /* yacc.c:1646  */
    {  (yyval.pred_) = new PredEQ((yyvsp[0].val_)); YY_RESULT_Pred_= (yyval.pred_); }
#line 2079 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 55:
#line 549 "Roller.y" /* yacc.c:1646  */
    {  (yyval.pred_) = new PredGT((yyvsp[0].val_)); YY_RESULT_Pred_= (yyval.pred_); }
#line 2085 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 56:
#line 550 "Roller.y" /* yacc.c:1646  */
    {  (yyval.pred_) = new PredLT((yyvsp[0].val_)); YY_RESULT_Pred_= (yyval.pred_); }
#line 2091 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 57:
#line 551 "Roller.y" /* yacc.c:1646  */
    {  (yyval.pred_) = new PredGTEq((yyvsp[0].val_)); YY_RESULT_Pred_= (yyval.pred_); }
#line 2097 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 58:
#line 552 "Roller.y" /* yacc.c:1646  */
    {  (yyval.pred_) = new PredLTEq((yyvsp[0].val_)); YY_RESULT_Pred_= (yyval.pred_); }
#line 2103 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 59:
#line 554 "Roller.y" /* yacc.c:1646  */
    {  (yyval.pred_) = (yyvsp[-1].pred_); YY_RESULT_Pred_= (yyval.pred_); }
#line 2109 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 60:
#line 555 "Roller.y" /* yacc.c:1646  */
    {  (yyval.pred_) = new PredNot((yyvsp[0].pred_)); YY_RESULT_Pred_= (yyval.pred_); }
#line 2115 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 61:
#line 556 "Roller.y" /* yacc.c:1646  */
    {  (yyval.pred_) = new PredIsStr(); YY_RESULT_Pred_= (yyval.pred_); }
#line 2121 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 62:
#line 557 "Roller.y" /* yacc.c:1646  */
    {  (yyval.pred_) = new PredIsInt(); YY_RESULT_Pred_= (yyval.pred_); }
#line 2127 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 63:
#line 558 "Roller.y" /* yacc.c:1646  */
    {  (yyval.pred_) = new PredIsFloat(); YY_RESULT_Pred_= (yyval.pred_); }
#line 2133 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 64:
#line 559 "Roller.y" /* yacc.c:1646  */
    {  (yyval.pred_) = new PredInd((yyvsp[0].exp_)); YY_RESULT_Pred_= (yyval.pred_); }
#line 2139 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 65:
#line 561 "Roller.y" /* yacc.c:1646  */
    {  (yyval.listpred_) = new ListPred(); YY_RESULT_ListPred_= (yyval.listpred_); }
#line 2145 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 66:
#line 562 "Roller.y" /* yacc.c:1646  */
    {  (yyval.listpred_) = new ListPred() ; (yyval.listpred_)->push_back((yyvsp[0].pred_)); YY_RESULT_ListPred_= (yyval.listpred_); }
#line 2151 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 67:
#line 563 "Roller.y" /* yacc.c:1646  */
    {  (yyvsp[0].listpred_)->push_back((yyvsp[-2].pred_)) ; (yyval.listpred_) = (yyvsp[0].listpred_) ; YY_RESULT_ListPred_= (yyval.listpred_); }
#line 2157 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 68:
#line 565 "Roller.y" /* yacc.c:1646  */
    {  (yyval.stmt_) = new SVarAs((yyvsp[-2].string_), (yyvsp[0].exp_)); YY_RESULT_Stmt_= (yyval.stmt_); }
#line 2163 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 69:
#line 566 "Roller.y" /* yacc.c:1646  */
    {  (yyval.stmt_) = new SVarAdd((yyvsp[-2].string_), (yyvsp[0].exp_)); YY_RESULT_Stmt_= (yyval.stmt_); }
#line 2169 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 70:
#line 567 "Roller.y" /* yacc.c:1646  */
    {  (yyval.stmt_) = new SVarSub((yyvsp[-2].string_), (yyvsp[0].exp_)); YY_RESULT_Stmt_= (yyval.stmt_); }
#line 2175 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 71:
#line 568 "Roller.y" /* yacc.c:1646  */
    {  (yyval.stmt_) = new SVarMul((yyvsp[-2].string_), (yyvsp[0].exp_)); YY_RESULT_Stmt_= (yyval.stmt_); }
#line 2181 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 72:
#line 569 "Roller.y" /* yacc.c:1646  */
    {  (yyval.stmt_) = new SVarDiv((yyvsp[-2].string_), (yyvsp[0].exp_)); YY_RESULT_Stmt_= (yyval.stmt_); }
#line 2187 "Parser.CPP" /* yacc.c:1646  */
    break;

  case 73:
#line 570 "Roller.y" /* yacc.c:1646  */
    {  std::reverse((yyvsp[-3].listexp_)->begin(),(yyvsp[-3].listexp_)->end()) ;(yyval.stmt_) = new SFunDef((yyvsp[-5].string_), (yyvsp[-3].listexp_), (yyvsp[0].exp_)); YY_RESULT_Stmt_= (yyval.stmt_); }
#line 2193 "Parser.CPP" /* yacc.c:1646  */
    break;


#line 2197 "Parser.CPP" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
