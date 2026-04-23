/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

/*
 * parser.y -- WS Language v3.0
 * LALR(1) grammar with AST generation.
 * Variable syntax: name type => value;
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbols.h"
#include "parser_helper.h"
#include "ast.h"
#include "interpreter.h"

int  yylex(void);
void yyerror(const char* s);

extern FILE* yyin;
extern int   yylineno;

ASTNode* root_ast = NULL;
InterpreterContext* interp = NULL;

#line 95 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PRINT = 3,                      /* PRINT  */
  YYSYMBOL_FUNCTION = 4,                   /* FUNCTION  */
  YYSYMBOL_RETURN = 5,                     /* RETURN  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_WHILE = 8,                      /* WHILE  */
  YYSYMBOL_INT_TYPE = 9,                   /* INT_TYPE  */
  YYSYMBOL_CHAR_TYPE = 10,                 /* CHAR_TYPE  */
  YYSYMBOL_DOUBLE_TYPE = 11,               /* DOUBLE_TYPE  */
  YYSYMBOL_BOOL_TYPE = 12,                 /* BOOL_TYPE  */
  YYSYMBOL_STRING_TYPE = 13,               /* STRING_TYPE  */
  YYSYMBOL_ARROW = 14,                     /* ARROW  */
  YYSYMBOL_SEMICOLON = 15,                 /* SEMICOLON  */
  YYSYMBOL_LPARENT = 16,                   /* LPARENT  */
  YYSYMBOL_RPARENT = 17,                   /* RPARENT  */
  YYSYMBOL_LBRACE = 18,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 19,                    /* RBRACE  */
  YYSYMBOL_COMMA = 20,                     /* COMMA  */
  YYSYMBOL_EQUALS = 21,                    /* EQUALS  */
  YYSYMBOL_PLUS = 22,                      /* PLUS  */
  YYSYMBOL_SUB = 23,                       /* SUB  */
  YYSYMBOL_MUL = 24,                       /* MUL  */
  YYSYMBOL_DIV = 25,                       /* DIV  */
  YYSYMBOL_EQ = 26,                        /* EQ  */
  YYSYMBOL_NE = 27,                        /* NE  */
  YYSYMBOL_LT = 28,                        /* LT  */
  YYSYMBOL_LE = 29,                        /* LE  */
  YYSYMBOL_GT = 30,                        /* GT  */
  YYSYMBOL_GE = 31,                        /* GE  */
  YYSYMBOL_AND = 32,                       /* AND  */
  YYSYMBOL_OR = 33,                        /* OR  */
  YYSYMBOL_NOT = 34,                       /* NOT  */
  YYSYMBOL_IDENTIFIER = 35,                /* IDENTIFIER  */
  YYSYMBOL_NUMBER = 36,                    /* NUMBER  */
  YYSYMBOL_DOUBLE_LITERAL = 37,            /* DOUBLE_LITERAL  */
  YYSYMBOL_CHAR_LITERAL = 38,              /* CHAR_LITERAL  */
  YYSYMBOL_BOOL_LITERAL = 39,              /* BOOL_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 40,            /* STRING_LITERAL  */
  YYSYMBOL_YYACCEPT = 41,                  /* $accept  */
  YYSYMBOL_program = 42,                   /* program  */
  YYSYMBOL_statements = 43,                /* statements  */
  YYSYMBOL_statement = 44,                 /* statement  */
  YYSYMBOL_block = 45,                     /* block  */
  YYSYMBOL_data_type = 46,                 /* data_type  */
  YYSYMBOL_var_declaration = 47,           /* var_declaration  */
  YYSYMBOL_var_assignment = 48,            /* var_assignment  */
  YYSYMBOL_print_statement = 49,           /* print_statement  */
  YYSYMBOL_function_declaration = 50,      /* function_declaration  */
  YYSYMBOL_parameter_list = 51,            /* parameter_list  */
  YYSYMBOL_if_statement = 52,              /* if_statement  */
  YYSYMBOL_while_statement = 53,           /* while_statement  */
  YYSYMBOL_function_call = 54,             /* function_call  */
  YYSYMBOL_argument_list = 55,             /* argument_list  */
  YYSYMBOL_expression = 56                 /* expression  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  45
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   274

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  118

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   295


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    75,    75,    86,    96,   105,   113,   114,   115,   116,
     117,   118,   119,   120,   123,   127,   139,   140,   141,   142,
     143,   147,   151,   156,   161,   169,   173,   181,   185,   189,
     195,   206,   217,   224,   235,   238,   245,   251,   262,   268,
     275,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PRINT", "FUNCTION",
  "RETURN", "IF", "ELSE", "WHILE", "INT_TYPE", "CHAR_TYPE", "DOUBLE_TYPE",
  "BOOL_TYPE", "STRING_TYPE", "ARROW", "SEMICOLON", "LPARENT", "RPARENT",
  "LBRACE", "RBRACE", "COMMA", "EQUALS", "PLUS", "SUB", "MUL", "DIV", "EQ",
  "NE", "LT", "LE", "GT", "GE", "AND", "OR", "NOT", "IDENTIFIER", "NUMBER",
  "DOUBLE_LITERAL", "CHAR_LITERAL", "BOOL_LITERAL", "STRING_LITERAL",
  "$accept", "program", "statements", "statement", "block", "data_type",
  "var_declaration", "var_assignment", "print_statement",
  "function_declaration", "parameter_list", "if_statement",
  "while_statement", "function_call", "argument_list", "expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-86)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-29)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      87,    90,   -27,    98,    -6,    53,    87,    66,    15,    87,
     -86,   -86,    56,    57,    58,   -86,   -86,   -86,    74,    98,
      98,    98,    34,   -86,   -86,   -86,   -86,    81,   -86,   220,
      84,    85,   -86,   157,    98,    98,     8,   -86,   -86,   -86,
     -86,   -86,    98,   123,     9,   -86,   -86,   -86,   -86,   -86,
     -86,   174,   -86,   -86,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,   -10,   -86,   191,   208,
     -86,    18,   220,    95,   220,   131,   -86,    27,    27,   -86,
     -86,   120,   120,     7,     7,     7,     7,   243,   232,    35,
      35,    20,    99,    99,   -86,    98,   103,   104,   105,   220,
     113,   -86,    35,    67,   116,   -86,   220,    87,   122,    35,
      99,    62,    87,   -86,   -86,   -86,    80,   -86
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,     0,     0,     0,     0,     0,     5,     0,     0,     2,
       3,    12,     0,     0,     0,     9,    10,    11,     0,     0,
       0,     0,    46,    41,    42,    43,    44,    45,    62,    29,
       0,    46,    45,     0,     0,     0,     0,    16,    18,    17,
      20,    19,    40,     0,     0,     1,     4,     6,     7,     8,
      14,     0,    60,    59,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    13,     0,     0,
      15,     0,    38,    45,    25,     0,    61,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,     0,
       0,     0,     0,     0,    37,     0,    43,    44,    45,    21,
       0,    32,     0,     0,    34,    36,    39,     5,     0,     0,
       0,     0,     5,    33,    35,    31,     0,    30
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -86,   -86,    -3,    -8,   -71,   -85,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,     0,   -86,    -1
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     8,     9,    10,    11,    44,    12,    13,    14,    15,
      91,    16,    17,    28,    71,    29
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      18,    46,    33,    36,   100,   101,    18,    89,    30,    18,
      34,     1,     2,     3,     4,    45,     5,   108,    51,    52,
      53,   104,   105,    75,   113,    90,     6,    70,    46,    54,
      55,    56,    57,    68,    69,    94,    18,   102,    95,   114,
     103,    72,    74,     7,    37,    38,    39,    40,    41,   -27,
      42,    56,    57,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,     1,     2,     3,     4,    35,
       5,    47,    48,    49,    99,    37,    38,    39,    40,    41,
       6,   115,    42,     1,     2,     3,     4,    43,     5,    50,
       1,     2,     3,     4,   106,     5,   -28,     7,     6,   117,
      66,    42,   109,    46,   111,     6,    19,    18,    46,   116,
     -26,    18,    18,    20,    19,     7,    18,     6,   -23,   -24,
     -22,    20,     7,   110,    21,    22,    23,    24,    25,    26,
      27,   107,    21,    31,    23,    24,    25,    26,    32,    19,
     112,     0,    54,    55,    56,    57,    20,    19,    60,    61,
      62,    63,     0,     0,    20,     0,     0,    21,    31,    23,
      24,    25,    26,    73,     0,    21,    31,    23,    24,    96,
      97,    98,    67,     0,     0,     0,     0,     0,     0,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    76,     0,     0,     0,     0,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    92,     0,
       0,     0,     0,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    93,     0,     0,     0,     0,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63
};

static const yytype_int8 yycheck[] =
{
       0,     9,     3,     6,    89,    90,     6,    17,    35,     9,
      16,     3,     4,     5,     6,     0,     8,   102,    19,    20,
      21,    92,    93,    14,   109,    35,    18,    19,    36,    22,
      23,    24,    25,    34,    35,    17,    36,    17,    20,   110,
      20,    42,    43,    35,     9,    10,    11,    12,    13,    15,
      16,    24,    25,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,     3,     4,     5,     6,    16,
       8,    15,    15,    15,    75,     9,    10,    11,    12,    13,
      18,    19,    16,     3,     4,     5,     6,    21,     8,    15,
       3,     4,     5,     6,    95,     8,    15,    35,    18,    19,
      16,    16,    35,   111,   107,    18,    16,   107,   116,   112,
      15,   111,   112,    23,    16,    35,   116,    18,    15,    15,
      15,    23,    35,     7,    34,    35,    36,    37,    38,    39,
      40,    18,    34,    35,    36,    37,    38,    39,    40,    16,
      18,    -1,    22,    23,    24,    25,    23,    16,    28,    29,
      30,    31,    -1,    -1,    23,    -1,    -1,    34,    35,    36,
      37,    38,    39,    40,    -1,    34,    35,    36,    37,    38,
      39,    40,    15,    -1,    -1,    -1,    -1,    -1,    -1,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    17,    -1,    -1,    -1,    -1,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    17,    -1,
      -1,    -1,    -1,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    17,    -1,    -1,    -1,    -1,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     8,    18,    35,    42,    43,
      44,    45,    47,    48,    49,    50,    52,    53,    54,    16,
      23,    34,    35,    36,    37,    38,    39,    40,    54,    56,
      35,    35,    40,    56,    16,    16,    43,     9,    10,    11,
      12,    13,    16,    21,    46,     0,    44,    15,    15,    15,
      15,    56,    56,    56,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    16,    15,    56,    56,
      19,    55,    56,    40,    56,    14,    17,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    17,
      35,    51,    17,    17,    17,    20,    38,    39,    40,    56,
      46,    46,    17,    20,    45,    45,    56,    18,    46,    35,
       7,    43,    18,    46,    45,    19,    43,    19
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    43,    43,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    45,    46,    46,    46,    46,
      46,    47,    47,    47,    47,    48,    48,    49,    49,    49,
      50,    50,    51,    51,    52,    52,    53,    54,    55,    55,
      55,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     0,     2,     2,     2,     1,
       1,     1,     1,     3,     2,     3,     1,     1,     1,     1,
       1,     4,     4,     4,     4,     3,     3,     2,     2,     2,
       9,     8,     2,     4,     5,     7,     5,     4,     1,     3,
       0,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* program: statements  */
