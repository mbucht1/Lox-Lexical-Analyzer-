#include "hello.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "scanner.h"
#include "token.h"
#include <string.h>
#define N 1000

static bool hadError = false;


void runFile(char *arg){

    char src[N];
    int len = 0;
    FILE *pFile = fopen("variable.txt", "r");
    if(pFile == NULL) return;
    for(int i = 0; !feof(pFile); i++){
        fscanf(pFile, "%c", &src[i]);
        len = i;
    }
    src[len] = '\0';
    Scanner *scanner = initScanner(src, len);
    Token *tokens = scan(scanner);

    
    // for(int i = 0; i < scanner->pointer; i++){
    //     printf("Type: %s\n", toString(scanner->tokens[i].type));
    //     printf("lexeme: %s\n", scanner->tokens[i].lexeme);
    //     printf("literal: %s\n", scanner->tokens[i].literal);
    //     printf("Line: %d\n", scanner->tokens[i].line);
    //     printf("\n");
    // }
}

void runPrompt(){

}


int main(int argc, char **argv){

    if(argc > 2){
        printf("Use: gcc <filepath>");

    }
    else if(argc == 2){
        runFile(argv[1]);
    }
    else runPrompt();
    return 0;
}

