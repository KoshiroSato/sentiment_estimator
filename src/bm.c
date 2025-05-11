#include <string.h>
#include "bm.h"

void build_shift_table(char *pattern, int table[], int len) {
    for (int i = 0; i < 256; i++) table[i] = len;
    for (int j = 0; j < len - 1; j++) {
        table[(unsigned char)pattern[j]] = len - 1 - j;
    }
}

int bm_search(char *text, char *pattern) {
    int m = strlen(pattern);
    int n = strlen(text);
    int table[256];
    build_shift_table(pattern, table, m);

    int i = m - 1;  
    while (i < n) {
        int j = m - 1; 
        int k = i;     

        while (j >= 0 && text[k] == pattern[j]) {
            k--;
            j--;
        }

        if (j < 0) {
            return k + 1;
        }

        int shift = table[(unsigned char)text[i]];
        i += (shift > (m - j) ? shift : (m - j));
    }
    return -1;
}