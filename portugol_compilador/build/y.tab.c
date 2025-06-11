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
#include "simbolos.h"

int yylex();
void yyerror(const char *s);

FILE *saida;

int escopo_atual = 0;

AST* raiz_ast = NULL;

Simbolo *inserirFuncao(char *nome, int tipo_retorno, int escopo, int n_parametros, Simbolo **parametros);
Simbolo *inserirParametro(char *nome, int tipo, int escopo, int referencia);

#define TIPO_INT 0
#define TIPO_FLOAT 1
#define TIPO_CHAR 2
#define TIPO_BOOL 3
#define TIPO_VOID 4


#line 98 "build/y.tab.c"

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
  YYSYMBOL_TIPO_LOGICO = 11,               /* TIPO_LOGICO  */
  YYSYMBOL_TIPO_VAZIO = 12,                /* TIPO_VAZIO  */
  YYSYMBOL_SE = 13,                        /* SE  */
  YYSYMBOL_SENAO = 14,                     /* SENAO  */
  YYSYMBOL_ENTAO = 15,                     /* ENTAO  */
  YYSYMBOL_FIMSE = 16,                     /* FIMSE  */
  YYSYMBOL_ENQUANTO = 17,                  /* ENQUANTO  */
  YYSYMBOL_FACA = 18,                      /* FACA  */
  YYSYMBOL_FIMENQUANTO = 19,               /* FIMENQUANTO  */
  YYSYMBOL_IGUAL = 20,                     /* IGUAL  */
  YYSYMBOL_COMPARA = 21,                   /* COMPARA  */
  YYSYMBOL_DIFERENTE = 22,                 /* DIFERENTE  */
  YYSYMBOL_MENOR = 23,                     /* MENOR  */
  YYSYMBOL_MAIOR = 24,                     /* MAIOR  */
  YYSYMBOL_MENOR_IGUAL = 25,               /* MENOR_IGUAL  */
  YYSYMBOL_MAIOR_IGUAL = 26,               /* MAIOR_IGUAL  */
  YYSYMBOL_SOMA = 27,                      /* SOMA  */
  YYSYMBOL_SUB = 28,                       /* SUB  */
  YYSYMBOL_MUL = 29,                       /* MUL  */
  YYSYMBOL_DIV = 30,                       /* DIV  */
  YYSYMBOL_ABREPAR = 31,                   /* ABREPAR  */
  YYSYMBOL_FECHAPAR = 32,                  /* FECHAPAR  */
  YYSYMBOL_PONTOEVIRGULA = 33,             /* PONTOEVIRGULA  */
  YYSYMBOL_VIRGULA = 34,                   /* VIRGULA  */
  YYSYMBOL_PARA = 35,                      /* PARA  */
  YYSYMBOL_DE = 36,                        /* DE  */
  YYSYMBOL_ATE = 37,                       /* ATE  */
  YYSYMBOL_FIMPARA = 38,                   /* FIMPARA  */
  YYSYMBOL_DOISPONTOS = 39,                /* DOISPONTOS  */
  YYSYMBOL_FIMFUNCAO = 40,                 /* FIMFUNCAO  */
  YYSYMBOL_NUM = 41,                       /* NUM  */
  YYSYMBOL_ID = 42,                        /* ID  */
  YYSYMBOL_STRING = 43,                    /* STRING  */
  YYSYMBOL_FUNCAO = 44,                    /* FUNCAO  */
  YYSYMBOL_RETORNE = 45,                   /* RETORNE  */
  YYSYMBOL_COMENTARIO_LINHA = 46,          /* COMENTARIO_LINHA  */
  YYSYMBOL_COMENTARIO_BLOCO = 47,          /* COMENTARIO_BLOCO  */
  YYSYMBOL_48_ = 48,                       /* '&'  */
  YYSYMBOL_YYACCEPT = 49,                  /* $accept  */
  YYSYMBOL_programa = 50,                  /* programa  */
  YYSYMBOL_funcao = 51,                    /* funcao  */
  YYSYMBOL_cabecalho_funcao = 52,          /* cabecalho_funcao  */
  YYSYMBOL_lista_args = 53,                /* lista_args  */
  YYSYMBOL_args = 54,                      /* args  */
  YYSYMBOL_lista_funcoes = 55,             /* lista_funcoes  */
  YYSYMBOL_bloco = 56,                     /* bloco  */
  YYSYMBOL_57_1 = 57,                      /* $@1  */
  YYSYMBOL_bloco_conteudo = 58,            /* bloco_conteudo  */
  YYSYMBOL_comando = 59,                   /* comando  */
  YYSYMBOL_chamada_funcao = 60,            /* chamada_funcao  */
  YYSYMBOL_declaracao = 61,                /* declaracao  */
  YYSYMBOL_tipo = 62,                      /* tipo  */
  YYSYMBOL_leitura = 63,                   /* leitura  */
  YYSYMBOL_escrita = 64,                   /* escrita  */
  YYSYMBOL_atribuicao = 65,                /* atribuicao  */
  YYSYMBOL_expressao = 66,                 /* expressao  */
  YYSYMBOL_lista_parametros = 67,          /* lista_parametros  */
  YYSYMBOL_parametros = 68,                /* parametros  */
  YYSYMBOL_parametro = 69,                 /* parametro  */
  YYSYMBOL_comentario = 70                 /* comentario  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   195

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  134

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   302


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
       2,     2,     2,     2,     2,     2,     2,     2,    48,     2,
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
      45,    46,    47
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    61,    61,    65,    72,    78,    94,    95,    99,   100,
     113,   114,   127,   127,   138,   139,   156,   157,   158,   159,
     160,   161,   164,   167,   170,   174,   177,   181,   185,   191,
     200,   201,   202,   203,   204,   208,   216,   222,   226,   229,
     236,   244,   249,   255,   260,   265,   270,   275,   280,   285,
     290,   295,   318,   323,   331,   332,   336,   337,   350,   351,
     355,   356
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
  "TIPO_LOGICO", "TIPO_VAZIO", "SE", "SENAO", "ENTAO", "FIMSE", "ENQUANTO",
  "FACA", "FIMENQUANTO", "IGUAL", "COMPARA", "DIFERENTE", "MENOR", "MAIOR",
  "MENOR_IGUAL", "MAIOR_IGUAL", "SOMA", "SUB", "MUL", "DIV", "ABREPAR",
  "FECHAPAR", "PONTOEVIRGULA", "VIRGULA", "PARA", "DE", "ATE", "FIMPARA",
  "DOISPONTOS", "FIMFUNCAO", "NUM", "ID", "STRING", "FUNCAO", "RETORNE",
  "COMENTARIO_LINHA", "COMENTARIO_BLOCO", "'&'", "$accept", "programa",
  "funcao", "cabecalho_funcao", "lista_args", "args", "lista_funcoes",
  "bloco", "$@1", "bloco_conteudo", "comando", "chamada_funcao",
  "declaracao", "tipo", "leitura", "escrita", "atribuicao", "expressao",
  "lista_parametros", "parametros", "parametro", "comentario", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-27)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      19,   -27,     5,    14,    12,     1,   -27,   -27,    60,   -27,
     -27,   -27,    10,    23,     6,   -27,   -27,   -27,   -27,   -27,
       8,     8,    15,   -16,     8,   -27,   -27,     1,   -27,    22,
     -27,    17,   -27,   -27,   -27,   -27,    69,    32,    35,    47,
     -22,    60,   -27,    59,    72,    85,    56,     8,     8,   113,
     -27,   -27,    71,   -27,    74,   -27,    84,    88,    20,    89,
     149,    75,     8,   -27,     8,     8,     8,     8,     8,     8,
       8,     8,     8,     8,   -27,     8,   126,    90,    91,   161,
     -27,   -27,    60,    93,    94,    95,    96,    97,    98,   100,
      26,   161,   161,   161,   161,   161,   161,    40,    40,    40,
      40,   104,     2,   -27,   -27,     8,    -4,   112,   111,   -27,
     -27,   -27,   -27,   -27,   -27,   -27,   -27,     1,   -27,   -27,
       8,   161,   -27,   116,   -27,    60,   164,   139,   -27,   -27,
     -27,   -27,   154,   -27
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      10,    12,     0,     0,     0,     0,     1,    12,     0,    11,
      12,     3,     0,     0,     0,    30,    31,    32,    33,    34,
       0,     0,     0,     0,     0,    60,    61,    13,    14,     0,
      16,     0,    17,    18,    19,    20,     0,     0,     0,     0,
       0,     0,    41,    42,     0,     0,     0,     0,     6,     0,
      15,    26,     0,     2,     0,     4,     0,    41,    42,     0,
       0,     0,     6,    12,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    12,     0,     0,     0,     7,     8,
      25,    29,    54,     0,     0,     0,     0,     0,     0,     0,
       0,    45,    50,    46,    47,    48,    49,    43,    44,    52,
      53,     0,     0,    40,    27,     0,     0,     0,    55,    56,
      35,    39,    36,    37,    38,    28,    51,     0,    22,    23,
       0,     9,    58,     0,     5,     0,     0,     0,    59,    57,
      21,    12,     0,    24
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -27,   -27,   -27,   -27,   131,   -27,   -27,    -7,   -27,   -27,
     -26,   -27,   -27,    -6,   -27,   -27,   -27,    13,   -27,   -27,
      70,   -27
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     9,    10,    77,    78,     3,     4,     5,    27,
      28,    29,    30,    31,    32,    33,    34,    79,   107,   108,
     109,    35
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      36,    50,    37,    38,    47,     6,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    48,    11,     7,    21,    57,
      58,    59,     1,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    44,    45,    61,    22,    49,   122,   120,
     117,    39,   118,    23,   123,    41,    24,    25,    26,    42,
      43,    62,    85,    60,    40,    51,    90,    46,     8,    52,
      76,    64,    65,    66,    67,    68,    69,   101,    15,    16,
      17,    18,    19,    53,    54,    55,   106,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,    63,   102,    56,
      62,   126,    75,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    81,    82,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    83,    88,   121,   106,
      84,    86,   104,   119,   132,   105,   110,   111,   112,   113,
     114,   115,   116,   127,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,   124,   125,    80,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,   131,   128,   103,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
     130,    87,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,   133,    89,     0,   129
};

static const yytype_int16 yycheck[] =
{
       7,    27,     8,    10,    20,     0,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    31,     4,     3,    17,    41,
      42,    43,     3,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    20,    21,    41,    35,    24,    42,    37,
      14,    31,    16,    42,    48,    39,    45,    46,    47,    41,
      42,    31,    32,    40,    31,    33,    63,    42,    44,    42,
      47,    21,    22,    23,    24,    25,    26,    74,     8,     9,
      10,    11,    12,     4,    42,    40,    82,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    15,    75,    42,
      31,   117,    36,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    18,    33,    31,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    32,    42,   105,   125,
      32,    32,    32,    19,   131,    34,    33,    33,    33,    33,
      33,    33,    32,   120,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    32,    34,    33,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    18,    42,    33,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      16,    32,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    38,    62,    -1,   125
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    50,    55,    56,    57,     0,     3,    44,    51,
      52,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    17,    35,    42,    45,    46,    47,    58,    59,    60,
      61,    62,    63,    64,    65,    70,    56,    62,    56,    31,
      31,    39,    41,    42,    66,    66,    42,    20,    31,    66,
      59,    33,    42,     4,    42,    40,    42,    41,    42,    43,
      66,    62,    31,    15,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    18,    36,    66,    53,    54,    66,
      33,    33,    31,    32,    32,    32,    32,    32,    42,    53,
      56,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    56,    66,    33,    32,    34,    62,    67,    68,    69,
      33,    33,    33,    33,    33,    33,    32,    14,    16,    19,
      37,    66,    42,    48,    32,    34,    59,    66,    42,    69,
      16,    18,    56,    38
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    50,    51,    52,    53,    53,    54,    54,
      55,    55,    57,    56,    58,    58,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    60,    61,    61,
      62,    62,    62,    62,    62,    63,    64,    64,    64,    64,
      65,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    67,    67,    68,    68,    69,    69,
      70,    70
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     3,     3,     6,     0,     1,     1,     3,
       0,     2,     0,     2,     1,     2,     1,     1,     1,     1,
       1,     7,     5,     5,     9,     3,     2,     4,     5,     3,
       1,     1,     1,     1,     1,     5,     5,     5,     5,     5,
       4,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     4,     3,     3,     0,     1,     1,     3,     2,     3,
       1,     1
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
  case 2: /* programa: lista_funcoes INICIO bloco FIM  */
