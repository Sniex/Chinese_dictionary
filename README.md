



# 中文字典（最终版）

[TOC]

## 一、 目标

1. 完成哈弗曼编码+二叉字典树的建立；
2. 实现多模匹配；
3. 对比字典树、二叉字典树、哈弗曼二叉字典树的时空效率；
4. 预估多模匹配的效率，与实际进行对比，分析。



## 二、理论思想及效率分析

<!--中文拥有共计128个特殊字节，加上常用的128个字符字节，共计256个字节-->

#### 空间

建立普通字典树需要每个节点开设256个指针，而二叉字典树则是用到了相关字节对应的整形数字的二进制，从而减少了每个节点所需要的指针数量，从而减少了建立字典树所需要的空间。

由于二叉字典树与哈夫曼二叉字典树都是在每个节点上开设两个指针，仅仅在建成后的字典树高度上，哈夫曼二叉树会低一些，因此二者在空间效率上并没有太大区别。

#### 时间

###### 普通字典树与二叉字典树对比

由于普通字典树每个节点上有256个指针，因此树中每一条边都对应了一个字节，树的形状为一颗矮胖树，

而二叉字典树是通过相应字节的整形转化的二进制来表示不同字节，树的形状为一颗瘦高树。

因此在相同时间内搜索同样的中文字符串，普通字典树的速度应相对较高。

###### 二叉字典树与哈夫曼二叉字典树对比

同样是二叉，不同点仅在于对不同字节的编码上，加上了哈夫曼的二叉字典树中，将汉字中的常用字节缩短，增加了不常用字节的编码长度使得建立在字典树上的常用字节可以里根节点更近从而提高了二叉字典树的搜索速度。



*存储n个字节的中文模式字符串，搜索m个字节的中文文本字符串。*

|            | 字典树 | 二叉字典树 | 哈夫曼+二叉字典树 |
| :--------: | :---: | :------: | :-------------: |
| 查找时间复杂度 | O(m) | O(m^2^) | O(m^2^) |
| 空间复杂度 | O(256^n^) | O(2^n^) | O(2^n^) |
| 综合评价 | 空间复杂度难以忍受 | 牺牲时间以换空间 | 空间与时间相对可以接受 |


## 三、 实际效率对比

空间效率计算公式

​                                                                                  $P = use/spand$

#### 1. 普通字典树

![](/home/yu_dong/Pictures/2018-08-12 21-31-42屏幕截图.png)

#### 2. 二叉字典树

![](/home/yu_dong/Pictures/2018-08-12 21-32-33屏幕截图.png)

#### 3. 哈夫曼二叉字典树

![](/home/yu_dong/Pictures/2018-08-12 21-32-05屏幕截图.png)

#### 总结

* 普通二叉树的时间效率在检索速度上很快，在不输出文本的情况下检索速度可以达到24ms；空间上，存储2183380字节的信息需要高达2368078800字节的空间建立二叉树，符合O(256^n^)的空间复杂度预期
* 二叉字典树的时间效率相对其他来说就慢了不少，在不输出文本的情况下检索速度只有53ms；而其空间效率相比较与普通二叉树有很大进步，存储2183380字节信息，所需空间也只需要2亿字节。
* 哈夫曼二叉字典树相比较与其他两种方法，在时间及空间上都有很出色的表现，相同情况下，检索速度达到了13ms，空间消耗也降到了163030800字节。


## 四、 已知问题

中文在utf-8编码集下，是由3个字节组成的，易知，存在任意3个字节（128-256）即可组成一个汉字。
因此在使用文本串检索字典树时，所检索的汉字在实际上检索的是字节信息，也正因为如此，存在两个相邻汉字的6个字节中，前一个汉字的后一部分字节与后一个汉字的前一部分字节可能组成一个新的汉字这种情况。



## 五、 改进方向

猜测：是否可以将文本串分词检索；

将文本串先按汉字分割为不同子串，将子串相互组合检索，是否可以避免上述问题。（待验证）

猜测：为字典树建立fail指针，变成哈夫曼AC自动机；

检索到文字尾部是跳转到下一个文字头，避免从中间字节开始检索，以避免上述问题。（待验证）



## 六、 哈夫曼二叉树运行截图

##### 词频统计表节选

![](/home/yu_dong/Pictures/2018-08-12 21-45-26屏幕截图.png)

##### 插入模式串节选

![](/home/yu_dong/Pictures/2018-08-12 21-48-39屏幕截图.png)