#line 75 "parser.y"
                 {
        if ((yyvsp[0].ast_array) != NULL) {
            /* Count statements in the array */
            int count = 0;
            while ((yyvsp[0].ast_array)[count] != NULL) count++;
            root_ast = ast_create_program((yyvsp[0].ast_array), count);
        }
    }
#line 1250 "parser.tab.c"
    break;

  case 3: /* statements: statement  */
#line 86 "parser.y"
                {
        ASTNode** arr = (ASTNode**) malloc(sizeof(ASTNode*) * 100);
        if ((yyvsp[0].ast_node) != NULL) {
            arr[0] = (yyvsp[0].ast_node);
            arr[1] = NULL;
        } else {
            arr[0] = NULL;
        }
        (yyval.ast_array) = arr;
    }
#line 1265 "parser.tab.c"
    break;

  case 4: /* statements: statements statement  */
#line 96 "parser.y"
                           {
        if ((yyvsp[0].ast_node) != NULL) {
            int i = 0;
            while ((yyvsp[-1].ast_array)[i] != NULL) i++;
            (yyvsp[-1].ast_array)[i] = (yyvsp[0].ast_node);
            (yyvsp[-1].ast_array)[i + 1] = NULL;
        }
        (yyval.ast_array) = (yyvsp[-1].ast_array);
    }