#line 61 "src/yacc.y"
                                   {
        raiz_ast = ast_cria(AST_PROGRAMA, NULL, 2, (yyvsp[-3].ast), (yyvsp[-1].ast));
        (yyval.ast) = raiz_ast;
    }
#line 1258 "build/y.tab.c"
    break;

  case 3: /* programa: INICIO bloco FIM  */
#line 65 "src/yacc.y"
                       {
        raiz_ast = ast_cria(AST_PROGRAMA, NULL, 1, (yyvsp[-1].ast));
        (yyval.ast) = raiz_ast;
    }
#line 1267 "build/y.tab.c"
    break;

  case 4: /* funcao: cabecalho_funcao bloco FIMFUNCAO  */
#line 72 "src/yacc.y"
                                     {
        (yyval.ast) = ast_cria(AST_FUNCAO, strdup((yyvsp[-2].ast)->valor), 2, (yyvsp[-2].ast)->filhos[0], (yyvsp[-1].ast));
    }
#line 1275 "build/y.tab.c"
    break;

  case 5: /* cabecalho_funcao: FUNCAO tipo ID ABREPAR lista_parametros FECHAPAR  */
#line 78 "src/yacc.y"
                                                     {
        // Insere a função ANTES do bloco, para permitir recursão
        Simbolo **parametros = NULL;
        if ((yyvsp[-1].ast)->n_filhos > 0) {
            parametros = malloc(sizeof(Simbolo*) * (yyvsp[-1].ast)->n_filhos);
            for (int i = 0; i < (yyvsp[-1].ast)->n_filhos; i++) {
                parametros[i] = buscarSimbolo((yyvsp[-1].ast)->filhos[i]->valor, escopo_atual + 1);
            }
        }
        inserirFuncao((yyvsp[-3].str), (yyvsp[-4].inteiro), escopo_atual, (yyvsp[-1].ast)->n_filhos, parametros);
        // Cria um nó AST para o cabeçalho (opcional, mas útil para manter a AST completa)
        (yyval.ast) = ast_cria(AST_DECLARACAO, strdup((yyvsp[-3].str)), 1, (yyvsp[-1].ast));
    }
