#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "bm.h"

void print_progress_bar(int progress, int total) {
    int bar_width = 50;
    float ratio = (float)progress / total;
    int pos = ratio * bar_width;

    printf("\r[");
    for (int i = 0; i < bar_width; i++) {
        if (i < pos) {
            printf("#");
        } else {
            printf("-");
        }
    }
    printf("] %3d%%", (int)(ratio * 100));
    fflush(stdout);
}

void load_dictionary(HashMap *map, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open dictionary");
        exit(1);
    }

    char line[256];
    int line_count = 0;
    while (fgets(line, sizeof(line), file)) {
        char *word = strtok(line, ",");
        char *label_str = strtok(NULL, ",");
        if (word && label_str) {
            int label = atoi(label_str);
            insert(map, word, label);
            line_count++;
        }
    }
    fclose(file);
    printf("Dictionary loaded: %d entries\n", line_count);
}

int analyze_sentiment(HashMap *map, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open text file");
        exit(1);
    }

    char text[10000];
    size_t bytes_read = fread(text, sizeof(char), sizeof(text) - 1, file);
    if (bytes_read == 0) {
        fprintf(stderr, "Error reading file or empty file.\n");
        fclose(file);
        exit(1);
    }
    fclose(file);
    text[bytes_read] = '\0';  

    int score = 0;
    int progress = 0;
    int total = map->size;
    printf("Analyzing sentiment for file: %s\n", filename);
    printf("Total dictionary size: %d\n", total);

    for (int i = 0; i < map->size; i++) {
        Node *node = map->buckets[i];
        while (node) {
            int result = bm_search(text, node->key);
            if (result != -1) {
                score += node->value;
                // printf("\nFound: \"%s\" at position %d, score: %d\n", node->key, result, score);
            }
            node = node->next;
        }
        if (i % (total / 100 + 1) == 0) {
            print_progress_bar(i, total);
        }
        progress++;
    }
    print_progress_bar(total, total);  
    printf("\n");  
    return score;
}

int main() {
    HashMap *map = create_hashmap(1978);
    load_dictionary(map, "data/emotional_expression_dict.csv");

    int score = analyze_sentiment(map, "data/input.txt");
    if (score > 0) {
        printf("Positive Sentiment: %d\n", score);
    } else if (score < 0) {
        printf("Negative Sentiment: %d\n", score);
    } else {
        printf("Neutral Sentiment\n");
    }

    free_hashmap(map);
    return 0;
}