#ifndef HASHMAP_H
#define HASHMAP_H

typedef struct Node {
    char *key;
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node **buckets;
    int size;
} HashMap;

unsigned long hash(char *str);
HashMap *create_hashmap(int size);
void insert(HashMap *map, char *key, int value);
int search(HashMap *map, char *key);
void free_hashmap(HashMap *map);

#endif