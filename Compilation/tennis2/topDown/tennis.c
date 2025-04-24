/*
           A recursive descent parser for exercise 2 (tennis champions)      
           
		   Note: the original grammar was not LL(1) because of the 
		   following productions that have left recursion: 		

           list_of_players: list_of_players player

		   list_of_years: list_of_years COMMA year_spec

           the following productions also make the grammar non LL(1):
		   
		   year_spec: YEAR | YEAR HYPHEN YEAR
		   
		   but these problems can easily be handled. See below
		   the functions list_of_players(), list_of_years() and
		   year_spec().
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tennis.h"
 
extern enum token yylex (void);
enum token lookahead;

struct player {
    char name[NAME_SIZE];
	int wins; // number of wins  at wimbledon
    enum gender gender;	
};

struct max_winner {
    char name[NAME_SIZE]; // name of woman with max wins at wimbledon 
	int wins; // number of wins of that woman at wimbledon 
	          //  if there are no women in the list then wins==0
};


// the recursive descent parser
void start();
struct max_winner list_of_players();

struct player player();

int optional_wimbledon();
void optional_australian_open();
void optional_french_open();

int list_of_years();
int year_spec();

void match(enum token expectedToken)
{
    if (lookahead == expectedToken)
        lookahead = yylex();
    else {
        char e[100]; 
        sprintf(e, "error: expected token %s, found token %s", 
                token_name(expectedToken), token_name(lookahead));
        errorMsg(e);
        exit(1);
    }
}

void parse()
{
    lookahead = yylex();
    start();
    if (lookahead != 0) {  // 0 means EOF
        errorMsg("EOF expected");
        exit(1);
    }
}

void 
start()
{
	//  start -> TITLE  list_of_players
    match(TITLE);
    struct max_winner mw = list_of_players();
    if (mw.wins == 0) 
        printf ("no woman won at wimbledon\n");
    else
        printf ("woman with greatest number of wins at Wimbledon: %s (%d wins)\n",
                mw.name, mw.wins);
}

/* we allow  an empty list.
   returns name and number of wins for woman in the list of players
   with the greatest number of wins in wimbledon.
   If there is no woman in the list that won at wimbledon
   then number of wins will be zero
*/   
struct max_winner
list_of_players()
{
	struct player p;
    struct max_winner mw = {"nobody", 0};
    while (lookahead == NAME) {
	    p = player(); 
		if (p.gender == WOMAN && p.wins > mw.wins) {
			strcpy(mw.name, p.name);
			mw.wins = p.wins;
		}
    }
    return mw;
}

struct player
player() 
{
	// player -> NAME PLAYER_NAME GENDER optional_wimbledon optional_australian_open optional_french_open
	struct player p;
    match(NAME);
	/* 
	   The order is important here: first read PLAYER_NAME's semantic
	   value  (from the global variable lexicalValue) and then
	   match(PLAYER_NAME). If we match first we may lose the semantic 
       value when match() calls yylex() which writes 'lexicalValue'.	   
    */	   
	if (lookahead == PLAYER_NAME)
		strcpy(p.name, lexicalValue.name);
	match(PLAYER_NAME);
	
	if (lookahead == GENDER)
		p.gender = lexicalValue.gender;
	match(GENDER);
	
	p.wins = optional_wimbledon();
	optional_australian_open();
    optional_french_open();

	return p;
}

// returns number of years in list of years for wimbledon
int optional_wimbledon() {
	if (lookahead != WIMBLEDON)
		return 0;
	match(WIMBLEDON);
	return list_of_years();
}

void optional_australian_open() {
	if (lookahead != AUSTRALIAN_OPEN)
		return;
	match(AUSTRALIAN_OPEN);
	list_of_years();
}

void optional_french_open() {
	if (lookahead != FRENCH_OPEN)
		return;
	match(FRENCH_OPEN);
	list_of_years();
}

/* returns number of years in the list */
int list_of_years() {
	int count = year_spec();
	while (lookahead == COMMA) {
		match(COMMA);
		count += year_spec();
	}
	return count;
}

int year_spec() {
	int year1, year2;
    if (lookahead == YEAR)
		year1 = lexicalValue.year;
    match(YEAR);
    if (lookahead != HYPHEN) 
	    return 1;  // one year;
	else {
		match(HYPHEN);
		if (lookahead == YEAR)
		    year2 = lexicalValue.year;
		match(YEAR);
		return year2-year1+1;
	}
}

int
main (int argc, char **argv)
{
    extern FILE *yyin; // defined by flex
    if (argc != 2) {
       fprintf (stderr, "Usage: %s <input-file-name>\n", argv[0]);
	   return 1;
    }
    yyin = fopen (argv [1], "r");
    if (yyin == NULL) {
       fprintf (stderr, "failed to open %s\n", argv[1]);
	   return 2;
    }
  
    parse();
  
    fclose (yyin);
    return 0;
}

void errorMsg(const char *s)
{
  extern int yylineno; // defined by flex
  fprintf (stderr, "line %d: %s\n", yylineno, s);
}
