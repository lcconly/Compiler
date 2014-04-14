/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "syntax.y"

#include<stdio.h>
#include"lex.yy.c"
#include"include/Node.h"
#define YYDEBUG 1


/* Line 268 of yacc.c  */
#line 79 "syntax.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     FLOAT = 259,
     ID = 260,
     SEMI = 261,
     COMMA = 262,
     ASSIGNOP = 263,
     RELOP = 264,
     PLUS = 265,
     MINUS = 266,
     STAR = 267,
     DIV = 268,
     AND = 269,
     OR = 270,
     DOT = 271,
     NOT = 272,
     TYPE = 273,
     LP = 274,
     RP = 275,
     LB = 276,
     RB = 277,
     LC = 278,
     RC = 279,
     STRUCT = 280,
     RETURN = 281,
     IF = 282,
     ELSE = 283,
     WHILE = 284,
     LOWER_THAN_ELSE = 285,
     LOWER_THAN_ERROR = 286,
     UNARY = 287
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 9 "syntax.y"

	struct TreeNode *Node;		



/* Line 293 of yacc.c  */
#line 153 "syntax.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 178 "syntax.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   300

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNRULES -- Number of states.  */
#define YYNSTATES  125

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   287

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    13,    16,    20,    23,
      25,    29,    31,    33,    39,    42,    44,    45,    47,    49,
      54,    59,    63,    66,    70,    72,    75,    80,    83,    86,
      87,    90,    92,    96,   102,   110,   116,   119,   122,   123,
     127,   130,   132,   136,   138,   142,   146,   150,   154,   158,
     162,   166,   170,   174,   178,   181,   184,   189,   193,   198,
     202,   204,   206,   208,   212,   217,   221
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      34,     0,    -1,    35,    -1,    36,    35,    -1,    -1,    38,
      37,     6,    -1,    38,     6,    -1,    38,    43,    46,    -1,
       1,     6,    -1,    42,    -1,    42,     7,    37,    -1,    18,
      -1,    39,    -1,    25,    40,    23,    49,    24,    -1,    25,
      41,    -1,     5,    -1,    -1,     5,    -1,     5,    -1,    42,
      21,     3,    22,    -1,     5,    19,    44,    20,    -1,     5,
      19,    20,    -1,     1,    20,    -1,    45,     7,    44,    -1,
      45,    -1,    38,    42,    -1,    23,    49,    47,    24,    -1,
       1,    24,    -1,    48,    47,    -1,    -1,    53,     6,    -1,
      46,    -1,    26,    53,     6,    -1,    27,    19,    53,    20,
      48,    -1,    27,    19,    53,    20,    48,    28,    48,    -1,
      29,    19,    53,    20,    48,    -1,     1,     6,    -1,    50,
      49,    -1,    -1,    38,    51,     6,    -1,     1,     6,    -1,
      52,    -1,    52,     7,    51,    -1,    42,    -1,    42,     8,
      53,    -1,    53,     8,    53,    -1,    53,    14,    53,    -1,
      53,    15,    53,    -1,    53,     9,    53,    -1,    53,    10,
      53,    -1,    53,    11,    53,    -1,    53,    12,    53,    -1,
      53,    13,    53,    -1,    19,    53,    20,    -1,    11,    53,
      -1,    17,    53,    -1,     5,    19,    54,    20,    -1,     5,
      19,    20,    -1,    53,    21,    53,    22,    -1,    53,    16,
       5,    -1,     5,    -1,     3,    -1,     4,    -1,    19,     1,
      20,    -1,    53,    21,     1,    22,    -1,    53,     7,    54,
      -1,    53,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    55,    55,    61,    66,    70,    76,    81,    87,    91,
      95,   102,   106,   111,   120,   126,   130,   134,   139,   143,
     151,   158,   164,   168,   174,   179,   185,   192,   196,   201,
     205,   210,   214,   220,   228,   238,   246,   250,   255,   259,
     265,   269,   273,   280,   284,   291,   297,   303,   309,   315,
     321,   327,   333,   339,   345,   350,   355,   362,   368,   375,
     381,   385,   389,   393,   396,   400,   406
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "ID", "SEMI", "COMMA",
  "ASSIGNOP", "RELOP", "PLUS", "MINUS", "STAR", "DIV", "AND", "OR", "DOT",
  "NOT", "TYPE", "LP", "RP", "LB", "RB", "LC", "RC", "STRUCT", "RETURN",
  "IF", "ELSE", "WHILE", "LOWER_THAN_ELSE", "LOWER_THAN_ERROR", "UNARY",
  "$accept", "Program", "ExtDefList", "ExDef", "ExtDecList", "Specifier",
  "StructSpecifier", "OptTag", "Tag", "VarDec", "FunDec", "VarList",
  "ParamDec", "CompSt", "StmTList", "Stmt", "DefList", "Def", "DecList",
  "Dec", "Exp", "Args", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    33,    34,    35,    35,    36,    36,    36,    36,    37,
      37,    38,    38,    39,    39,    40,    40,    41,    42,    42,
      43,    43,    43,    44,    44,    45,    46,    46,    47,    47,
      48,    48,    48,    48,    48,    48,    48,    49,    49,    50,
      50,    51,    51,    52,    52,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    54,    54
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     2,     1,
       3,     1,     1,     5,     2,     1,     0,     1,     1,     4,
       4,     3,     2,     3,     1,     2,     4,     2,     2,     0,
       2,     1,     3,     5,     7,     5,     2,     2,     0,     3,
       2,     1,     3,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     4,     3,     4,     3,
       1,     1,     1,     3,     4,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    11,    16,     0,     2,     0,     0,    12,     8,
      17,     0,    14,     1,     3,     0,    18,     6,     0,     9,
       0,     0,    22,     0,     5,     0,     0,     0,     0,     7,
       0,     0,     0,     0,    21,     0,     0,    24,    18,    10,
       0,    27,     0,    40,    43,     0,    41,    13,    37,    25,
      20,     0,    19,     0,    61,    62,    60,     0,     0,     0,
       0,     0,     0,    31,     0,     0,     0,     0,    39,     0,
      23,    36,     0,    54,    55,     0,     0,     0,     0,     0,
      26,    28,    30,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    44,    42,    57,    66,     0,    63,    53,
      32,     0,     0,    45,    48,    49,    50,    51,    52,    46,
      47,    59,     0,     0,     0,    56,     0,     0,    64,    58,
      65,    33,    35,     0,    34
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    18,    31,     8,    11,    12,    19,
      20,    36,    37,    63,    64,    65,    32,    33,    45,    46,
      66,    97
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -111
static const yytype_int16 yypact[] =
{
      19,    12,  -111,    34,    40,  -111,    19,   141,  -111,  -111,
      18,    29,  -111,  -111,  -111,    38,    44,  -111,    58,    17,
      13,    76,  -111,    30,  -111,    70,    73,    65,    42,  -111,
      84,    70,    78,    42,  -111,    70,    85,    97,  -111,  -111,
      92,  -111,    69,  -111,     4,   119,   115,  -111,  -111,   109,
    -111,    -9,  -111,    -1,  -111,  -111,   113,   134,   134,   107,
     134,   121,   122,  -111,   104,    69,   146,   134,  -111,    70,
    -111,  -111,   116,    33,    33,   114,   204,   160,   134,   134,
    -111,  -111,  -111,   134,   134,   134,   134,   134,   134,   134,
     134,   138,   112,   246,  -111,  -111,   175,   124,  -111,  -111,
    -111,   218,   232,   246,   279,    66,    66,    33,    33,   272,
     259,  -111,   126,   189,   134,  -111,    80,    80,  -111,  -111,
    -111,   135,  -111,    80,  -111
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -111,  -111,   143,  -111,   125,    11,  -111,  -111,  -111,   -27,
    -111,   127,  -111,   144,   100,  -110,    23,  -111,   108,  -111,
     -57,    79
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -39
static const yytype_int8 yytable[] =
{
      73,    74,    76,    77,    44,    71,   121,   122,    49,     2,
      93,     7,    67,   124,    27,    96,     3,     7,     9,    -4,
       1,   101,   102,    41,    25,    26,   103,   104,   105,   106,
     107,   108,   109,   110,    35,   113,    28,     2,    26,    10,
      13,   -15,    44,    30,     3,   -38,   -38,   -38,     2,    91,
      34,    42,    21,   -38,    92,     3,    48,    96,    22,   -38,
       2,   -38,    35,    23,    24,   -38,   -38,     3,   -38,   -38,
      53,   -38,    54,    55,    56,    38,    40,    30,    87,    88,
      57,    53,    91,    54,    55,    56,    58,    92,    59,    41,
      43,    57,    28,   -29,     2,    60,    61,    58,    62,    59,
     -38,     3,    47,    28,    51,    50,    60,    61,    75,    62,
      54,    55,    56,   112,    52,    54,    55,    56,    57,    54,
      55,    56,    69,    57,    58,    68,    59,    57,    80,    58,
      26,    59,    72,    58,    98,    59,    95,    54,    55,    56,
      78,    79,    15,   111,   115,    57,    16,    17,   118,    14,
      39,    58,    82,    59,    83,    84,    85,    86,    87,    88,
      89,    90,    91,   123,    29,    81,   100,    92,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    94,    70,     0,
       0,    92,   114,    83,    84,    85,    86,    87,    88,    89,
      90,    91,     0,   120,     0,     0,    92,    83,    84,    85,
      86,    87,    88,    89,    90,    91,     0,     0,     0,     0,
      92,   119,    83,    84,    85,    86,    87,    88,    89,    90,
      91,     0,     0,     0,    99,    92,    83,    84,    85,    86,
      87,    88,    89,    90,    91,     0,     0,     0,   116,    92,
      83,    84,    85,    86,    87,    88,    89,    90,    91,     0,
       0,     0,   117,    92,    83,    84,    85,    86,    87,    88,
      89,    90,    91,     0,     0,     0,     0,    92,    84,    85,
      86,    87,    88,    89,     0,    91,     0,     0,     0,     0,
      92,    84,    85,    86,    87,    88,     0,     0,    91,    85,
      86,    87,    88,    92,     0,    91,     0,     0,     0,     0,
      92
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-111))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      57,    58,    59,    60,    31,     6,   116,   117,    35,    18,
      67,     0,     8,   123,     1,    72,    25,     6,     6,     0,
       1,    78,    79,    24,     7,    21,    83,    84,    85,    86,
      87,    88,    89,    90,    23,    92,    23,    18,    21,     5,
       0,    23,    69,     1,    25,     3,     4,     5,    18,    16,
      20,    28,    23,    11,    21,    25,    33,   114,    20,    17,
      18,    19,    51,    19,     6,    23,    24,    25,    26,    27,
       1,    29,     3,     4,     5,     5,     3,     1,    12,    13,
      11,     1,    16,     3,     4,     5,    17,    21,    19,    24,
       6,    11,    23,    24,    18,    26,    27,    17,    29,    19,
      24,    25,    24,    23,     7,    20,    26,    27,     1,    29,
       3,     4,     5,     1,    22,     3,     4,     5,    11,     3,
       4,     5,     7,    11,    17,     6,    19,    11,    24,    17,
      21,    19,    19,    17,    20,    19,    20,     3,     4,     5,
      19,    19,     1,     5,    20,    11,     5,     6,    22,     6,
      25,    17,     6,    19,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    28,    20,    65,     6,    21,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    69,    51,    -1,
      -1,    21,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    -1,   114,    -1,    -1,    21,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    -1,    -1,    -1,    -1,
      21,    22,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    20,    21,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    -1,    -1,    -1,    20,    21,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    -1,    20,    21,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    -1,    21,     9,    10,
      11,    12,    13,    14,    -1,    16,    -1,    -1,    -1,    -1,
      21,     9,    10,    11,    12,    13,    -1,    -1,    16,    10,
      11,    12,    13,    21,    -1,    16,    -1,    -1,    -1,    -1,
      21
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    18,    25,    34,    35,    36,    38,    39,     6,
       5,    40,    41,     0,    35,     1,     5,     6,    37,    42,
      43,    23,    20,    19,     6,     7,    21,     1,    23,    46,
       1,    38,    49,    50,    20,    38,    44,    45,     5,    37,
       3,    24,    49,     6,    42,    51,    52,    24,    49,    42,
      20,     7,    22,     1,     3,     4,     5,    11,    17,    19,
      26,    27,    29,    46,    47,    48,    53,     8,     6,     7,
      44,     6,    19,    53,    53,     1,    53,    53,    19,    19,
      24,    47,     6,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    21,    53,    51,    20,    53,    54,    20,    20,
       6,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,     5,     1,    53,     7,    20,    20,    20,    22,    22,
      54,    48,    48,    28,    48
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

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
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
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
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = YYLEX;
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
  *++yyvsp = yylval;
  *++yylsp = yylloc;
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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 55 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Program","",(yylsp[(1) - (1)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (1)].Node));
													root=(yyval.Node);
                                                }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 61 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"ExtDefList","",(yylsp[(1) - (2)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (2)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (2)].Node));
                                                }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 66 "syntax.y"
    {
                                                    (yyval.Node)=NULL;
                                                }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 70 "syntax.y"
    {
													CreateNode(&(yyval.Node),"ExDef","",(yylsp[(1) - (3)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (3)].Node));
                                                }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 76 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"ExDef","",(yylsp[(1) - (2)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (2)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (2)].Node));
                                                }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 81 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"ExDef","",(yylsp[(1) - (3)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (3)].Node));
                                                }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 87 "syntax.y"
    {
                                                    //CreateNode("ERROR",0,0);
                                                }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 91 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"ExtDecList","",(yylsp[(1) - (1)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (1)].Node));    
                                                }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 95 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"ExtDecList","",(yylsp[(1) - (3)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (3)].Node));
                                                }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 102 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Specifier","",(yylsp[(1) - (1)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (1)].Node));
                                                }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 106 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Specifier","",(yylsp[(1) - (1)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (1)].Node));
                                                }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 111 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"StructSpecifier","",(yylsp[(1) - (5)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (5)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (5)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (5)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(4) - (5)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(5) - (5)].Node));

                                                }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 120 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"StructSpecifier","",(yylsp[(1) - (2)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (2)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (2)].Node));
                                                }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 126 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"OptTag","",(yylsp[(1) - (1)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (1)].Node));
                                                }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 130 "syntax.y"
    {
                                                    (yyval.Node)=NULL;    
                                                }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 134 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Tag","",(yylsp[(1) - (1)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (1)].Node));
                                                }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 139 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"VarDec","",(yylsp[(1) - (1)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (1)].Node));
                                                }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 143 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"VarDec","",(yylsp[(1) - (4)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (4)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (4)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (4)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(4) - (4)].Node));
                                                }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 151 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"FunDec","",(yylsp[(1) - (4)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (4)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (4)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (4)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(4) - (4)].Node));
                                                }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 158 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"FunDec","",(yylsp[(1) - (3)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (3)].Node));
                                                }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 164 "syntax.y"
    {
                                                    //CreateNode("ERROR",0,0);			
                                                }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 168 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"VarList","",(yylsp[(1) - (3)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (3)].Node));
                                                }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 174 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"VarList","",(yylsp[(1) - (1)]).first_line);   
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (1)].Node));
                                                }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 179 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"ParamDec","",(yylsp[(1) - (2)]).first_line);   
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (2)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (2)].Node));
                                                }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 185 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"CompSt","",(yylsp[(1) - (4)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (4)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (4)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (4)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(4) - (4)].Node));
                                                }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 192 "syntax.y"
    {
                                                    //CreateNode("ERROR",0,0);
                                                }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 196 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"StmTList","",(yylsp[(1) - (2)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (2)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (2)].Node));
                                                }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 201 "syntax.y"
    {
                                                    (yyval.Node)=NULL;
                                                }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 205 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Stmt","",(yylsp[(1) - (2)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (2)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (2)].Node));
                                                }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 210 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Stmt","",(yylsp[(1) - (1)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (1)].Node));
                                                }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 214 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Stmt","",(yylsp[(1) - (3)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (3)].Node));
                                                }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 220 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Stmt","",(yylsp[(1) - (5)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (5)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (5)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (5)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(4) - (5)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(5) - (5)].Node));
                                                }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 228 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Stmt","",(yylsp[(1) - (7)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (7)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (7)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (7)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(4) - (7)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(5) - (7)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(6) - (7)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(7) - (7)].Node));
                                                }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 238 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Stmt","",(yylsp[(1) - (5)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (5)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (5)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (5)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(4) - (5)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(5) - (5)].Node));
                                                }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 246 "syntax.y"
    {
                                                    //CreateNode("ERROR",0,0);
                                                }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 250 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"DecList","",(yylsp[(1) - (2)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (2)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (2)].Node));
                                                }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 255 "syntax.y"
    {
                                                    (yyval.Node)=NULL;
                                                }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 259 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Def","",(yylsp[(1) - (3)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (3)].Node));
                                                }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 265 "syntax.y"
    {
                                                    //CreateNode("ERROR",0,0);
                                                }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 269 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"DecList","",(yylsp[(1) - (1)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (1)].Node));
                                                }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 273 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"DecList","",(yylsp[(1) - (3)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (3)].Node));
                                                }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 280 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Dec","",(yylsp[(1) - (1)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (1)].Node));
                                                }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 284 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Dec","",(yylsp[(1) - (3)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (3)].Node));
                                                }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 291 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Exp","",(yylsp[(1) - (3)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (3)].Node));
                                                }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 297 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Exp","",(yylsp[(1) - (3)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (3)].Node));
                                                }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 303 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Exp","",(yylsp[(1) - (3)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (3)].Node));
                                                }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 309 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Exp","",(yylsp[(1) - (3)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (3)].Node));
                                                }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 315 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Exp","",(yylsp[(1) - (3)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (3)].Node));
                                                }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 321 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Exp","",(yylsp[(1) - (3)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (3)].Node));
                                                }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 327 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Exp","",(yylsp[(1) - (3)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (3)].Node));
                                                }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 333 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Exp","",(yylsp[(1) - (3)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (3)].Node));
                                                }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 339 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Exp","",(yylsp[(1) - (3)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (3)].Node));
                                                }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 345 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Exp","",(yylsp[(1) - (2)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (2)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (2)].Node));
                                                }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 350 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Exp","",(yylsp[(1) - (2)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (2)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (2)].Node));
                                                }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 355 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Exp","",(yylsp[(1) - (4)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (4)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (4)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (4)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(4) - (4)].Node));
                                                }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 362 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Exp","",(yylsp[(1) - (3)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (3)].Node));
                                                }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 368 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Exp","",(yylsp[(1) - (4)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (4)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (4)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (4)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(4) - (4)].Node));
                                                }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 375 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Exp","",(yylsp[(1) - (3)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (3)].Node));
                                                }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 381 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Exp","",(yylsp[(1) - (1)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (1)].Node));
                                                }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 385 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Exp","",(yylsp[(1) - (1)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (1)].Node));
                                                }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 389 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Exp","",(yylsp[(1) - (1)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (1)].Node));
                                                }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 393 "syntax.y"
    {
                                                    //CreateNode("ERROR",0,0);
                                                }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 396 "syntax.y"
    {
                                                    //CreateNode("ERROR",0,0);
                                                }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 400 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Args","",(yylsp[(1) - (3)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(2) - (3)].Node));
													addNodeToParent(&(yyval.Node),(yyvsp[(3) - (3)].Node));
                                                }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 406 "syntax.y"
    {
                                                    CreateNode(&(yyval.Node),"Args","",(yylsp[(1) - (1)]).first_line);
													addNodeToParent(&(yyval.Node),(yyvsp[(1) - (1)].Node));
                                                }
    break;



/* Line 1806 of yacc.c  */
#line 2316 "syntax.tab.c"
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
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

  yyerror_range[1] = yylloc;

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
		      yytoken, &yylval, &yylloc);
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

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 411 "syntax.y"

yyerror(char* msg){
    hasError=1;
    fprintf(stderr,"Error type B at line %d : %s\n",yylineno,msg);
}



