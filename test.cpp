/*************************************************************************
	> File Name: test.cpp
	> Author: Yu_dong
	> Mail: 1124250973@qq.com
	> Created Time: 2018年08月07日 星期二 11时15分52秒
 ************************************************************************/

#include <stdio.h>
#include <math.h>
#include "./frequency.h"
#include "./huffman.h"
#include "./trie.h"
#include "./sear.h"
#include <string.h>
#include <time.h>
#define CHAR_NUM 256

void output_test_info(double dur_time, int byte_sum, int use_num) {
    printf("search complete\n");
    printf("==========================================\n");
    printf("efficiency analysis:\n");
    printf("program running time is [ %lf ] ms\n", dur_time);
    printf("program occupied [ %d ] byte, use [ %d ] byte, space utilization [ %lf ]\n", byte_sum, use_num, use_num * 1.0 / byte_sum);
    printf("==========================================\n");
    return ;
}

void display_frequency(int *freq) {
    for (int i = 0; i < 256; i++) {
        printf("[%3d ---- %3d] ", i, freq[i]);
         if (i % 3 == 0) printf("\n");
    }
    printf("\n");
    return ;
}

void build_huffman_tree(HFNode *arr[], int *freq, char (*huf_code)[100]) {
    char buff[100];
    int cnt  =  0;
    for (int i  =  0; i < 256; i++) {
        if (freq[i] == 0) {
            cnt += 1;
            continue;
        }
        HFNode *new_node = get_new_node();
        new_node->ch = (char)i;
        new_node->freq = freq[i];
        arr[i - cnt] = new_node;
    }
    build(CHAR_NUM - cnt, arr);
    extract(arr[0], buff, huf_code, 0);
}

int Search(hashtable *h, Trie root, char (*huf_code)[100], unsigned char *ans) {    
    char huf_ans[1000] = {0};
    for (int i = 0; ans[i]; i++) {
        strcat(huf_ans, huf_code[ans[i]]);
    }

    Trie p = root;

    char result[1000] = {0};
    unsigned char tmp[1000] = {0};
    if (root == NULL) return 0;
    int i = 0;
    int j = 0;
    int flag = 0;
    while (huf_ans[j] != '\0') {
        if (huf_ans[i] == '\0') {
            i = j + 1;
            if (huf_ans[i] == '\0') break;
        }
        if (p->flag == 1){
            flag = 1;
            huff_to_str(result, h, tmp, huf_code);
            printf("find %s : YES\t", tmp);
            printf("%s\n", result);
            memset(tmp, 0, sizeof(tmp));
        }
        int ind = huf_ans[i++] - '0';
        strncat(result, huf_ans + i - 1, 1);
        if (p->next[ind] == NULL) {
            memset(result, 0, sizeof(result));
            p = root;
            i = j + 1;
            j = i;
            continue;
        }
        p = p->next[ind];
    }
    if (!flag) printf("Not Find\n");
    return 0;
}

int search_time(Trie root, unsigned char *text, char (*huf_code)[100]) {
    printf("search in text [ %s ]\n", text);
    if (root == NULL) return 0;
    Trie p = root;
    char huff[100] = {0};

    int i = 0;
    
    while (text[i]) {
        int k = 0;
        for(int l = 0; huf_code[text[i]][l]; ++l){
            huff[k++] = huf_code[text[i]][l];
        }
        huff[k] = '\0';
        int j = 0;
        while (1) {
            if (huff[j] == '\0') break;
            if (p->flag) {
                break;
            }
            int ind = huff[j++];
            if (p->next[ind] == NULL) {
                p = root;
                break;
            }
            p = p->next[ind];
        }
        huff[0] = '\0';
        i++;
    }
    printf("search complete\n");
    return 0; 
}


int Insert(hashtable *h, unsigned char *origin, Trie root, char (*huf_code)[100], char *temp, unsigned char *ans, int word_cnt){
    clock_t start, end;

    FILE *fp = fopen("test_input", "r");

    while (!feof(fp)) {
        fscanf(fp, "%s\n", origin);
        temp[0] = '\0';
        int ind = 0, i;
        for(i = 0; origin[i]; ++i){
            for(int j = 0; huf_code[origin[i]][j]; ++j){
                temp[ind++] = huf_code[origin[i]][j];
            }
        }
        word_cnt += i;
        temp[ind] = '\0';
        printf(" [%s : %s]\n", origin, temp);
        root = insert(root,temp);
    }
    fclose(fp);

    printf("done\n");
    
    printf("Search begin: \n");
    fp = fopen("search_file", "r"); 
    
    while (!feof(fp)) {
        ans[0] = '\0';
        fscanf(fp, "%s", ans);
        printf("%s\n", ans);
        Search(h, root, huf_code, ans);
        printf("\n\n");
    }

    unsigned char text[200] = {0};
    fp = fopen("search_file", "r");
    fscanf(fp, "%s", text);

    start = clock();
    search_time(root, text, huf_code);
    end = clock();
    output_test_info((double)(end - start), node_cnt * sizeof(Node), word_cnt);
    return 0;

}

int main() {
    char str[6]  =  "input";
    int freq[256]  =  {0};
    read_file(str, freq);

    display_frequency(freq);

    HFNode *arr[CHAR_NUM]  =  {0};
    char huf_code[256][100]  =  {0};
    build_huffman_tree(arr, freq, huf_code);

    Trie root = NULL;
    int word_cnt = 0;
    unsigned char origin[100] = {0};
    char temp[500] = {0};
    unsigned char ans[100] = {0};

    hashtable *h = init(100000);
    for(int i = 0; i < CHAR_NUM; i++){
        insert_ha(h, huf_code[i], i);
    }

    Insert(h, origin, root, huf_code, temp, ans, word_cnt);

    return 0;
}