#line 1293 "build/y.tab.c"
    break;

  case 6: /* lista_args: %empty  */
#line 94 "src/yacc.y"
                { (yyval.ast) = ast_cria(AST_BLOCO, NULL, 0); }
#line 1299 "build/y.tab.c"
    break;

  case 7: /* lista_args: args  */
#line 95 "src/yacc.y"
           { (yyval.ast) = (yyvsp[0].ast); }
#line 1305 "build/y.tab.c"
    break;

  case 8: /* args: expressao  */
#line 99 "src/yacc.y"
              { (yyval.ast) = ast_cria(AST_BLOCO, NULL, 1, (yyvsp[0].ast)); }
#line 1311 "build/y.tab.c"
    break;

  case 9: /* args: args VIRGULA expressao  */
#line 100 "src/yacc.y"
                             {
        int n = (yyvsp[-2].ast)->n_filhos + 1;
        AST** filhos = malloc(sizeof(AST*) * n);
        for (int i = 0; i < (yyvsp[-2].ast)->n_filhos; i++) filhos[i] = (yyvsp[-2].ast)->filhos[i];
        filhos[n-1] = (yyvsp[0].ast);
        AST* novo = ast_cria(AST_BLOCO, NULL, 0);
        novo->n_filhos = n;
        novo->filhos = filhos;
        (yyval.ast) = novo;
    }
