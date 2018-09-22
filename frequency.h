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