##### 搜索文本串结果节选

![](/home/yu_dong/Pictures/2018-08-12 21-50-06屏幕截图.png)






## 七、资料来源

词频统计语料库：  小说 《Re：从零开始的异世界生活》 21.2 MB

模式串词汇： [THUOCL：清华大学开放中文词库](http://thuocl.thunlp.org/) [语料库在线](http://corpus.zhonghuayuwen.org/wdindex.aspx)  2.4 MB

文本串语料：[百度文库 赞美汉语的句子](https://wenku.baidu.com/view/871a94ca0b4c2e3f56276304.html) 4.5 KB



## 八、 附录

------

### 哈夫曼二叉树代码：

##### 主文件 `test.cpp` 代码

```C
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


```

##### 统计词频`frequency.cpp`文件

```c
/*************************************************************************
	> File Name: frequency.h
	> Author: Yu_dong
	> Mail: 1124250973@qq.com
	> Created Time: 2018年08月07日 星期二 08时59分38秒
 ************************************************************************/

#ifndef _FREQUENCY_H
#define _FREQUENCY_H

void read_file(char *filename, int *word_frequency) {
    FILE *fp = fopen(filename, "r");
    while (!feof(fp)) {
        int ch=fgetc(fp);
        //printf("%d ",ch);

        if (ch != -1) {
            word_frequency[ch] += 1;
        }
    }
    fclose(fp);
    return ;
}

#endif
```

##### 哈夫曼树`huffman.h`文件

```c
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

```

##### 字典树`trie.h`文件

```c
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

```

##### 哈希表`sear.h`文件

```c

#ifndef _SEAR_H
#define _SEAR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./trie.h"
#define null 300


typedef struct HashTable{

    int *data;
    int h_size;
}hashtable;

hashtable *init(int size){
    hashtable *h=(hashtable *)malloc(sizeof(hashtable));
    h->h_size=size;
    h->data=(int *)calloc(sizeof(int),size);
    for(int i=0;i<h->h_size;i++) h->data[i]=null;
    return h;
}

int hash_convert(hashtable *h,char *str){
    int ans=0;
    for(int i=0;str[i];i++){
        ans=(ans*256+str[i]+256)%h->h_size;
    }
    return ans;
}

int se(hashtable *h,char *value,int *pos,int *times,int n){
    *pos=hash_convert(h,value);
    *times=0;
    while(h->data[*pos]!=null&&h->data[*pos]!=n){
        (*times++);
        if(*times<h->h_size){
            *pos=(*pos+1)%h->h_size;
        }
        else return 0;
    }
    if(h->data[*pos]!=null&&h->data[*pos]==n){
        return 1;
    }else return 0;
}

void insert_ha(hashtable *h,char *huff_code,int val){
    int pos,times;
    if(se(h,huff_code,&pos,&times,val)) return;
    //int key=hash_convert(h,huff_code);
    //if(h->data[key]!=null) printf("hell");
    h->data[pos]=val;
    return ;
}


void huff_to_str(char *hu_code,hashtable *h,unsigned char *ans,char (*hu)[100]){
    int ind=0;
    char temp[100]={0};
    int k=0;
    for(int i=0;hu_code[i];i++){
        temp[k]=hu_code[i];
        temp[k+1]='\0';
        int key=hash_convert(h,temp);
        while(h->data[key]!=null&&strcmp(hu[h->data[key]],temp)!=0){
            key=(key+1)%h->h_size;
        }
        if(strcmp(hu[h->data[key]],temp)==0){
            ans[ind++]=h->data[key];
            memset(temp,0,sizeof(temp));
            k=-1;
        }
        k++;
    }
    ans[ind]='\0';
    return ;
}
#endif

```

### 普通字典树

##### 普通字典树`trei_tree.cpp`文件

```c
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
    char *str;
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
    p->str = (char *)malloc(strlen(string));
    p->str = strdup(string);
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

void output(Trie *root, char *str, int level) {
    node_cnt++;
    if (root == NULL) return ;
    str[level] = 0;
    if (root->flag) {
        printf("find word: %s\n", root->str);
    }
    for (int i = 0; i < 256; i++) {
        if (root->next[i] == NULL) continue;
        str[level] = i + '0';
        output(root->next[i], str, level + 1);
    }
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
```

### 二叉字典树

##### 二叉字典树`two_trei_tree.cpp`文件

```c
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
```