#line 1326 "build/y.tab.c"
    break;

  case 10: /* lista_funcoes: %empty  */
#line 113 "src/yacc.y"
                { (yyval.ast) = ast_cria(AST_BLOCO, NULL, 0); }
#line 1332 "build/y.tab.c"
    break;

  case 11: /* lista_funcoes: lista_funcoes funcao  */
#line 114 "src/yacc.y"
                           { 
        int n = (yyvsp[-1].ast)->n_filhos + 1;
        AST** filhos = malloc(sizeof(AST*) * n);
        for (int i = 0; i < (yyvsp[-1].ast)->n_filhos; i++) filhos[i] = (yyvsp[-1].ast)->filhos[i];
        filhos[n-1] = (yyvsp[0].ast);
        AST* novo = ast_cria(AST_BLOCO, NULL, 0);
        novo->n_filhos = n;
        novo->filhos = filhos;
        (yyval.ast) = novo;
    }
#line 1347 "build/y.tab.c"
    break;

  case 12: /* $@1: %empty  */
#line 127 "src/yacc.y"
    {
        escopo_atual++; // Entra em novo escopo
    }
#line 1355 "build/y.tab.c"
    break;

  case 13: /* bloco: $@1 bloco_conteudo  */
#line 131 "src/yacc.y"
    {
        escopo_atual--; // Sai do escopo ao final do bloco
        (yyval.ast) = (yyvsp[0].ast);
    }
#line 1364 "build/y.tab.c"
    break;

  case 14: /* bloco_conteudo: comando  */
#line 138 "src/yacc.y"
            { (yyval.ast) = ast_cria(AST_BLOCO, NULL, 1, (yyvsp[0].ast)); }
#line 1370 "build/y.tab.c"
    break;

  case 15: /* bloco_conteudo: bloco_conteudo comando  */
#line 139 "src/yacc.y"
                             {
        if (!(yyvsp[0].ast)) {
            fprintf(stderr, "[ERRO] Comando nulo em bloco!\n");
            (yyval.ast) = (yyvsp[-1].ast);
        } else {
            int n = (yyvsp[-1].ast)->n_filhos + 1;
            AST** filhos = malloc(sizeof(AST*) * n);
            for (int i = 0; i < (yyvsp[-1].ast)->n_filhos; i++) filhos[i] = (yyvsp[-1].ast)->filhos[i];
            filhos[n-1] = (yyvsp[0].ast);
            AST* novo_bloco = ast_cria(AST_BLOCO, NULL, 0);
            novo_bloco->n_filhos = n;
            novo_bloco->filhos = filhos;
            (yyval.ast) = novo_bloco;
        }
    }
