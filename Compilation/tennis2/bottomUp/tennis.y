%code {
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int yylex(void);
void yyerror (const char *msg);
}

%code requires {
enum gender { MAN, WOMAN };
#define NAME_SIZE 30

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
} /* code requires */

%union {
    char name[NAME_SIZE];
    int year;
	int number_of_years;
	enum gender gender;
	struct player player;
	struct max_winner max_winner;
}

%token TITLE NAME WIMBLEDON AUSTRALIAN_OPEN FRENCH_OPEN
%token <name> PLAYER_NAME
%token <gender> GENDER
%token <year> YEAR

%nterm <player> player
%nterm <max_winner> list_of_players
%nterm <number_of_years> optional_wimbledon
%nterm <number_of_years> list_of_years year_spec

%define parse.error verbose

/* %error-verbose */

%%

input: TITLE list_of_players 
          { if ($2.wins>0) 
	            printf("Woman with most wins at Wimbledon:%s (%d wins)\n",
		               $2.name, $2.wins);
			    else printf("No woman won at wimbledon\n");
		  };

list_of_players: list_of_players player
          { if ($2.gender == WOMAN && $2.wins > $1.wins) {
			    strcpy($$.name, $2.name);
				$$.wins = $2.wins;
			} else
			    $$ = $1;
		  };

list_of_players: player
         { if ($1.gender == WOMAN) {
		       strcpy($$.name, $1.name);
			   $$.wins = $1.wins;
		   } else {
		       strcpy($$.name, "nobody");
			   $$.wins = 0;
		   }
	     };

player: NAME PLAYER_NAME GENDER 
        optional_wimbledon  // $4
		optional_australian_open 
		optional_french_open
		{ strcpy($$.name, $2);
		  $$.gender = $3;
		  $$.wins = $4;
		};
      
optional_wimbledon: WIMBLEDON list_of_years { $$ = $2;} |
                    %empty { $$ = 0; };

optional_australian_open: AUSTRALIAN_OPEN list_of_years |
                    %empty;

optional_french_open: FRENCH_OPEN list_of_years |
                    %empty;
					
list_of_years: list_of_years ',' year_spec { $$ = $1 + $3; };

list_of_years: year_spec { $$ = $1; };

year_spec: YEAR { $$ = 1; } | YEAR '-' YEAR { $$ = $3 - $1 + 1; };

%%
int main (int argc, char **argv)
{
   extern FILE *yyin; // defined by flex
   if (argc != 2) {
      fprintf(stderr, "Usage: %s <input file name>\n", argv [0]);
      exit (1);
   }

   yyin = fopen (argv[1], "r");
   if (yyin == NULL) { fprintf(stderr, "failed to open file %s\n", argv[1]); exit(1);}

   yyparse();
   
   fclose (yyin);
   exit (0);
}

void yyerror (const char *msg){
    extern int yylineno; // defined by flex
	fprintf(stderr, "line %d: %s\n", yylineno, msg);
}

	

