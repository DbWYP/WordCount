#define _CRT_SECURE_NO_WARNINGS  1
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isAsciiChar(int c) {
    return c >= 0 && c <= 127;
}

void Count(FILE* file, int* charCount, int* wordCount) {
    int c;
    bool inWord = false;

    while ((c = fgetc(file)) != EOF) 
    {

        if (!isAsciiChar(c)) 
        {
            continue;
        }

        (*charCount)++;

        if (c == ' ' || c == ',' || c == '\n' || c == '\t') 
        {
            if (inWord) 
            {
                (*wordCount)++;
                inWord = false;
            }
        }
        else 
        {
            inWord = true;
        }
    }

    if (inWord) 
    {
        (*wordCount)++;
    }
}

int main(int argc, char* argv[]) {

    if (argc != 3 || (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-w") != 0))
    {
        fprintf(stderr, "请使用格式: %s -c input.txt  或者 %s -w input.txt\n", argv[0], argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[2], "r");
    if (file == NULL) 
    {
        perror("此文件不存在!");
        return 1;
    }

    int charCount = 0;// 记录字符数量
    int wordCount = 0;// 记录单词数量

    Count(file, &charCount, &wordCount);

    fclose(file);

    if (strcmp(argv[1], "-c") == 0)
    {
        printf("字符数: %d\n", charCount);
    }
    else
    {
        printf("单词数: %d\n", wordCount);
    }
    

    return 0;
}