#line 1279 "parser.tab.c"
    break;

  case 5: /* statements: %empty  */
#line 105 "parser.y"
                  {
        ASTNode** arr = (ASTNode**) malloc(sizeof(ASTNode*) * 100);
        arr[0] = NULL;
        (yyval.ast_array) = arr;
    }
#line 1289 "parser.tab.c"
    break;

  case 6: /* statement: var_declaration SEMICOLON  */
#line 113 "parser.y"
                                { (yyval.ast_node) = (yyvsp[-1].ast_node); }
#line 1295 "parser.tab.c"
    break;

  case 7: /* statement: var_assignment SEMICOLON  */
#line 114 "parser.y"
                               { (yyval.ast_node) = (yyvsp[-1].ast_node); }
#line 1301 "parser.tab.c"
    break;

  case 8: /* statement: print_statement SEMICOLON  */
#line 115 "parser.y"
                                { (yyval.ast_node) = (yyvsp[-1].ast_node); }
#line 1307 "parser.tab.c"
    break;

  case 9: /* statement: function_declaration  */
#line 116 "parser.y"
                           { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1313 "parser.tab.c"
    break;

  case 10: /* statement: if_statement  */
#line 117 "parser.y"
                   { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1319 "parser.tab.c"
    break;

  case 11: /* statement: while_statement  */
#line 118 "parser.y"
                      { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1325 "parser.tab.c"
    break;

  case 12: /* statement: block  */
#line 119 "parser.y"
            { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1331 "parser.tab.c"
    break;

  case 13: /* statement: RETURN expression SEMICOLON  */
#line 120 "parser.y"
                                  {
        (yyval.ast_node) = ast_create_return((yyvsp[-1].ast_node), yylineno);
    }
#line 1339 "parser.tab.c"
    break;

  case 14: /* statement: function_call SEMICOLON  */
#line 123 "parser.y"
                              { (yyval.ast_node) = (yyvsp[-1].ast_node); }
#line 1345 "parser.tab.c"
    break;

  case 15: /* block: LBRACE statements RBRACE  */
#line 127 "parser.y"
                               {
        if ((yyvsp[-1].ast_array) != NULL) {
            int count = 0;
            while ((yyvsp[-1].ast_array)[count] != NULL) count++;
            (yyval.ast_node) = ast_create_block((yyvsp[-1].ast_array), count);
        } else {
            (yyval.ast_node) = ast_create_block(NULL, 0);
        }
    }
#line 1359 "parser.tab.c"
    break;

  case 16: /* data_type: INT_TYPE  */
#line 139 "parser.y"
                   { (yyval.type_enum) = TYPE_INT;    }
#line 1365 "parser.tab.c"
    break;

  case 17: /* data_type: DOUBLE_TYPE  */
#line 140 "parser.y"
                   { (yyval.type_enum) = TYPE_DOUBLE; }
#line 1371 "parser.tab.c"
    break;

  case 18: /* data_type: CHAR_TYPE  */
#line 141 "parser.y"
                   { (yyval.type_enum) = TYPE_CHAR;   }
#line 1377 "parser.tab.c"
    break;

  case 19: /* data_type: STRING_TYPE  */
#line 142 "parser.y"
                   { (yyval.type_enum) = TYPE_STRING; }
#line 1383 "parser.tab.c"
    break;

  case 20: /* data_type: BOOL_TYPE  */
#line 143 "parser.y"
                   { (yyval.type_enum) = TYPE_BOOL;   }
#line 1389 "parser.tab.c"
    break;

  case 21: /* var_declaration: IDENTIFIER data_type ARROW expression  */
#line 147 "parser.y"
                                            {
        (yyval.ast_node) = ast_create_var_decl((yyvsp[-3].s_val), (DataType)(yyvsp[-2].type_enum), (yyvsp[0].ast_node), yylineno);
        free((yyvsp[-3].s_val));
    }
#line 1398 "parser.tab.c"
    break;

  case 22: /* var_declaration: IDENTIFIER data_type ARROW STRING_LITERAL  */
#line 151 "parser.y"
                                                {
        (yyval.ast_node) = ast_create_var_decl((yyvsp[-3].s_val), (DataType)(yyvsp[-2].type_enum), 
            ast_create_literal_string((yyvsp[0].s_val), yylineno), yylineno);
        free((yyvsp[-3].s_val));
    }
#line 1408 "parser.tab.c"
    break;

  case 23: /* var_declaration: IDENTIFIER data_type ARROW CHAR_LITERAL  */
#line 156 "parser.y"
                                              {
        (yyval.ast_node) = ast_create_var_decl((yyvsp[-3].s_val), (DataType)(yyvsp[-2].type_enum), 
            ast_create_literal_char((yyvsp[0].c_val), yylineno), yylineno);
        free((yyvsp[-3].s_val));
    }
#line 1418 "parser.tab.c"
    break;

  case 24: /* var_declaration: IDENTIFIER data_type ARROW BOOL_LITERAL  */
#line 161 "parser.y"
                                              {
        (yyval.ast_node) = ast_create_var_decl((yyvsp[-3].s_val), (DataType)(yyvsp[-2].type_enum), 
            ast_create_literal_bool((yyvsp[0].b_val), yylineno), yylineno);
        free((yyvsp[-3].s_val));
    }
#line 1428 "parser.tab.c"
    break;

  case 25: /* var_assignment: IDENTIFIER EQUALS expression  */
#line 169 "parser.y"
                                   {
        (yyval.ast_node) = ast_create_var_assign((yyvsp[-2].s_val), (yyvsp[0].ast_node), yylineno);
        free((yyvsp[-2].s_val));
    }
#line 1437 "parser.tab.c"
    break;

  case 26: /* var_assignment: IDENTIFIER EQUALS STRING_LITERAL  */
#line 173 "parser.y"
                                       {
        (yyval.ast_node) = ast_create_var_assign((yyvsp[-2].s_val), 
            ast_create_literal_string((yyvsp[0].s_val), yylineno), yylineno);
        free((yyvsp[-2].s_val));
    }
#line 1447 "parser.tab.c"
    break;

  case 27: /* print_statement: PRINT IDENTIFIER  */
#line 181 "parser.y"
                       { 
        (yyval.ast_node) = ast_create_print(ast_create_identifier((yyvsp[0].s_val), yylineno), yylineno);
        free((yyvsp[0].s_val));
    }
#line 1456 "parser.tab.c"
    break;

  case 28: /* print_statement: PRINT STRING_LITERAL  */
#line 185 "parser.y"
                           {
        (yyval.ast_node) = ast_create_print(ast_create_literal_string((yyvsp[0].s_val), yylineno), yylineno);
        free((yyvsp[0].s_val));
    }
#line 1465 "parser.tab.c"
    break;

  case 29: /* print_statement: PRINT expression  */
#line 189 "parser.y"
                       {
        (yyval.ast_node) = ast_create_print((yyvsp[0].ast_node), yylineno);
    }
#line 1473 "parser.tab.c"
    break;

  case 30: /* function_declaration: FUNCTION IDENTIFIER LPARENT parameter_list RPARENT data_type LBRACE statements RBRACE  */
#line 195 "parser.y"
                                                                                            {
        int param_count = 0;
        while ((yyvsp[-5].ast_array) != NULL && (yyvsp[-5].ast_array)[param_count] != NULL) param_count++;
        
        int stmt_count = 0;
        while ((yyvsp[-1].ast_array) != NULL && (yyvsp[-1].ast_array)[stmt_count] != NULL) stmt_count++;
        
        ASTNode* body = ast_create_block((yyvsp[-1].ast_array), stmt_count);
        (yyval.ast_node) = ast_create_func_decl((yyvsp[-7].s_val), (yyvsp[-5].ast_array), param_count, (DataType)(yyvsp[-3].type_enum), body, yylineno);
        free((yyvsp[-7].s_val));
    }
#line 1489 "parser.tab.c"
    break;

  case 31: /* function_declaration: FUNCTION IDENTIFIER LPARENT RPARENT data_type LBRACE statements RBRACE  */
#line 206 "parser.y"
                                                                             {
        int stmt_count = 0;
        while ((yyvsp[-1].ast_array) != NULL && (yyvsp[-1].ast_array)[stmt_count] != NULL) stmt_count++;
        
        ASTNode* body = ast_create_block((yyvsp[-1].ast_array), stmt_count);
        (yyval.ast_node) = ast_create_func_decl((yyvsp[-6].s_val), NULL, 0, (DataType)(yyvsp[-3].type_enum), body, yylineno);
        free((yyvsp[-6].s_val));
    }
#line 1502 "parser.tab.c"
    break;

  case 32: /* parameter_list: IDENTIFIER data_type  */
#line 217 "parser.y"
                           {
        ASTNode** params = (ASTNode**) malloc(sizeof(ASTNode*) * 10);
        params[0] = ast_create_param((yyvsp[-1].s_val), (DataType)(yyvsp[0].type_enum), yylineno);
        params[1] = NULL;
        (yyval.ast_array) = params;
        free((yyvsp[-1].s_val));
    }
#line 1514 "parser.tab.c"
    break;

  case 33: /* parameter_list: parameter_list COMMA IDENTIFIER data_type  */
#line 224 "parser.y"
                                                {
        int i = 0;
        while ((yyvsp[-3].ast_array)[i] != NULL) i++;
        (yyvsp[-3].ast_array)[i] = ast_create_param((yyvsp[-1].s_val), (DataType)(yyvsp[0].type_enum), yylineno);
        (yyvsp[-3].ast_array)[i + 1] = NULL;
        (yyval.ast_array) = (yyvsp[-3].ast_array);
        free((yyvsp[-1].s_val));
    }
#line 1527 "parser.tab.c"
    break;

  case 34: /* if_statement: IF LPARENT expression RPARENT block  */
#line 235 "parser.y"
                                          {
        (yyval.ast_node) = ast_create_if((yyvsp[-2].ast_node), (yyvsp[0].ast_node), NULL, yylineno);
    }
#line 1535 "parser.tab.c"
    break;

  case 35: /* if_statement: IF LPARENT expression RPARENT block ELSE block  */
#line 238 "parser.y"
                                                     {
        (yyval.ast_node) = ast_create_if((yyvsp[-4].ast_node), (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno);
    }
#line 1543 "parser.tab.c"
    break;

  case 36: /* while_statement: WHILE LPARENT expression RPARENT block  */
#line 245 "parser.y"
                                             {
        (yyval.ast_node) = ast_create_while((yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno);
    }
#line 1551 "parser.tab.c"
    break;

  case 37: /* function_call: IDENTIFIER LPARENT argument_list RPARENT  */
#line 251 "parser.y"
                                               {
        int arg_count = 0;
        if ((yyvsp[-1].ast_array) != NULL) {
            while ((yyvsp[-1].ast_array)[arg_count] != NULL) arg_count++;
        }
        (yyval.ast_node) = ast_create_func_call((yyvsp[-3].s_val), (yyvsp[-1].ast_array), arg_count, yylineno);
        free((yyvsp[-3].s_val));
    }
#line 1564 "parser.tab.c"
    break;

  case 38: /* argument_list: expression  */
#line 262 "parser.y"
                 {
        ASTNode** arr = (ASTNode**) malloc(sizeof(ASTNode*) * 10);
        arr[0] = (yyvsp[0].ast_node);
        arr[1] = NULL;
        (yyval.ast_array) = arr;
    }
#line 1575 "parser.tab.c"
    break;

  case 39: /* argument_list: argument_list COMMA expression  */
#line 268 "parser.y"
                                     {
        int i = 0;
        while ((yyvsp[-2].ast_array)[i] != NULL) i++;
        (yyvsp[-2].ast_array)[i] = (yyvsp[0].ast_node);
        (yyvsp[-2].ast_array)[i + 1] = NULL;
        (yyval.ast_array) = (yyvsp[-2].ast_array);
    }
#line 1587 "parser.tab.c"
    break;

  case 40: /* argument_list: %empty  */
#line 275 "parser.y"
                  {
        (yyval.ast_array) = NULL;
    }
#line 1595 "parser.tab.c"
    break;

  case 41: /* expression: NUMBER  */
#line 281 "parser.y"
                                   { (yyval.ast_node) = ast_create_literal_int((int)(yyvsp[0].d_val), yylineno); }
#line 1601 "parser.tab.c"
    break;

  case 42: /* expression: DOUBLE_LITERAL  */
#line 282 "parser.y"
                                   { (yyval.ast_node) = ast_create_literal_double((yyvsp[0].d_val), yylineno); }
#line 1607 "parser.tab.c"
    break;

  case 43: /* expression: CHAR_LITERAL  */
#line 283 "parser.y"
                                   { (yyval.ast_node) = ast_create_literal_char((yyvsp[0].c_val), yylineno); }
#line 1613 "parser.tab.c"
    break;

  case 44: /* expression: BOOL_LITERAL  */
#line 284 "parser.y"
                                   { (yyval.ast_node) = ast_create_literal_bool((yyvsp[0].b_val), yylineno); }
#line 1619 "parser.tab.c"
    break;

  case 45: /* expression: STRING_LITERAL  */
#line 285 "parser.y"
                                   { (yyval.ast_node) = ast_create_literal_string((yyvsp[0].s_val), yylineno); }
#line 1625 "parser.tab.c"
    break;

  case 46: /* expression: IDENTIFIER  */
#line 286 "parser.y"
                                   { (yyval.ast_node) = ast_create_identifier((yyvsp[0].s_val), yylineno); free((yyvsp[0].s_val)); }
#line 1631 "parser.tab.c"
    break;

  case 47: /* expression: expression PLUS expression  */
#line 287 "parser.y"
                                   { (yyval.ast_node) = ast_create_binop(BINOP_PLUS, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1637 "parser.tab.c"
    break;

  case 48: /* expression: expression SUB expression  */
#line 288 "parser.y"
                                   { (yyval.ast_node) = ast_create_binop(BINOP_MINUS, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1643 "parser.tab.c"
    break;

  case 49: /* expression: expression MUL expression  */
#line 289 "parser.y"
                                   { (yyval.ast_node) = ast_create_binop(BINOP_MUL, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1649 "parser.tab.c"
    break;

  case 50: /* expression: expression DIV expression  */
#line 290 "parser.y"
                                   { (yyval.ast_node) = ast_create_binop(BINOP_DIV, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1655 "parser.tab.c"
    break;

  case 51: /* expression: expression EQ expression  */
#line 291 "parser.y"
                                   { (yyval.ast_node) = ast_create_binop(BINOP_EQ, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1661 "parser.tab.c"
    break;

  case 52: /* expression: expression NE expression  */
#line 292 "parser.y"
                                   { (yyval.ast_node) = ast_create_binop(BINOP_NE, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1667 "parser.tab.c"
    break;

  case 53: /* expression: expression LT expression  */
#line 293 "parser.y"
                                   { (yyval.ast_node) = ast_create_binop(BINOP_LT, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1673 "parser.tab.c"
    break;

  case 54: /* expression: expression LE expression  */
#line 294 "parser.y"
                                   { (yyval.ast_node) = ast_create_binop(BINOP_LE, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1679 "parser.tab.c"
    break;

  case 55: /* expression: expression GT expression  */
#line 295 "parser.y"
                                   { (yyval.ast_node) = ast_create_binop(BINOP_GT, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1685 "parser.tab.c"
    break;

  case 56: /* expression: expression GE expression  */
#line 296 "parser.y"
                                   { (yyval.ast_node) = ast_create_binop(BINOP_GE, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1691 "parser.tab.c"
    break;

  case 57: /* expression: expression AND expression  */
#line 297 "parser.y"
                                   { (yyval.ast_node) = ast_create_binop(BINOP_AND, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1697 "parser.tab.c"
    break;

  case 58: /* expression: expression OR expression  */
#line 298 "parser.y"
                                   { (yyval.ast_node) = ast_create_binop(BINOP_OR, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), yylineno); }
#line 1703 "parser.tab.c"
    break;

  case 59: /* expression: NOT expression  */
#line 299 "parser.y"
                                   { (yyval.ast_node) = ast_create_unary(UNARY_NOT, (yyvsp[0].ast_node), yylineno); }
#line 1709 "parser.tab.c"
    break;

  case 60: /* expression: SUB expression  */
#line 300 "parser.y"
                                  { (yyval.ast_node) = ast_create_unary(UNARY_NEG, (yyvsp[0].ast_node), yylineno); }
#line 1715 "parser.tab.c"
    break;

  case 61: /* expression: LPARENT expression RPARENT  */
#line 301 "parser.y"
                                   { (yyval.ast_node) = (yyvsp[-1].ast_node); }
#line 1721 "parser.tab.c"
    break;

  case 62: /* expression: function_call  */
#line 302 "parser.y"
                                   { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1727 "parser.tab.c"
    break;


#line 1731 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 305 "parser.y"


void yyerror(const char* s) {
    fprintf(stderr, "[WS ERROR] Line %d: %s\n", yylineno, s);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file.ws>\n", argv[0]);
        return 1;
    }
    FILE* file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "[WS ERROR] Could not open file: %s\n", argv[1]);
        return 1;
    }
    yyin = file;
    push_scope();
    
    interp = interp_create();
    
    int result = yyparse();
    fclose(file);
    
    if (result == 0 && root_ast != NULL) {
        printf("\nParsing successful. Executing...\n\n");
        interp_execute(interp, root_ast);
        ast_free(root_ast);
        printf("\n[SUCCESS] Program executed successfully.\n");
    } else if (result == 0) {
        printf("\nNo statements to execute.\n");
    }
    
    interp_free(interp);
    free_table();
    return result;
}
