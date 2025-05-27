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
#line 1 "src/yacc.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

int yylex();
void yyerror(const char *s);

FILE *saida;

#define MAX_VARS 100

struct variavel {
    char nome[50];
    int tipo;  
};

struct variavel variaveis[MAX_VARS];
int num_vars = 0;

AST* raiz_ast = NULL;

int buscar_tipo_variavel(char *nome) {
    for(int i = 0; i < num_vars; i++) {
        if(strcmp(variaveis[i].nome, nome) == 0) {
            return variaveis[i].tipo;
        }
    }
    return -1;
}

// Add these variable type definitions
#define TIPO_INT 0
#define TIPO_FLOAT 1
#define TIPO_CHAR 2


#line 110 "build/y.tab.c"

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

#include "y.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INICIO = 3,                     /* INICIO  */
  YYSYMBOL_FIM = 4,                        /* FIM  */
  YYSYMBOL_LEIA = 5,                       /* LEIA  */
  YYSYMBOL_ESCREVA = 6,                    /* ESCREVA  */
  YYSYMBOL_VAR = 7,                        /* VAR  */
  YYSYMBOL_TIPO_INTEIRO = 8,               /* TIPO_INTEIRO  */
  YYSYMBOL_TIPO_REAL = 9,                  /* TIPO_REAL  */
  YYSYMBOL_TIPO_CARACTERE = 10,            /* TIPO_CARACTERE  */
  YYSYMBOL_SE = 11,                        /* SE  */
  YYSYMBOL_SENAO = 12,                     /* SENAO  */
  YYSYMBOL_ENTAO = 13,                     /* ENTAO  */
  YYSYMBOL_FIMSE = 14,                     /* FIMSE  */
  YYSYMBOL_ENQUANTO = 15,                  /* ENQUANTO  */
  YYSYMBOL_FACA = 16,                      /* FACA  */
  YYSYMBOL_FIMENQUANTO = 17,               /* FIMENQUANTO  */
  YYSYMBOL_IGUAL = 18,                     /* IGUAL  */
  YYSYMBOL_COMPARA = 19,                   /* COMPARA  */
  YYSYMBOL_DIFERENTE = 20,                 /* DIFERENTE  */
  YYSYMBOL_MENOR = 21,                     /* MENOR  */
  YYSYMBOL_MAIOR = 22,                     /* MAIOR  */
  YYSYMBOL_MENOR_IGUAL = 23,               /* MENOR_IGUAL  */
  YYSYMBOL_MAIOR_IGUAL = 24,               /* MAIOR_IGUAL  */
  YYSYMBOL_SOMA = 25,                      /* SOMA  */
  YYSYMBOL_SUB = 26,                       /* SUB  */
  YYSYMBOL_MUL = 27,                       /* MUL  */
  YYSYMBOL_DIV = 28,                       /* DIV  */
  YYSYMBOL_ABREPAR = 29,                   /* ABREPAR  */
  YYSYMBOL_FECHAPAR = 30,                  /* FECHAPAR  */
  YYSYMBOL_PONTOEVIRGULA = 31,             /* PONTOEVIRGULA  */
  YYSYMBOL_PARA = 32,                      /* PARA  */
  YYSYMBOL_DE = 33,                        /* DE  */
  YYSYMBOL_ATE = 34,                       /* ATE  */
  YYSYMBOL_FIMPARA = 35,                   /* FIMPARA  */
  YYSYMBOL_DOISPONTOS = 36,                /* DOISPONTOS  */
  YYSYMBOL_NUM = 37,                       /* NUM  */
  YYSYMBOL_ID = 38,                        /* ID  */
  YYSYMBOL_STRING = 39,                    /* STRING  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_programa = 41,                  /* programa  */
  YYSYMBOL_bloco = 42,                     /* bloco  */
  YYSYMBOL_comando = 43,                   /* comando  */
  YYSYMBOL_declaracao = 44,                /* declaracao  */
  YYSYMBOL_tipo = 45,                      /* tipo  */
  YYSYMBOL_leitura = 46,                   /* leitura  */
  YYSYMBOL_escrita = 47,                   /* escrita  */
  YYSYMBOL_atribuicao = 48,                /* atribuicao  */
  YYSYMBOL_expressao = 49                  /* expressao  */
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
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   204

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  10
/* YYNRULES -- Number of rules.  */
#define YYNRULES  32
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  83

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


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
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    69,    69,    76,    79,    96,    97,    98,    99,   100,
     103,   106,   109,   116,   127,   128,   129,   133,   140,   144,
     148,   151,   158,   165,   166,   167,   170,   173,   176,   179,
     182,   185,   188
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
  "\"end of file\"", "error", "\"invalid token\"", "INICIO", "FIM",
  "LEIA", "ESCREVA", "VAR", "TIPO_INTEIRO", "TIPO_REAL", "TIPO_CARACTERE",
  "SE", "SENAO", "ENTAO", "FIMSE", "ENQUANTO", "FACA", "FIMENQUANTO",
  "IGUAL", "COMPARA", "DIFERENTE", "MENOR", "MAIOR", "MENOR_IGUAL",
  "MAIOR_IGUAL", "SOMA", "SUB", "MUL", "DIV", "ABREPAR", "FECHAPAR",
  "PONTOEVIRGULA", "PARA", "DE", "ATE", "FIMPARA", "DOISPONTOS", "NUM",
  "ID", "STRING", "$accept", "programa", "bloco", "comando", "declaracao",
  "tipo", "leitura", "escrita", "atribuicao", "expressao", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-36)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       8,    90,    20,   -11,     0,    -5,   -35,   -35,    -8,    22,
      10,   -36,   -36,   -36,   -36,   -36,   -36,     5,   -15,    18,
     -36,   -36,   126,   159,    11,   -35,   -36,   -36,    16,    23,
      27,    30,   147,   -36,   -36,   -36,    14,    90,   -35,   -35,
     -35,   -35,   -35,   -35,   -35,   -35,    90,   -35,   134,    31,
      33,    34,    35,    41,    43,    44,   178,   178,   178,   178,
     178,   178,   -14,   -14,    62,   110,   -36,   -36,   -36,   -36,
     -36,   -36,   -36,    90,   -36,   -36,   -35,    47,   170,   -36,
      90,    78,   -36
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     3,     5,     6,     7,     8,     1,     0,     0,     0,
      23,    24,     0,     0,     0,     0,     2,     4,     0,    23,
      24,     0,     0,    14,    15,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    27,    32,    28,    29,
      30,    31,    25,    26,     0,     0,    22,    17,    21,    18,
      19,    20,    13,     0,    10,    11,     0,     0,     0,     9,
       0,     0,    12
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -36,   -36,   -33,   -10,   -36,   -36,   -36,   -36,   -36,    -6
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,    10,    11,    12,    36,    13,    14,    15,    22
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      27,    23,    20,    21,    55,    38,    39,    40,    41,    42,
      43,     1,    32,    64,    26,     3,     4,     5,    17,    48,
      16,     6,    29,    30,    31,     7,    33,    34,    35,    18,
      24,    19,    56,    57,    58,    59,    60,    61,    62,    63,
      25,    65,     8,    28,    47,    27,    49,    81,     9,     3,
       4,     5,    54,    50,    27,     6,    73,    51,    74,     7,
      52,    79,    67,    77,    68,    69,    70,     3,     4,     5,
      78,    27,    71,     6,    72,     0,     8,     7,     0,    75,
       0,     0,     9,     3,     4,     5,     0,     0,     0,     6,
       0,     0,     0,     7,     8,     3,     4,     5,     0,     0,
       9,     6,     0,     0,     0,     7,     0,     0,     0,     0,
       8,     0,     0,    82,     0,     0,     9,     0,     0,     0,
       0,     0,     8,     0,     0,     0,     0,     0,     9,    38,
      39,    40,    41,    42,    43,    44,    45,     0,     0,    37,
       0,     0,     0,     0,    76,    38,    39,    40,    41,    42,
      43,    44,    45,    38,    39,    40,    41,    42,    43,    44,
      45,     0,     0,     0,     0,    66,    38,    39,    40,    41,
      42,    43,    44,    45,     0,    46,     0,    53,    38,    39,
      40,    41,    42,    43,    44,    45,    80,     0,     0,    38,
      39,    40,    41,    42,    43,    44,    45,    38,    39,    40,
      41,    42,    43,    44,    45
};