#line 1390 "build/y.tab.c"
    break;

  case 16: /* comando: declaracao  */
#line 156 "src/yacc.y"
               { (yyval.ast) = (yyvsp[0].ast); }
#line 1396 "build/y.tab.c"
    break;

  case 17: /* comando: leitura  */
#line 157 "src/yacc.y"
              { (yyval.ast) = (yyvsp[0].ast); }
#line 1402 "build/y.tab.c"
    break;

  case 18: /* comando: escrita  */
#line 158 "src/yacc.y"
              { (yyval.ast) = (yyvsp[0].ast); }
#line 1408 "build/y.tab.c"
    break;

  case 19: /* comando: atribuicao  */
#line 159 "src/yacc.y"
                 { (yyval.ast) = (yyvsp[0].ast); }
#line 1414 "build/y.tab.c"
    break;

  case 20: /* comando: comentario  */
#line 160 "src/yacc.y"
                 { (yyval.ast) = (yyvsp[0].ast); }
#line 1420 "build/y.tab.c"
    break;

  case 21: /* comando: SE expressao ENTAO bloco SENAO comando FIMSE  */
#line 161 "src/yacc.y"
                                                   {
        (yyval.ast) = ast_cria(AST_IF, NULL, 3, (yyvsp[-5].ast), (yyvsp[-3].ast), (yyvsp[-1].ast));
    }
#line 1428 "build/y.tab.c"
    break;

  case 22: /* comando: SE expressao ENTAO bloco FIMSE  */
#line 164 "src/yacc.y"
                                     {
        (yyval.ast) = ast_cria(AST_IF, NULL, 2, (yyvsp[-3].ast), (yyvsp[-1].ast));
    }
#line 1436 "build/y.tab.c"
    break;

  case 23: /* comando: ENQUANTO expressao FACA bloco FIMENQUANTO  */
#line 167 "src/yacc.y"
                                                {
        (yyval.ast) = ast_cria(AST_WHILE, NULL, 2, (yyvsp[-3].ast), (yyvsp[-1].ast));
    }
#line 1444 "build/y.tab.c"
    break;

  case 24: /* comando: PARA ID DE expressao ATE expressao FACA bloco FIMPARA  */
#line 170 "src/yacc.y"
                                                            {
        AST* id = ast_cria(AST_ID, strdup((yyvsp[-7].str)), 0);
        (yyval.ast) = ast_cria(AST_FOR, NULL, 4, id, (yyvsp[-5].ast), (yyvsp[-3].ast), (yyvsp[-1].ast));
    }
#line 1453 "build/y.tab.c"
    break;

  case 25: /* comando: RETORNE expressao PONTOEVIRGULA  */
#line 174 "src/yacc.y"
                                      {
        (yyval.ast) = ast_cria(AST_EXPRESSAO, strdup("return"), 1, (yyvsp[-1].ast));
    }
#line 1461 "build/y.tab.c"
    break;

  case 26: /* comando: chamada_funcao PONTOEVIRGULA  */
#line 177 "src/yacc.y"
                                   { (yyval.ast) = (yyvsp[-1].ast); }
#line 1467 "build/y.tab.c"
    break;

  case 27: /* chamada_funcao: ID ABREPAR lista_args FECHAPAR  */
#line 181 "src/yacc.y"
                                   { (yyval.ast) = ast_cria(AST_CHAMADA_FUNCAO, strdup((yyvsp[-3].str)), 1, (yyvsp[-1].ast)); }
#line 1473 "build/y.tab.c"
    break;

  case 28: /* declaracao: VAR DOISPONTOS tipo ID PONTOEVIRGULA  */
#line 185 "src/yacc.y"
                                         {
        inserirSimbolo((yyvsp[-1].str), (yyvsp[-2].inteiro), escopo_atual); // Agora inclui o escopo!
        AST* tipo_no = ast_cria(AST_ID, strdup((yyvsp[-1].str)), 0);
        AST* tipo_tipo = ast_cria(AST_NUM, strdup((yyvsp[-2].inteiro) == TIPO_INT ? "int" : (yyvsp[-2].inteiro) == TIPO_FLOAT ? "float" : "char"), 0);
        (yyval.ast) = ast_cria(AST_DECLARACAO, NULL, 2, tipo_tipo, tipo_no);
    }
