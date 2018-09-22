/*************************************************************************
    > File Name: two_trie_tree.cpp
    > Author: Yu_dong
    > Mail: 1124250973@qq.com
    > Created Time: 2018年08月12日 星期三 15时10分32秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Trie {
    int flag;
    struct Trie *next[2];
} Trie;

int node_cnt = 0;

Trie *getNewTrieNode() {
    Trie *p = (Trie *)malloc(sizeof(Trie));
    p->flag = 0;
    node_cnt++;
    return p;
}

void get_binary_code(int binary_code[8], int num) {
    for (int i = 7; i >= 0; --i) {
        binary_code[i] = num % 2;
        num /= 2;
    }
    return ;
}

Trie *build(Trie *root, char *string) {
    if (root == NULL) root = getNewTrieNode();
    Trie *p = root;
    int binary_code[8] = {0};
    int ind, num;
    for (int i = 0; string[i]; ++i) {
        num = (unsigned char)string[i];
        get_binary_code(binary_code, num);
        for (int i = 0; i < 8; ++i) {
            ind = binary_code[i];
            if (!p->next[ind]) p->next[ind] = getNewTrieNode();
            p = p->next[ind];
        }
    }
    p->flag = 1;
    return root;
}

void search(Trie *root, char *text) {
    printf("search in text [ %s ]\n", text);
    if (root == NULL) return ;
    Trie *p = root;
    int binary_code[8] = {0};
    int ind, num;
    for (int text_ind = 0; text[text_ind]; ++text_ind) {
        p = root;
        for (int i = text_ind; text[i]; ++i) {
            num = (unsigned char)text[i];
            get_binary_code(binary_code, num);
            int j = 0;
            for (; j < 8; ++j) {
                ind = binary_code[j];
                if (!p->next[ind]) break;
                p = p->next[ind];
            }
            if (j < 8) break;
            if (p->flag);
        }
    }
    return ; 
}


void output_test_info(double dur_time, long byte_sum, long use_num) {
    printf("==========================================\n");
    printf("efficiency analysis:\n");
    printf("program running time is [ %.2f ] ms\n", dur_time);
    printf("program occupied [ %ld ] byte, use [ %ld ] byte, space utilization [ %lf ]\n", byte_sum, use_num, use_num * 1.0 / byte_sum);
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
        // string[strlen(string) - 1] = 0;
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
    
    
    return 0;
}