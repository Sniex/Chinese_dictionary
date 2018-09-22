/*************************************************************************
    > File Name: trie_tree.cpp
    > Author: Yu_dong
    > Mail: 1124250973@qq.com
    > Created Time: 2018年08月12日 星期三 14时22分48秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Trie {
    int flag;
    struct Trie *next[256];
} Trie;

long node_cnt = 0;


Trie *getNewTrieNode() {
    Trie *p = (Trie *)malloc(sizeof(Trie));
    p->flag = 0;
    node_cnt++;
    return p;
}

Trie *build(Trie *root, char *string) {
    if (root == NULL) root = getNewTrieNode();
    int ind;
    Trie *p = root;
    for (int i = 0; string[i]; ++i) {
        ind = (unsigned char)string[i];
        if (!p->next[ind]) p->next[ind] = getNewTrieNode();
        p = p->next[ind];
    }
    p->flag = 1;
    return root;
}

void search(Trie *root, char *text) {
    printf("search in text [ %s ]\n", text);
    if (root == NULL) return ;
    int ind;
    Trie *p = root;
    for (int text_ind = 0; text[text_ind]; ++text_ind) {
        p = root;
        for (int i = text_ind; text[i]; ++i) {
            ind = (unsigned char)text[i];
            if (!p->next[ind]) break;
            p = p->next[ind];
            if (p->flag);
        }
    }
    printf("search complete\n");
    return ;
}

void output_test_info(double dur_time, long byte_sum, long use_num) {
    printf("==========================================\n");
    printf("efficiency analysis:\n");
    printf("program running time is [ %.2f ] ms\n", dur_time);
    printf("program occupied [ %ld ] byte, use [ %d ] byte, space utilization [ %lf ]\n", byte_sum, use_num, use_num * 1.0 / byte_sum );
    printf("==========================================\n");
    return ;
}

int main() {
    Trie *root = NULL;
    char string[200] = {0}, text[200] = {0};
    int result; 
    long byte_sum = 0, use_num = 0;
    double dur_time;
    clock_t start, end;
    FILE *fp;
    fp = fopen("test_input", "r");
    while (!feof(fp)) {
        fscanf(fp, "%s", string);
        root = build(root, string);
        printf("insert [ %s ] complete\n", string);
        use_num += strlen(string);
    }
    printf("build trie complete\n");
    
    fp = fopen("search_file", "r");
    fscanf(fp, "%s", text);
    start = clock();
    search(root, text);
    end = clock();
    dur_time = (double)(end - start);
    output_test_info(dur_time, node_cnt * sizeof(Trie), use_num); 
    printf("%d", sizeof(Trie));
    
    return 0;
}