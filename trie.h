/*************************************************************************
	> File Name: trie.h
	> Author: Yu_dong
	> Mail: 1124250973@qq.com
	> Created Time: 2018年08月08日 星期三 14时32分48秒
 ************************************************************************/

#ifndef _TRIE_H
#define _TRIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./sear.h"
#define BASE 2

int StrtoInt(char *str) {
    int res = 0;
    for (int i = 0; str[i]; i++) {
        res += (int)pow(2, strlen(str) - i - 1) * (str[i] - '0');
        // printf("%d  [%d]  %d\n",strlen(str) - i - 1, str[i] - '0', res);
    }
    return res;
}

int node_cnt = 0;

typedef struct Node {
    int flag;
    struct Node *next[BASE];
} Node, *Trie;

Node *getNode() {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    node_cnt += 1;
    return p;
}

Node *insert(Trie root, const char *str) {
    if (root == NULL) root = getNode();
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        int ind = str[i] - '0';
        if (p->next[ind] == NULL) p->next[ind] = getNode();
        p = p->next[ind];
    }
    p->flag = 1;
    return root;
}

int search(Trie root, char *str) {
    // int id = 0;
    Node *p = root;
    int i = 0;
    while (p && str[i]) {
        int ind = str[i++] - '0';
        p = p->next[ind];
    }
    // if (p&&p->flag) return 1;
    // else return 0;
    return (p && p->flag);
}

void output(Trie root, char *str, int level) {
    if (root == NULL) return ;
    // node_cnt++;
    str[level] = 0;
    if (root->flag) {
        printf("find word: %s\n", str);
    }
    for (int i = 0; i < BASE; i++) {
        if (root->next[i] == NULL) continue;
        str[level] = i + '0';
        output(root->next[i], str, level + 1);
    }
    return ;
}







#endif
