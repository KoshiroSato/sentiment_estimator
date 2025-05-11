#include <string.h>
#include "bm.h"

// シフトテーブル構築
void build_shift_table(char *pattern, int table[], int len) {
    for (int i = 0; i < 256; i++) table[i] = len;
    for (int j = 0; j < len - 1; j++) {
        table[(unsigned char)pattern[j]] = len - 1 - j;
    }
}

// BM法による文字列検索
int bm_search(char *text, char *pattern) {
    int m = strlen(pattern);
    int n = strlen(text);
    int table[256];
    build_shift_table(pattern, table, m);

    int i = m - 1; // パターンの末尾位置から探索開始
    while (i < n) {
        int j = m - 1; 
        int k = i;     
        // パターンとテキストが一致している限り比較を続ける
        while (j >= 0 && text[k] == pattern[j]) {
            k--;
            j--;
        }
        // すべて一致した場合、パターンが見つかった位置を返す
        if (j < 0) {
            return k + 1;
        }
        // シフト量を計算し、シフトして次の比較位置へ
        int shift = table[(unsigned char)text[i]];
        i += (shift > (m - j) ? shift : (m - j));
    }
    return -1;
}