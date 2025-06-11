/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_BUILD_Y_TAB_H_INCLUDED
# define YY_YY_BUILD_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INICIO = 258,                  /* INICIO  */
    FIM = 259,                     /* FIM  */
    LEIA = 260,                    /* LEIA  */
    ESCREVA = 261,                 /* ESCREVA  */
    VAR = 262,                     /* VAR  */
    TIPO_INTEIRO = 263,            /* TIPO_INTEIRO  */
    TIPO_REAL = 264,               /* TIPO_REAL  */
    TIPO_CARACTERE = 265,          /* TIPO_CARACTERE  */
    TIPO_LOGICO = 266,             /* TIPO_LOGICO  */
    TIPO_VAZIO = 267,              /* TIPO_VAZIO  */
    SE = 268,                      /* SE  */
    SENAO = 269,                   /* SENAO  */
    ENTAO = 270,                   /* ENTAO  */
    FIMSE = 271,                   /* FIMSE  */
    ENQUANTO = 272,                /* ENQUANTO  */
    FACA = 273,                    /* FACA  */
    FIMENQUANTO = 274,             /* FIMENQUANTO  */
    IGUAL = 275,                   /* IGUAL  */
    COMPARA = 276,                 /* COMPARA  */
    DIFERENTE = 277,               /* DIFERENTE  */
    MENOR = 278,                   /* MENOR  */
    MAIOR = 279,                   /* MAIOR  */
    MENOR_IGUAL = 280,             /* MENOR_IGUAL  */
    MAIOR_IGUAL = 281,             /* MAIOR_IGUAL  */
    SOMA = 282,                    /* SOMA  */
    SUB = 283,                     /* SUB  */
    MUL = 284,                     /* MUL  */
    DIV = 285,                     /* DIV  */
    ABREPAR = 286,                 /* ABREPAR  */
    FECHAPAR = 287,                /* FECHAPAR  */
    PONTOEVIRGULA = 288,           /* PONTOEVIRGULA  */
    VIRGULA = 289,                 /* VIRGULA  */
    PARA = 290,                    /* PARA  */
    DE = 291,                      /* DE  */
    ATE = 292,                     /* ATE  */
    FIMPARA = 293,                 /* FIMPARA  */
    DOISPONTOS = 294,              /* DOISPONTOS  */
    FIMFUNCAO = 295,               /* FIMFUNCAO  */
    NUM = 296,                     /* NUM  */
    ID = 297,                      /* ID  */
    STRING = 298,                  /* STRING  */
    FUNCAO = 299,                  /* FUNCAO  */
    RETORNE = 300,                 /* RETORNE  */
    COMENTARIO_LINHA = 301,        /* COMENTARIO_LINHA  */
    COMENTARIO_BLOCO = 302         /* COMENTARIO_BLOCO  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 28 "src/yacc.y"

    char* str;
    int inteiro;
    struct {
        char* valor;
        int tipo;
    } expr;
    struct AST* ast; // novo campo para AST

#line 121 "build/y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_BUILD_Y_TAB_H_INCLUDED  */
