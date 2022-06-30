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




// int main(){
    
//     Map *table[TABLE_SIZE];
//     initTable(table);
//     char *a = "and";
//     char *b = "class";
//     char *c = "else";
//     char *d = "false";
//     char *e = "for";
//     char *f = "fun";
//     char *g = "if";
//     char *h = "nil";
//     char *i = "or";
//     char *j = "print";
//     char *k = "return";
//     char *l = "super";
//     char *m = "this";
//     char *n = "true";
//     char *o = "var";
//     char *p = "while";
//     put(table, a, a); 
//     put(table, b, b);
//     put(table, c, c);
//     put(table, d, d); 
//     put(table, e, e); 
//     put(table, f, f); 
//     put(table, g, g); 
//     put(table, h, h); 
//     put(table, i, i); 
//     put(table, j, j); 
//     put(table, k, k); 
//     put(table, l, l); 
//     put(table, m, m); 
//     put(table, n, n); 
//     put(table, o, o);
//     put(table, p, p); 
//     //printTable(table);
//     printf("%s\n", get(table, a));
//     printf("%s\n", get(table, k));
//     printf("%s\n", get(table, p));
//     return 0;
// }