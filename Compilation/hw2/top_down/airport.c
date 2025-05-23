#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airport.h"

static void advance(ParserContext *ctx) {
    ctx->token = yylex();
    strcpy(ctx->text, yylval.name);
}

static int is_time_before_noon(const char *time_str) {
    int hour, min;
    char suffix[10] = "";

    if (strstr(time_str, "a.m.") || strstr(time_str, "p.m.")) {
        sscanf(time_str, "%d:%d%[^ ]", &hour, &min, suffix);
        if (strstr(suffix, "a.m.")) return 1;
        if (strstr(suffix, "p.m.")) return 0;
    } else {
        sscanf(time_str, "%d:%d", &hour, &min);
        int total = hour * 60 + min;
        return total < 12 * 60;
    }
    return 0;
}

static void match(ParserContext *ctx, int expected_token) {
    if (ctx->token != expected_token) {
        fprintf(stderr, "Unexpected token: %s\n", ctx->text);
        exit(1);
    }
    advance(ctx);
}

static void parse_optional_cargo(ParserContext *ctx, int *is_cargo) {
    if (ctx->token == CARGO || ctx->token == FREIGHT) {
        *is_cargo = 1;
        advance(ctx);
    }
}

static void parse_flight(ParserContext *ctx) {
    char flight_number[80], time[80];
    int is_cargo = 0;

    strcpy(flight_number, ctx->text);
    match(ctx, FLIGHT_NUMBER);

    strcpy(time, ctx->text);
    match(ctx, TIME);

    match(ctx, AIRPORT);
    parse_optional_cargo(ctx, &is_cargo);

    if (is_cargo) {
        printf("%s\n", flight_number);
    } else {
        if (is_time_before_noon(time)) {
            ctx->flights_before_noon++;
        } else {
            ctx->flights_after_noon++;
        }
    }
}

static void parse_flights_list(ParserContext *ctx) {
    while (ctx->token == FLIGHT_NUMBER) {
        parse_flight(ctx);
    }
}

void parse(ParserContext *ctx) {
    advance(ctx); // first token
    match(ctx, DEPARTURES);
    parse_flights_list(ctx);

    printf("number of flights before noon: %d\n", ctx->flights_before_noon);
    printf("number of flights after noon: %d\n", ctx->flights_after_noon);
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror("Error opening file");
            return 1;
        }
    } else {
        yyin = stdin;
    }

    ParserContext ctx = {0};
    parse(&ctx);

    if (yyin != stdin) {
        fclose(yyin);
    }

    return 0;
}