static const yytype_int8 yycheck[] =
{
      10,     7,    37,    38,    37,    19,    20,    21,    22,    23,
      24,     3,    18,    46,     4,     5,     6,     7,    29,    25,
       0,    11,    37,    38,    39,    15,     8,     9,    10,    29,
      38,    36,    38,    39,    40,    41,    42,    43,    44,    45,
      18,    47,    32,    38,    33,    55,    30,    80,    38,     5,
       6,     7,    38,    30,    64,    11,    12,    30,    14,    15,
      30,    14,    31,    73,    31,    31,    31,     5,     6,     7,
      76,    81,    31,    11,    31,    -1,    32,    15,    -1,    17,
      -1,    -1,    38,     5,     6,     7,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    15,    32,     5,     6,     7,    -1,    -1,
      38,    11,    -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,
      32,    -1,    -1,    35,    -1,    -1,    38,    -1,    -1,    -1,
      -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    38,    19,
      20,    21,    22,    23,    24,    25,    26,    -1,    -1,    13,
      -1,    -1,    -1,    -1,    34,    19,    20,    21,    22,    23,
      24,    25,    26,    19,    20,    21,    22,    23,    24,    25,
      26,    -1,    -1,    -1,    -1,    31,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    16,    -1,    30,    19,    20,
      21,    22,    23,    24,    25,    26,    16,    -1,    -1,    19,
      20,    21,    22,    23,    24,    25,    26,    19,    20,    21,
      22,    23,    24,    25,    26
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    41,     5,     6,     7,    11,    15,    32,    38,
      42,    43,    44,    46,    47,    48,     0,    29,    29,    36,
      37,    38,    49,    49,    38,    18,     4,    43,    38,    37,
      38,    39,    49,     8,     9,    10,    45,    13,    19,    20,
      21,    22,    23,    24,    25,    26,    16,    33,    49,    30,
      30,    30,    30,    30,    38,    42,    49,    49,    49,    49,
      49,    49,    49,    49,    42,    49,    31,    31,    31,    31,
      31,    31,    31,    12,    14,    17,    34,    43,    49,    14,
      16,    42,    35
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    43,    43,    43,
      43,    43,    43,    44,    45,    45,    45,    46,    47,    47,
      47,    47,    48,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     1,     2,     1,     1,     1,     1,     7,
       5,     5,     9,     5,     1,     1,     1,     5,     5,     5,
       5,     5,     4,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3
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
  case 2: /* programa: INICIO bloco FIM  */
#line 69 "src/yacc.y"
                     {
        raiz_ast = ast_cria(AST_PROGRAMA, NULL, 1, (yyvsp[-1].ast));
        (yyval.ast) = raiz_ast;
    }
#line 1218 "build/y.tab.c"
    break;

  case 3: /* bloco: comando  */
#line 76 "src/yacc.y"
            { 
        (yyval.ast) = ast_cria(AST_BLOCO, NULL, 1, (yyvsp[0].ast)); 
    }
#line 1226 "build/y.tab.c"
    break;

  case 4: /* bloco: bloco comando  */
#line 79 "src/yacc.y"
                    {
        if (!(yyvsp[0].ast)) {
            fprintf(stderr, "[ERRO] Comando nulo em bloco!\n");
            (yyval.ast) = (yyvsp[-1].ast); // Retorna o bloco anterior sem adicionar comando nulo
        } else {
            int n = (yyvsp[-1].ast)->n_filhos + 1;
            AST** filhos = malloc(sizeof(AST*) * n);
            for (int i = 0; i < (yyvsp[-1].ast)->n_filhos; i++) filhos[i] = (yyvsp[-1].ast)->filhos[i];
            filhos[n-1] = (yyvsp[0].ast);
            AST* novo_bloco = ast_cria(AST_BLOCO, NULL, 0); // cria vazio
            novo_bloco->n_filhos = n;
            novo_bloco->filhos = filhos;
            (yyval.ast) = novo_bloco;
        }
    }
#line 1246 "build/y.tab.c"
    break;

  case 5: /* comando: declaracao  */
#line 96 "src/yacc.y"
               { (yyval.ast) = (yyvsp[0].ast); }
#line 1252 "build/y.tab.c"
    break;

  case 6: /* comando: leitura  */
#line 97 "src/yacc.y"
              { (yyval.ast) = (yyvsp[0].ast); }
#line 1258 "build/y.tab.c"
    break;

  case 7: /* comando: escrita  */
#line 98 "src/yacc.y"
              { (yyval.ast) = (yyvsp[0].ast); }
#line 1264 "build/y.tab.c"
    break;

  case 8: /* comando: atribuicao  */
#line 99 "src/yacc.y"
                 { (yyval.ast) = (yyvsp[0].ast); }
#line 1270 "build/y.tab.c"
    break;

  case 9: /* comando: SE expressao ENTAO bloco SENAO comando FIMSE  */
#line 100 "src/yacc.y"
                                                   {
        (yyval.ast) = ast_cria(AST_IF, NULL, 3, (yyvsp[-5].ast), (yyvsp[-3].ast), (yyvsp[-1].ast));
    }
#line 1278 "build/y.tab.c"
    break;

  case 10: /* comando: SE expressao ENTAO bloco FIMSE  */
#line 103 "src/yacc.y"
                                     {
        (yyval.ast) = ast_cria(AST_IF, NULL, 2, (yyvsp[-3].ast), (yyvsp[-1].ast));
    }
#line 1286 "build/y.tab.c"
    break;

  case 11: /* comando: ENQUANTO expressao FACA bloco FIMENQUANTO  */
#line 106 "src/yacc.y"
                                                {
        (yyval.ast) = ast_cria(AST_WHILE, NULL, 2, (yyvsp[-3].ast), (yyvsp[-1].ast));
    }
#line 1294 "build/y.tab.c"
    break;

  case 12: /* comando: PARA ID DE expressao ATE expressao FACA bloco FIMPARA  */
#line 109 "src/yacc.y"
                                                            {
        AST* id = ast_cria(AST_ID, strdup((yyvsp[-7].str)), 0);
        (yyval.ast) = ast_cria(AST_FOR, NULL, 4, id, (yyvsp[-5].ast), (yyvsp[-3].ast), (yyvsp[-1].ast));
    }
#line 1303 "build/y.tab.c"
    break;

  case 13: /* declaracao: VAR DOISPONTOS tipo ID PONTOEVIRGULA  */
#line 116 "src/yacc.y"
                                         {
        strcpy(variaveis[num_vars].nome, (yyvsp[-1].str));
        variaveis[num_vars].tipo = (yyvsp[-2].inteiro);
        num_vars++;
        AST* tipo_no = ast_cria(AST_ID, strdup((yyvsp[-1].str)), 0);
        AST* tipo_tipo = ast_cria(AST_NUM, strdup((yyvsp[-2].inteiro) == TIPO_INT ? "int" : (yyvsp[-2].inteiro) == TIPO_FLOAT ? "float" : "char"), 0);
        (yyval.ast) = ast_cria(AST_DECLARACAO, NULL, 2, tipo_tipo, tipo_no);
    }
#line 1316 "build/y.tab.c"
    break;

  case 14: /* tipo: TIPO_INTEIRO  */
#line 127 "src/yacc.y"
                     { (yyval.inteiro) = TIPO_INT; }
#line 1322 "build/y.tab.c"
    break;

  case 15: /* tipo: TIPO_REAL  */
#line 128 "src/yacc.y"
                     { (yyval.inteiro) = TIPO_FLOAT; }
#line 1328 "build/y.tab.c"
    break;

  case 16: /* tipo: TIPO_CARACTERE  */
#line 129 "src/yacc.y"
                     { (yyval.inteiro) = TIPO_CHAR; }
#line 1334 "build/y.tab.c"
    break;

  case 17: /* leitura: LEIA ABREPAR ID FECHAPAR PONTOEVIRGULA  */
#line 133 "src/yacc.y"
                                           {
        AST* id = ast_cria(AST_ID, strdup((yyvsp[-2].str)), 0);
        (yyval.ast) = ast_cria(AST_LEITURA, NULL, 1, id);
    }
#line 1343 "build/y.tab.c"
    break;

  case 18: /* escrita: ESCREVA ABREPAR ID FECHAPAR PONTOEVIRGULA  */
#line 140 "src/yacc.y"
                                              {
        AST* id = ast_cria(AST_ID, strdup((yyvsp[-2].str)), 0);
        (yyval.ast) = ast_cria(AST_ESCRITA, NULL, 1, id);
    }
#line 1352 "build/y.tab.c"
    break;

  case 19: /* escrita: ESCREVA ABREPAR STRING FECHAPAR PONTOEVIRGULA  */
#line 144 "src/yacc.y"
                                                    {
        AST* str = ast_cria(AST_STRING, strdup((yyvsp[-2].str)), 0);
        (yyval.ast) = ast_cria(AST_ESCRITA, NULL, 1, str);
    }
#line 1361 "build/y.tab.c"
    break;

  case 20: /* escrita: ESCREVA ABREPAR expressao FECHAPAR PONTOEVIRGULA  */
#line 148 "src/yacc.y"
                                                       {
        (yyval.ast) = ast_cria(AST_ESCRITA, NULL, 1, (yyvsp[-2].ast));
    }
#line 1369 "build/y.tab.c"
    break;

  case 21: /* escrita: ESCREVA ABREPAR NUM FECHAPAR PONTOEVIRGULA  */
#line 151 "src/yacc.y"
                                                 {
        AST* num = ast_cria(AST_NUM, strdup((yyvsp[-2].str)), 0);
        (yyval.ast) = ast_cria(AST_ESCRITA, NULL, 1, num);
    }
#line 1378 "build/y.tab.c"
    break;

  case 22: /* atribuicao: ID IGUAL expressao PONTOEVIRGULA  */
#line 158 "src/yacc.y"
                                     {
        AST* id = ast_cria(AST_ID, strdup((yyvsp[-3].str)), 0);
        (yyval.ast) = ast_cria(AST_ATRIBUICAO, NULL, 2, id, (yyvsp[-1].ast));
    }
#line 1387 "build/y.tab.c"
    break;

  case 23: /* expressao: NUM  */
#line 165 "src/yacc.y"
        { (yyval.ast) = ast_cria(AST_NUM, strdup((yyvsp[0].str)), 0); }
#line 1393 "build/y.tab.c"
    break;

  case 24: /* expressao: ID  */
#line 166 "src/yacc.y"
         { (yyval.ast) = ast_cria(AST_ID, strdup((yyvsp[0].str)), 0); }
#line 1399 "build/y.tab.c"
    break;

  case 25: /* expressao: expressao SOMA expressao  */
#line 167 "src/yacc.y"
                               {
        (yyval.ast) = ast_cria(AST_EXPRESSAO, strdup("+"), 2, (yyvsp[-2].ast), (yyvsp[0].ast));
    }
#line 1407 "build/y.tab.c"
    break;

  case 26: /* expressao: expressao SUB expressao  */
#line 170 "src/yacc.y"
                              {
        (yyval.ast) = ast_cria(AST_EXPRESSAO, strdup("-"), 2, (yyvsp[-2].ast), (yyvsp[0].ast));
    }
#line 1415 "build/y.tab.c"
    break;

  case 27: /* expressao: expressao COMPARA expressao  */
#line 173 "src/yacc.y"
                                  {
        (yyval.ast) = ast_cria(AST_EXPRESSAO, strdup("=="), 2, (yyvsp[-2].ast), (yyvsp[0].ast));
    }
#line 1423 "build/y.tab.c"
    break;

  case 28: /* expressao: expressao MENOR expressao  */
#line 176 "src/yacc.y"
                                {
        (yyval.ast) = ast_cria(AST_EXPRESSAO, strdup("<"), 2, (yyvsp[-2].ast), (yyvsp[0].ast));
    }
#line 1431 "build/y.tab.c"
    break;

  case 29: /* expressao: expressao MAIOR expressao  */
#line 179 "src/yacc.y"
                                {
        (yyval.ast) = ast_cria(AST_EXPRESSAO, strdup(">"), 2, (yyvsp[-2].ast), (yyvsp[0].ast));
    }
#line 1439 "build/y.tab.c"
    break;

  case 30: /* expressao: expressao MENOR_IGUAL expressao  */
#line 182 "src/yacc.y"
                                      {
        (yyval.ast) = ast_cria(AST_EXPRESSAO, strdup("<="), 2, (yyvsp[-2].ast), (yyvsp[0].ast));
    }
#line 1447 "build/y.tab.c"
    break;

  case 31: /* expressao: expressao MAIOR_IGUAL expressao  */
#line 185 "src/yacc.y"
                                      {
        (yyval.ast) = ast_cria(AST_EXPRESSAO, strdup(">="), 2, (yyvsp[-2].ast), (yyvsp[0].ast));
    }
#line 1455 "build/y.tab.c"
    break;

  case 32: /* expressao: expressao DIFERENTE expressao  */
#line 188 "src/yacc.y"
                                    {
        (yyval.ast) = ast_cria(AST_EXPRESSAO, strdup("!="), 2, (yyvsp[-2].ast), (yyvsp[0].ast));
    }
#line 1463 "build/y.tab.c"
    break;


#line 1467 "build/y.tab.c"

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

#line 193 "src/yacc.y"


void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);
}
