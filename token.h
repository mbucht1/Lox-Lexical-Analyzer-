#ifndef TOKEN_H
#define TOKEN_H

enum types {
    //Single-character tokens
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,
    //One or two character tokens
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,
    //Literals
    IDENTIFIER, STRING, NUMBER,
    //Keywords
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE, ENDOF};

typedef enum types TokenType;

typedef struct token{
    TokenType type;
    char *lexeme;
    void *literal;
    int line;
}Token;

char *toString(TokenType type);




#endif