/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_INPUT_TAB_H_INCLUDED
# define YY_YY_INPUT_TAB_H_INCLUDED
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
    LINEINFO = 258,
    TITLE = 259,
    KEYWORD = 260,
    BOOL_PARAMETER = 261,
    REAL_PARAMETER = 262,
    INT_PARAMETER = 263,
    STRING_PARAMETER = 264,
    UD_BOOL_PARAMETER = 265,
    UD_REAL_PARAMETER = 266,
    UD_INT_PARAMETER = 267,
    UD_STRING_PARAMETER = 268,
    INT_TYPE = 269,
    REAL_TYPE = 270,
    BOOL_TYPE = 271,
    STRING_TYPE = 272,
    INT_ID = 273,
    REAL_ID = 274,
    BOOL_ID = 275,
    STRING_ID = 276,
    INT_VALUE = 277,
    REAL_VALUE = 278,
    STRING_VALUE = 279,
    BOOL_VALUE = 280,
    ENDFILE = 281,
    BLANK = 282,
    COMMENT = 283,
    BAD_WORD = 284,
    GE = 285,
    GT = 286,
    LE = 287,
    LT = 288,
    EQ = 289,
    NE = 290,
    NOT = 291,
    OR = 292,
    AND = 293,
    PLUS = 294,
    MINUS = 295,
    ASTERISK = 296,
    DIVIDE = 297,
    MOD = 298,
    LOWEST = 299,
    ELSE = 300,
    UNARYLOW = 301,
    UNARYHIGH = 302,
    LEFTSQUARE = 303,
    LEFTPAREN = 304,
    HIGHEST = 305
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "input.y"

    bool   bval;
    int    ival;
    double dval;
    char   sval[1024];
    std::vector<bool>     * bool_array;
    std::vector<int>      * int_array;
    std::vector<double>   * real_array;
    std::vector<std::string>  * string_array;
    Parser::Parameter * parameter;
    std::vector<Parser::Parameter *> * parameter_array;
    Parser::Card      * card;

#line 122 "input.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void * dummy);

#endif /* !YY_YY_INPUT_TAB_H_INCLUDED  */