#line 1484 "build/y.tab.c"
    break;

  case 29: /* declaracao: tipo ID PONTOEVIRGULA  */
#line 191 "src/yacc.y"
                            {
        inserirSimbolo((yyvsp[-1].str), (yyvsp[-2].inteiro), escopo_atual);
        AST* tipo_no = ast_cria(AST_ID, strdup((yyvsp[-1].str)), 0);
        AST* tipo_tipo = ast_cria(AST_NUM, strdup((yyvsp[-2].inteiro) == TIPO_INT ? "int" : (yyvsp[-2].inteiro) == TIPO_FLOAT ? "float" : "char"), 0);
        (yyval.ast) = ast_cria(AST_DECLARACAO, NULL, 2, tipo_tipo, tipo_no);
    }
#line 1495 "build/y.tab.c"
    break;

  case 30: /* tipo: TIPO_INTEIRO  */
#line 200 "src/yacc.y"
                     { (yyval.inteiro) = TIPO_INT; }
#line 1501 "build/y.tab.c"
    break;

  case 31: /* tipo: TIPO_REAL  */
#line 201 "src/yacc.y"
                     { (yyval.inteiro) = TIPO_FLOAT; }
#line 1507 "build/y.tab.c"
    break;

  case 32: /* tipo: TIPO_CARACTERE  */
#line 202 "src/yacc.y"
                     { (yyval.inteiro) = TIPO_CHAR; }
#line 1513 "build/y.tab.c"
    break;

  case 33: /* tipo: TIPO_LOGICO  */
#line 203 "src/yacc.y"
                     { (yyval.inteiro) = TIPO_BOOL; }
#line 1519 "build/y.tab.c"
    break;

  case 34: /* tipo: TIPO_VAZIO  */
#line 204 "src/yacc.y"
                     { (yyval.inteiro) = TIPO_VOID; }
#line 1525 "build/y.tab.c"
    break;

  case 35: /* leitura: LEIA ABREPAR ID FECHAPAR PONTOEVIRGULA  */
#line 208 "src/yacc.y"
                                           {
        checar_declaracao((yyvsp[-2].str));
        AST* id = ast_cria(AST_ID, strdup((yyvsp[-2].str)), 0);
        (yyval.ast) = ast_cria(AST_LEITURA, NULL, 1, id);
    }
#line 1535 "build/y.tab.c"
    break;

  case 36: /* escrita: ESCREVA ABREPAR ID FECHAPAR PONTOEVIRGULA  */
#line 216 "src/yacc.y"
                                              {
        checar_declaracao((yyvsp[-2].str));
        AST* id = ast_cria(AST_ID, strdup((yyvsp[-2].str)), 0);
        id->tipo_expr = buscar_tipo_variavel((yyvsp[-2].str)); // Propaga o tipo!
        (yyval.ast) = ast_cria(AST_ESCRITA, NULL, 1, id);
    }
#line 1546 "build/y.tab.c"
    break;

  case 37: /* escrita: ESCREVA ABREPAR STRING FECHAPAR PONTOEVIRGULA  */
#line 222 "src/yacc.y"
                                                    {
        AST* str = ast_cria(AST_STRING, strdup((yyvsp[-2].str)), 0);
        (yyval.ast) = ast_cria(AST_ESCRITA, NULL, 1, str);
    }
#line 1555 "build/y.tab.c"
    break;

  case 38: /* escrita: ESCREVA ABREPAR expressao FECHAPAR PONTOEVIRGULA  */
#line 226 "src/yacc.y"
                                                       {
        (yyval.ast) = ast_cria(AST_ESCRITA, NULL, 1, (yyvsp[-2].ast));
    }
#line 1563 "build/y.tab.c"
    break;

  case 39: /* escrita: ESCREVA ABREPAR NUM FECHAPAR PONTOEVIRGULA  */
#line 229 "src/yacc.y"
                                                 {
        AST* num = ast_cria(AST_NUM, strdup((yyvsp[-2].str)), 0);
        (yyval.ast) = ast_cria(AST_ESCRITA, NULL, 1, num);
    }
#line 1572 "build/y.tab.c"
    break;

  case 40: /* atribuicao: ID IGUAL expressao PONTOEVIRGULA  */
#line 236 "src/yacc.y"
                                     {
        checar_declaracao((yyvsp[-3].str));
        AST* id = ast_cria(AST_ID, strdup((yyvsp[-3].str)), 0);
        (yyval.ast) = ast_cria(AST_ATRIBUICAO, NULL, 2, id, (yyvsp[-1].ast));
    }
#line 1582 "build/y.tab.c"
    break;

  case 41: /* expressao: NUM  */
