%{
#include <string.h>
#include <stdlib.h> 

#include "tennis.h"

union _lexVal lexicalValue; // semantic value of current token
                            
%}

%option noyywrap
%option yylineno

/* exclusive start condition for handling comments */ 
%x STAR_COMMENT

%%
"** Winners **" { return TITLE; }

"<name>"     { return NAME; }

"<Woman>"      { lexicalValue.gender = WOMAN; return GENDER; }
"<Man>"        { lexicalValue.gender = MAN; return GENDER; }

"<Wimbledon>"       { return WIMBLEDON; }
"<Australian Open>" { return AUSTRALIAN_OPEN; } 
"<French Open>"     { return FRENCH_OPEN; }

[0-9]+ { lexicalValue.year = atoi(yytext); return YEAR; }

["'][A-Z][a-z]*(" "[A-Z][a-z]*)?["']  { // copy name without the surrounding quotes
           strcpy (lexicalValue.name, yytext+1);
           lexicalValue.name[strlen(lexicalValue.name)-1] = '\0';
           return PLAYER_NAME; }
		   
"-"       { return HYPHEN; }
","       { return COMMA; }

[\t\r\n ]+  { /* skip white space */ }

"/*"        { BEGIN(STAR_COMMENT); }
<STAR_COMMENT>.  { /* skip character inside comment */ }
<STAR_COMMENT>"*/" { BEGIN(0); }

"//".*      { /* skip comment starting with "//" */ }

.         { char e[100];
            sprintf(e, "unrecognized token %c(%x)", yytext[0], yytext[0]);  
            errorMsg(e);  
            exit(1);
          }
					  
%%
/* useful for error messages */
char *token_name(enum token token)
{
    static char *names[] = {
		"EOF", "TITLE", "NAME", "GENDER", "WIMBLEDON",
        "AUSTRALIAN_OPEN", "FRENCH_OPEN", "YEAR",
    	"PLAYER_NAME", "HYPHEN", "COMMA" };  
 
    return token <= COMMA ? names[token] : "unknown token";
}


