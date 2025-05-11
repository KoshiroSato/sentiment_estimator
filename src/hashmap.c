#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

// 文字列からハッシュ値を生成
unsigned long hash(char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

// ハッシュマップ作成
HashMap *create_hashmap(int size) {
    HashMap *map = malloc(sizeof(HashMap));
    map->buckets = calloc(size, sizeof(Node *));
    map->size = size;
    return map;
}

// ノード作成
Node *create_node(char *key, int value) {
    Node *node = malloc(sizeof(Node));
    node->key = strdup(key);
    node->value = value;
    node->next = NULL;
    return node;
}

// ハッシュマップにキーと値を挿入
void insert(HashMap *map, char *key, int value) {
    unsigned long index = hash(key) % map->size;
    Node *new_node = create_node(key, value);
    new_node->next = map->buckets[index];
    map->buckets[index] = new_node;
}

// ハッシュマップからキーを探索し、対応する値を取得
int search(HashMap *map, char *key) {
    unsigned long index = hash(key) % map->size;
    Node *node = map->buckets[index];
    while (node) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }
    return 0;
}

void free_hashmap(HashMap *map) {
    for (int i = 0; i < map->size; i++) {
        Node *node = map->buckets[i];
        while (node) {
            Node *temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
    }
    free(map->buckets);
    free(map);
}