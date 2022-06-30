#ifndef HASHMAP_H
#define HASHMAP_H


typedef struct map{
    int index;
    char *key;
    int value;
    struct map *next;
}Map;


int hashfunction(char *c);
void put(Map *map[], char *K, int V);
void printTable(Map *map[]);
void initTable(Map *map[]);
int get(Map *map[], char *elem);
#endif