#line 244 "src/yacc.y"
        {
        AST* num = ast_cria(AST_NUM, strdup((yyvsp[0].str)), 0);
        num->tipo_expr = TIPO_INT; // ou TIPO_FLOAT se detectar ponto
        (yyval.ast) = num;
    }
#line 1592 "build/y.tab.c"
    break;

  case 42: /* expressao: ID  */
#line 249 "src/yacc.y"
         {
        checar_declaracao((yyvsp[0].str));
        AST* id = ast_cria(AST_ID, strdup((yyvsp[0].str)), 0);
        id->tipo_expr = buscar_tipo_variavel((yyvsp[0].str));
        (yyval.ast) = id;
    }
#line 1603 "build/y.tab.c"
    break;

  case 43: /* expressao: expressao SOMA expressao  */
#line 255 "src/yacc.y"
                               {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup("+"), 2, (yyvsp[-2].ast), (yyvsp[0].ast));
        novo->tipo_expr = ((yyvsp[-2].ast)->tipo_expr == TIPO_FLOAT || (yyvsp[0].ast)->tipo_expr == TIPO_FLOAT) ? TIPO_FLOAT : TIPO_INT;
        (yyval.ast) = novo;
    }
#line 1613 "build/y.tab.c"
    break;

  case 44: /* expressao: expressao SUB expressao  */
#line 260 "src/yacc.y"
                              {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup("-"), 2, (yyvsp[-2].ast), (yyvsp[0].ast));
        novo->tipo_expr = ((yyvsp[-2].ast)->tipo_expr == TIPO_FLOAT || (yyvsp[0].ast)->tipo_expr == TIPO_FLOAT) ? TIPO_FLOAT : TIPO_INT;
        (yyval.ast) = novo;
    }
#line 1623 "build/y.tab.c"
    break;

  case 45: /* expressao: expressao COMPARA expressao  */
#line 265 "src/yacc.y"
                                  {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup("=="), 2, (yyvsp[-2].ast), (yyvsp[0].ast));
        novo->tipo_expr = TIPO_BOOL;
        (yyval.ast) = novo;
    }
#line 1633 "build/y.tab.c"
    break;

  case 46: /* expressao: expressao MENOR expressao  */
#line 270 "src/yacc.y"
                                {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup("<"), 2, (yyvsp[-2].ast), (yyvsp[0].ast));
        novo->tipo_expr = TIPO_BOOL;
        (yyval.ast) = novo;
    }
#line 1643 "build/y.tab.c"
    break;

  case 47: /* expressao: expressao MAIOR expressao  */
#line 275 "src/yacc.y"
                                {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup(">"), 2, (yyvsp[-2].ast), (yyvsp[0].ast));
        novo->tipo_expr = TIPO_BOOL;
        (yyval.ast) = novo;
    }
#line 1653 "build/y.tab.c"
    break;

  case 48: /* expressao: expressao MENOR_IGUAL expressao  */
#line 280 "src/yacc.y"
                                      {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup("<="), 2, (yyvsp[-2].ast), (yyvsp[0].ast));
        novo->tipo_expr = TIPO_BOOL;
        (yyval.ast) = novo;
    }
#line 1663 "build/y.tab.c"
    break;

  case 49: /* expressao: expressao MAIOR_IGUAL expressao  */
#line 285 "src/yacc.y"
                                      {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup(">="), 2, (yyvsp[-2].ast), (yyvsp[0].ast));
        novo->tipo_expr = TIPO_BOOL;
        (yyval.ast) = novo;
    }
#line 1673 "build/y.tab.c"
    break;

  case 50: /* expressao: expressao DIFERENTE expressao  */
#line 290 "src/yacc.y"
                                    {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup("!="), 2, (yyvsp[-2].ast), (yyvsp[0].ast));
        novo->tipo_expr = TIPO_BOOL;
        (yyval.ast) = novo;
    }
#line 1683 "build/y.tab.c"
    break;

  case 51: /* expressao: ID ABREPAR lista_args FECHAPAR  */
