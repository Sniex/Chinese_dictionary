
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
