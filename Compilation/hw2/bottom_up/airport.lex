%{
#include "airport.tab.h"
#include <string.h>
#include <stdlib.h>

int line = 1;

#define YY_DECL int yylex(void)

extern YYSTYPE yylval;

%}

%option noyywrap
%option yylineno

%%

"<departures>"					{ return DEPARTURES; }
[A-Z][A-Z][0-9]{1,4}			 	{ yylval.str = strdup(yytext); return FLIGHT_NUMBER; }
"0"[0-9]+":"[0-5]+[0-9]+"a.m."			{ yylval.str = strdup(yytext); return TIME; }
"1"[0-2]+":"[0-5]+[0-9]+"a.m."			{ yylval.str = strdup(yytext); return TIME; }
"0"[0-9]+":"[0-5]+[0-9]+"p.m."			{ yylval.str = strdup(yytext); return TIME; }
"1"[0-2]+":"[0-5]+[0-9]+"p.m."			{ yylval.str = strdup(yytext); return TIME; }
[0-1]+[0-9]+":"[0-5]+[0-9]+			{ yylval.str = strdup(yytext); return TIME; }
"2"[0-3]+":"[0-5]+[0-9]+			{ yylval.str = strdup(yytext); return TIME; }
"["([a-z]*[A-Z]*" "*)*"]"       		{ return AIRPORT; }
"cargo"						{ return CARGO; }
"freight"					{ return FREIGHT; }


[\t\r ]+          {}
\n              { line++; }

.          { fprintf (stderr, "line %d: unrecognized token %c(%x)\n", 
                               line, yytext[0], yytext[0]); }

%%


