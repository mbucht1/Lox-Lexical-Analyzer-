#ifndef SCANNER_H
#define SCANNER_H
#include "token.h"
#include "hashmap.h"
#include <stdbool.h>


typedef struct scan{
    int start;
    int current;
    int line;
    const char* source;
    int length;
    
    
    int cap;
    int size;
    int pointer;
    Token *tokens;
    Map *hashtable[100];

}Scanner;

void string(Scanner *scanner);
bool match(char expected, Scanner *scanner);
bool isAtEnd(Scanner *scanner);
Token *scan(Scanner *scanner);
Scanner* initScanner(char *src, int len);
void addToken(TokenType type, Scanner *scanner);
void addTokens(TokenType type, void* literal, Scanner *scanner);
void number(Scanner *scanner);
char peek(Scanner *scanner);
char peekNext(Scanner *scanner);
char *subString(const char *source, int pos1, int pos2);
bool isDigit(char c);
bool isAlpha(char c);
char advance(Scanner *scanner);
void scanToken(Scanner *scanner);
void identifier(Scanner *scanner);

#endif