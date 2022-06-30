#include "hashmap.h"
#include "tokentype.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TABLE_SIZE 100


void put(Map *map[], char *K, int V){
    int key = hashfunction(K);
    if(map[key]->value == -1){
        map[key]->key = K;
        map[key]->value = V;
    }
    else{
        Map *elem = malloc(sizeof(Map));
        elem->key = K;
        elem->value = V;
        elem->next = map[key];
        map[key] = elem;
    }
}

void printTable(Map *map[]){
    
    for(int i = 0; i < 100; i++){
        if(map[i]->value == -1) continue;
        printf("%d ", map[i]->value);
        if(map[i]->next != NULL){
            Map *temp;
            for(temp = map[i]; temp != NULL; temp = temp->next){
                printf("%d ", temp->value);
            }
        }
        printf("\n");
    }
    

}

void initTable(Map *map[]){
    for(int i = 0; i < TABLE_SIZE; i++){
        map[i] = malloc(sizeof(Map));
        map[i]->key = "\0";
        map[i]->value = -1;
        map[i]->next = NULL;
    }
}

int hashfunction(char *c){
    
    int x = 0;
    for(char *i = c; *i != '\0'; i++){
        x += *i;
    }
    return x % 15;
}

int get(Map *map[], char *elem){
    //switch() case later
    int key = hashfunction(elem);
    for(Map *e = map[key]; e != NULL; e = e->next){
        if(strcmp(e->key, elem) == 0) return e->value;
    }
    return -1;
}


