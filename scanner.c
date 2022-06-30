#include "scanner.h"
#include "token.h"
#include "hashmap.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

Token *scan(Scanner *scanner){
    put(scanner->hashtable, "and", AND);
    put(scanner->hashtable, "class", CLASS);
    put(scanner->hashtable, "else", ELSE);
    put(scanner->hashtable, "false", FALSE);
    put(scanner->hashtable, "for", FOR);
    put(scanner->hashtable, "fun", FUN);
    put(scanner->hashtable, "if", IF);
    put(scanner->hashtable, "nil", NIL);
    put(scanner->hashtable, "or", OR);
    put(scanner->hashtable, "print", PRINT);
    put(scanner->hashtable, "return", RETURN);
    put(scanner->hashtable, "super", SUPER);
    put(scanner->hashtable, "this", THIS);
    put(scanner->hashtable, "true", TRUE);
    put(scanner->hashtable, "var", VAR);
    put(scanner->hashtable, "while", WHILE);
    
    while(!isAtEnd(scanner)){
        scanner->start = scanner->current;
        scanToken(scanner);
    }
    scanner->tokens[scanner->pointer].type = ENDOF;
    scanner->tokens[scanner->pointer].lexeme = "";
    scanner->tokens[scanner->pointer].literal = NULL;
    scanner->tokens[scanner->pointer].line = scanner->line;
    scanner->pointer++;
    return scanner->tokens;
}


Scanner *initScanner(char *src, int len){
    Scanner *s = (Scanner *)malloc(sizeof(Scanner));
    s->start = 0;
    s->current = 0;
    s->line = 1;
    s->source = src;
    s->length = len;
    s->cap = len;
    s->size = len;
    s->pointer = 0;
    s->tokens = (Token *)malloc(len * sizeof(Token));
    initTable(s->hashtable);
    return s;
}

void scanToken(Scanner *scanner){
    char c = advance(scanner);
    switch(c){
        case '(': addToken(LEFT_PAREN, scanner); break;
        case ')': addToken(RIGHT_PAREN, scanner); break;
        case '{': addToken(LEFT_BRACE, scanner); break;
        case '}': addToken(RIGHT_BRACE, scanner); break;
        case ',': addToken(COMMA, scanner); break;
        case '.': addToken(DOT, scanner); break;
        case '-': addToken(MINUS, scanner); break;
        case '+': addToken(PLUS, scanner); break;
        case ';': addToken(SEMICOLON, scanner); break;
        case '*': addToken(STAR, scanner); break;
        case '!': addToken(match('=', scanner) ? BANG_EQUAL : BANG, scanner); break;
        case '=': addToken(match('=', scanner) ? EQUAL_EQUAL : BANG, scanner); break;
        case '<': addToken(match('=', scanner) ? LESS_EQUAL : LESS, scanner); break;
        case '>': addToken(match('=', scanner) ? GREATER_EQUAL : GREATER, scanner); break;
        case '/':
            if(match('/', scanner)){
                while(peek(scanner) != '\n' && !isAtEnd(scanner)) advance(scanner);
            }
            else{
                addToken(SLASH, scanner);
            }
            break;
        case ' ':
        case '\t':
            break;
        case '\r':
        case '\n':
            scanner->line++;
            break;
        case '"': string(scanner); break;
        default:
            if(isDigit(c)){
                number(scanner);
            }
            else if(isAlpha(c)){
                identifier(scanner);
            }
            else{
                printf("Line %d. Unexpected error", scanner->line);
            }
            break;
    }
}

bool isAlphaNumeric(char c){    
    return isAlpha(c) || isDigit(c);
}


void identifier(Scanner *scanner){
    while(isAlphaNumeric(peek(scanner))) advance(scanner);
    char *text = subString(scanner->source, scanner->start, scanner->current);
    TokenType type = get(scanner->hashtable, text);
    if(type == -1) type = IDENTIFIER;
    addToken(type, scanner);
}

bool match(char expected, Scanner *scanner){
    if(isAtEnd(scanner)) return false;
    if(scanner->source[scanner->current] != expected) return false;
    scanner->current++;
    return true;
}

bool isAtEnd(Scanner *scanner){
    return scanner->current >= scanner->length;
}

void number(Scanner *scanner){
    while(isDigit(peek(scanner))) advance(scanner);

    if(peek(scanner) == '.' && isDigit(peekNext(scanner))){
        advance(scanner);
        while(isDigit(peek(scanner))) advance(scanner);
    }

    char *value = subString(scanner->source, scanner->start, scanner->current);
    
    addTokens(NUMBER, (void*)value, scanner);
}


void string(Scanner *scanner){
    while(peek(scanner) != '"' && !isAtEnd(scanner)){
        if(peek(scanner) == '\n') scanner->line++;
        advance(scanner);
    }
    if(isAtEnd(scanner)){
        printf("Unterminated String\n");
        return;
    }
    advance(scanner);
    char *value = subString(scanner->source, scanner->start + 1, scanner->current - 1);
    addTokens(STRING, (void*)value, scanner);
}

char peek(Scanner *scanner){
    if(isAtEnd(scanner)) return '\0';
    return scanner->source[scanner->current];
}

char peekNext(Scanner *scanner){
    if(scanner->current + 1 >= scanner->length) return '\0';
    return scanner->source[scanner->current + 1];
}

void addToken(TokenType type, Scanner *scanner){
    addTokens(type, NULL, scanner);
}

void addTokens(TokenType type, void* literal, Scanner *scanner){
    char *text = subString(scanner->source, scanner->start, scanner->current);
    //printf("%s", text);
    scanner->tokens[scanner->pointer].type = type;
    scanner->tokens[scanner->pointer].lexeme = text;
    scanner->tokens[scanner->pointer].literal = literal;
    scanner->tokens[scanner->pointer].line = scanner->line;


    //printf("%s", scanner->tokens[0].lexeme);
    scanner->pointer++;
}

char *subString(const char *source, int pos1, int pos2){

    //printf("source: %s\n", source);
    char *temp = malloc( (pos2 - pos1) * sizeof(char));
    int i = 0;
    int j = 0;
    for(j = pos1; j < pos2; j++){
        temp[i] = source[j];
        i++;
    }
    temp[i] = '\0';
    //printf("temp: %s\n", temp);
    return temp;
}


bool isDigit(char c){
    return c >= '0' && c <= '9';
}

bool isAlpha(char c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

char advance(Scanner *scanner){
    return scanner->source[scanner->current++];
}


