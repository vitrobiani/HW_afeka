%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int yylex(void);
void yyerror(const char *s);
extern int yyparse(void);
extern FILE *yyin;

int is_before_noon(const char *time);
#define TRUE 1
#define FALSE 0
%}

%union {
    char* str;
    int int_val;
    struct {
	    int before_noon;
	    int after_noon;
	} counters;;
}

%token <str> FLIGHT_NUMBER TIME AIRPORT
%token CARGO FREIGHT DEPARTURES

%type <counters> flights_list flight
%type <int_val> optional_cargo

%%

input:
    DEPARTURES flights_list {
        printf("number of flights before noon: %d\n", $2.before_noon);
        printf("number of flights after noon: %d\n", $2.after_noon);
    }
;

flights_list:
    flights_list flight {
        $$.before_noon = $1.before_noon + $2.before_noon;
        $$.after_noon = $1.after_noon + $2.after_noon;
    }
    |
    /* empty */ {
        $$.before_noon = 0;
        $$.after_noon = 0;
    }
;

flight:
    FLIGHT_NUMBER TIME AIRPORT optional_cargo {
        if ($4 == 0) {
            if (is_before_noon($2)) {
                $$.before_noon = 1;
                $$.after_noon = 0;
            } else {
                $$.before_noon = 0;
                $$.after_noon = 1;
            }
        } else {
            printf("%s\n", $1);
            $$.before_noon = 0;
            $$.after_noon = 0;
        }
    }
;

optional_cargo:
    CARGO { $$ = 1; }
    | FREIGHT { $$ = 1; }
    | /* empty */ { $$ = 0; }
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int is_before_noon(const char *time) {
    int hour, minute;
    char suffix[6] = "";

    if (strstr(time, "a.m.") || strstr(time, "p.m.")) {
        sscanf(time, "%d:%d%5s", &hour, &minute, suffix);
        for (int i = 0; suffix[i]; ++i) suffix[i] = tolower(suffix[i]);
        if (strstr(suffix, "a.m.")) return TRUE;
        else return FALSE;
    } else {
        sscanf(time, "%d:%d", &hour, &minute);
        if (hour < 12) return TRUE;
        else return FALSE;
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror("Failed to open file");
            return EXIT_FAILURE;
        }
    } else {
        yyin = stdin;
    }

    if (yyparse() != 0) {
        fprintf(stderr, "Parsing failed.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