#line 295 "src/yacc.y"
                                     {
        Simbolo *func = buscarSimbolo((yyvsp[-3].str), 0);
        if (!func) {
            fprintf(stderr, "[ERRO SEMÂNTICO] Função '%s' não declarada!\n", (yyvsp[-3].str));
            exit(1);
        }
        if (func->n_parametros != (yyvsp[-1].ast)->n_filhos) {
            fprintf(stderr, "[ERRO SEMÂNTICO] Função '%s' espera %d parâmetros, mas recebeu %d.\n", (yyvsp[-3].str), func->n_parametros, (yyvsp[-1].ast)->n_filhos);
            exit(1);
        }
        for (int i = 0; i < func->n_parametros; i++) {
            int tipo_esperado = func->parametros[i]->tipo;
            int tipo_recebido = (yyvsp[-1].ast)->filhos[i]->tipo_expr;
            if (tipo_esperado != tipo_recebido) {
                fprintf(stderr, "[ERRO SEMÂNTICO] Parâmetro %d da função '%s' espera tipo %d, mas recebeu tipo %d.\n", i+1, (yyvsp[-3].str), tipo_esperado, tipo_recebido);
                exit(1);
            }
        }
        AST* id = ast_cria(AST_ID, strdup((yyvsp[-3].str)), 0);
        AST* call = ast_cria(AST_EXPRESSAO, NULL, 2, id, (yyvsp[-1].ast));
        call->tipo_expr = func->tipo_retorno;
        (yyval.ast) = call;
    }
#line 1711 "build/y.tab.c"
    break;

  case 52: /* expressao: expressao MUL expressao  */
#line 318 "src/yacc.y"
                              {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup("*"), 2, (yyvsp[-2].ast), (yyvsp[0].ast));
        novo->tipo_expr = ((yyvsp[-2].ast)->tipo_expr == TIPO_FLOAT || (yyvsp[0].ast)->tipo_expr == TIPO_FLOAT) ? TIPO_FLOAT : TIPO_INT;
        (yyval.ast) = novo;
    }
#line 1721 "build/y.tab.c"
    break;

  case 53: /* expressao: expressao DIV expressao  */
#line 323 "src/yacc.y"
                              {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup("/"), 2, (yyvsp[-2].ast), (yyvsp[0].ast));
        novo->tipo_expr = TIPO_FLOAT; // divisão sempre resulta em float
        (yyval.ast) = novo;
    }
#line 1731 "build/y.tab.c"
    break;

  case 54: /* lista_parametros: %empty  */
#line 331 "src/yacc.y"
                { (yyval.ast) = ast_cria(AST_BLOCO, NULL, 0); }
#line 1737 "build/y.tab.c"
    break;

  case 55: /* lista_parametros: parametros  */
#line 332 "src/yacc.y"
                 { (yyval.ast) = (yyvsp[0].ast); }
#line 1743 "build/y.tab.c"
    break;

  case 56: /* parametros: parametro  */
#line 336 "src/yacc.y"
              { (yyval.ast) = ast_cria(AST_BLOCO, NULL, 1, (yyvsp[0].ast)); }
#line 1749 "build/y.tab.c"
    break;

  case 57: /* parametros: parametros VIRGULA parametro  */
#line 337 "src/yacc.y"
                                   {
        int n = (yyvsp[-2].ast)->n_filhos + 1;
        AST** filhos = malloc(sizeof(AST*) * n);
        for (int i = 0; i < (yyvsp[-2].ast)->n_filhos; i++) filhos[i] = (yyvsp[-2].ast)->filhos[i];
        filhos[n-1] = (yyvsp[0].ast);
        AST* novo = ast_cria(AST_BLOCO, NULL, 0);
        novo->n_filhos = n;
        novo->filhos = filhos;
        (yyval.ast) = novo;
    }
#line 1764 "build/y.tab.c"
    break;

  case 58: /* parametro: tipo ID  */
#line 350 "src/yacc.y"
            { inserirParametro((yyvsp[0].str), (yyvsp[-1].inteiro), escopo_atual, 0); (yyval.ast) = ast_cria(AST_DECLARACAO, strdup((yyvsp[0].str)), 0); }
#line 1770 "build/y.tab.c"
    break;

  case 59: /* parametro: tipo '&' ID  */
#line 351 "src/yacc.y"
                  { inserirParametro((yyvsp[0].str), (yyvsp[-2].inteiro), escopo_atual, 1); (yyval.ast) = ast_cria(AST_DECLARACAO, strdup((yyvsp[0].str)), 0); }
#line 1776 "build/y.tab.c"
    break;

  case 60: /* comentario: COMENTARIO_LINHA  */
#line 355 "src/yacc.y"
                     { (yyval.ast) = ast_cria(AST_COMENTARIO, strdup((yyvsp[0].str)), 0); }
#line 1782 "build/y.tab.c"
    break;

  case 61: /* comentario: COMENTARIO_BLOCO  */
#line 356 "src/yacc.y"
                       { (yyval.ast) = ast_cria(AST_COMENTARIO, strdup((yyvsp[0].str)), 0); }
#line 1788 "build/y.tab.c"
    break;


#line 1792 "build/y.tab.c"

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

#line 359 "src/yacc.y"


void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);
}
