%{
#include "airport.h"
#include <string.h>
#include <stdlib.h>

YYSTYPE yylval;

int line = 1;

extern int atoi (const char *);
%}

%option noyywrap

%option yylineno

%x COMMENT

%%
"<departures>"					{ strcpy(yylval.name, yytext); return DEPARTURES; }
[A-Z][A-Z][0-9]{1,4}			 	{ strcpy(yylval.name, yytext); return FLIGHT_NUMBER; }
"0"[0-9]+":"[0-5]+[0-9]+"a.m."			{ strcpy(yylval.name, yytext); return TIME; }
"1"[0-2]+":"[0-5]+[0-9]+"a.m."			{ strcpy(yylval.name, yytext); return TIME; }
"0"[0-9]+":"[0-5]+[0-9]+"p.m."			{ strcpy(yylval.name, yytext); return TIME; }
"1"[0-2]+":"[0-5]+[0-9]+"p.m."			{ strcpy(yylval.name, yytext); return TIME; }
[0-1]+[0-9]+":"[0-5]+[0-9]+			{ strcpy(yylval.name, yytext); return TIME; }
"2"[0-3]+":"[0-5]+[0-9]+			{ strcpy(yylval.name, yytext); return TIME; }
"["([a-z]*[A-Z]*" "*)*"]"       		{ strcpy(yylval.name, yytext); return AIRPORT; }
"cargo"						{ strcpy(yylval.name, yytext); return CARGO; }
"freight"					{ strcpy(yylval.name, yytext); return FREIGHT; }

"#".*           { BEGIN(COMMENT); }
<COMMENT>\n     { BEGIN(0); line++; }

[\t\r ]+          {}
\n              { line++; }

.          { fprintf (stderr, "line %d: unrecognized token %c(%x)\n", 
                               line, yytext[0], yytext[0]); }


%%

