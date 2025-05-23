#ifndef AIRPORT_H
#define AIRPORT_H

#define DEPARTURES 300
#define FLIGHT_NUMBER 301
#define TIME 302
#define AIRPORT 303
#define CARGO 304
#define FREIGHT 305

typedef struct {
    int flights_before_noon;
    int flights_after_noon;
    int token;
    char text[80];
} ParserContext;

int yylex(void);

typedef union YYSTYPE {
    int ival;
    char name[30];
    char str[80];
} YYSTYPE;

extern YYSTYPE yylval;

extern FILE *yyin;

void parse(ParserContext *ctx);

#endif // AIRPORT_H

