%{
/*
 * lexer.l -- WS Lenguaje
 * Lexical analyzer.
 * Variable syntax: name type => value;
 */
#include "parser.tab.h"
#include "symbols.h"
%}
%option nounput
%option noinput
%option yylineno
DIGIT   [0-9]
LETTER  [a-zA-Z_]
ID      {LETTER}({LETTER}|{DIGIT})*
WS      [ \t\r]+
STRING  \"(\\.|[^"\\])*\"
%%
{WS}                          { /* ignore whitespace */ }
\n                            { /* newline counted by yylineno */ }
"//"[^\n]*                    { /* single-line comment */ }
"/*"([^*]|\*+[^*/])*\*+"/"   { /* multi-line comment  */ }
"print"    { return PRINT;        }
"func"     { return FUNCTION;    }
"function" { return FUNCTION;    }
"return"   { return RETURN;      }
"if"       { return IF;          }
"else"     { return ELSE;        }
"while"    { return WHILE;       }
"int"      { return INT_TYPE;    }
"double"   { return DOUBLE_TYPE; }
"char"     { return CHAR_TYPE;   }
"string"   { return STRING_TYPE; }
"boolean"  { return BOOL_TYPE;   }
"=>"  { return ARROW;     }
"=="  { return EQ;        }
"!="  { return NE;        }
"<="  { return LE;        }
">="  { return GE;        }
"&&"  { return AND;       }
"||"  { return OR;        }
"="   { return EQUALS;    }
"<"   { return LT;        }
">"   { return GT;        }
"!"   { return NOT;       }
"+"   { return PLUS;      }
"-"   { return SUB;       }
"*"   { return MUL;       }
"/"   { return DIV;       }
"("   { return LPARENT;   }
")"   { return RPARENT;   }
"{"   { return LBRACE;    }
"}"   { return RBRACE;    }
";"   { return SEMICOLON; }
","   { return COMMA;     }
"true"  { yylval.b_val = 1; return BOOL_LITERAL; }
"false" { yylval.b_val = 0; return BOOL_LITERAL; }
"'"."'" { yylval.c_val = yytext[1]; return CHAR_LITERAL; }
{DIGIT}+ {
    yylval.d_val = atof(yytext);
    return NUMBER;
}
{DIGIT}*\.{DIGIT}+|{DIGIT}+\. {
    yylval.d_val = atof(yytext);
    return DOUBLE_LITERAL;
}
{STRING} {
    yylval.s_val = strndup(yytext + 1, strlen(yytext) - 2);
    return STRING_LITERAL;
}
{ID} {
    yylval.s_val = strdup(yytext);
    return IDENTIFIER;
}
%%
int yywrap() {
    return 1;
}
