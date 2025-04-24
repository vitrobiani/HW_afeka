#ifndef TENNIS

// yylex returns 0 when EOF is encountered
enum token {
     TITLE = 1, 
     NAME,
     GENDER,
	 WIMBLEDON,
     AUSTRALIAN_OPEN, 
     FRENCH_OPEN,
     YEAR,
     PLAYER_NAME,
	 HYPHEN,
     COMMA  
};

char *token_name(enum token token);

enum gender { MAN, WOMAN};

#define NAME_SIZE 30

// semantic values for tokens
union _lexVal{
    char name[NAME_SIZE]; // semantic value for PLAYER_NAME
    enum gender gender; // semantic value for GENDER
	int year;  // semantic value for YEAR 
};

extern union _lexVal lexicalValue;// like yylval when we use bison

void errorMsg(const char *s);

#endif
