%{
/*
 * lexer.l -- WS Language v3.0
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
"print"    { return PRINT;       }
"int"      { return INT_TYPE;    }
"double"   { return DOUBLE_TYPE; }
"char"     { return CHAR_TYPE;   }
"string"   { return STRING_TYPE; }
"boolean"  { return BOOL_TYPE;   }
"=>"  { return ARROW;     }
"+"   { return PLUS;      }
"-"   { return SUB;       }
"*"   { return MUL;       }
"/"   { return DIV;       }
"("   { return LPARENT;   }
")"   { return RPARENT;   }
";"   { return SEMICOLON; }
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
    SymbolEntry* node = find_entry(yytext);
    if (node == NULL) {
        node = create_entry(yytext, yylineno);
    }
    yylval.entry = node;
    return IDENTIFIER;
}
%%
int yywrap() {
    return 1;
}
