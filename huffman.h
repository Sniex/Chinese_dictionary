/*************************************************************************
	> File Name: huffman.h
	> Author: Yu_dong
	> Mail: 1124250973@qq.com
	> Created Time: 2018年08月07日 星期二 10时09分57秒
 ************************************************************************/
#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include <stdlib.h>
#include <string.h>

#define swap(a, b) { \
    __typeof(a) temp = a; \
    a = b, b = temp ; \
}


typedef struct HFNode {
    unsigned char ch;
    int freq;
    struct HFNode *l, *r;
} HFNode;

HFNode *get_new_node() {
    HFNode *p = (HFNode *)malloc(sizeof(HFNode));
    p->ch = p->freq = 0;
    p->l = p->r = NULL;
    return p;
}

void build(int n, HFNode *arr[]) {
    for (int times = 0; times < n - 1; times++) {
        HFNode *minNode = arr[0];
        int ind = 0;
        for (int i = 1; i < n - times; i++) {
            if (arr[i]->freq >= minNode->freq) continue;
            minNode = arr[i];
            ind = i;
        }
        swap(arr[ind], arr[n - times - 1]);
        minNode = arr[0];
        ind = 0;
        for (int i = 1; i < n - times - 1; i++) {
            if (arr[i]->freq >= minNode->freq) continue;
            minNode = arr[i];
            ind = i;
        }
        swap(arr[ind], arr[n - times - 2]);
        HFNode *new_node = get_new_node();
        new_node->l = arr[n - times - 1];
        new_node->r = arr[n - times - 2];
        new_node->freq = arr[n - times - 1]->freq + arr[n - times - 2]->freq;
        arr[n - times - 2] = new_node;
    }
    return ;
}

void extract(HFNode *root, char *buff, char (*huf_code)[100], int n) {
    buff[n] = '\0';
    if (root->l == NULL && root->r == NULL) {
        strcpy(huf_code[root->ch ], buff);
        // printf("%d : %s\n", root->ch , buff);
        return ;
    }
    buff[n] = '0';
    // printf("-->%s\n", buff);
    extract(root->l, buff, huf_code, n + 1);
    buff[n] = '1';
    extract(root->r, buff, huf_code, n + 1);
    return ;
}


#endif
