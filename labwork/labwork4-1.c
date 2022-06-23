/*
    任给一个英文资料的文本文件，要求编程完成以下功能，统计该文本文件的所有单词(每个单词不包括空格及跨行，
    单词由字母序列构成且不区分大小写），并按字典顺序排列存储在一个文件里，统计每个单词在文本文件中出现的总次数、
    频度（该单词出现的总次数/所有单词出现次数之和）、在文本文件中首次出现的行号及位置。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void TransCapital(char *in, char *out) //用于转化大写为小写
{
    int i = 0, j = 0;
    while (*(in + i) != '\0')
    {
        char ch = *(in + i);
        if (ch >= 'A' && ch <= 'Z')
            ch += 32;
        *(out + j) = ch;
        i++;
        j++;
    }
    *(out + j) = '\0';
}

typedef struct node
{
    char s[50];
    int row;
    int col;
    int times;
    struct node *next;
} word;

int main()
{
    FILE *t = fopen("labwork4-1-temp.txt", "w"); //打开缓存文件
    FILE *p = fopen("labwork4-1-read.txt", "r"); //打开输入文件

    word *head[26], *lead, *follow;
    for (int i_ = 0; i_ < 26; i_++)
    {
        head[i_] = (word *)malloc(sizeof(word)); //为表头节点分配空间
        head[i_]->next = NULL;
    }

    char ch;
    char temp[50];
    int i, col = 1, row = 0;
    while ((ch = fgetc(p)) != EOF) //逐字读取文件
    {
        if (ch == '\n') //换行，行数清零
            col++, row = 0;
        if ((ch <= 'Z' && ch >= 'A') || (ch <= 'z' && ch >= 'a')) //如果读到英文字符，则记录该单词
        {
            i = 0, row++;
            while ((ch <= 'Z' && ch >= 'A') || (ch <= 'z' && ch >= 'a') || (ch == '-' && temp[i - 1] != '-') || (ch == '\''))
            {
                temp[i] = ch;
                ch = fgetc(p);
                i++;
            }
            if (temp[i - 1] == '-' || temp[i - 1] == '\'')
                i--;
            temp[i] = '\0';

            //创建临时节点
            word *tempnode = (word *)malloc(1*sizeof(word));
            TransCapital(temp, tempnode->s); //转化大写为小写
            tempnode->times = 1;
            tempnode->col = col;
            tempnode->row = row;
            tempnode->next = NULL;

            fprintf(t,"%s-- ",tempnode->s);
            fprintf(t, "putting \"%s\" to head[%d]\n", tempnode->s, tempnode->s[0] - 97);

            //将单词计入链表
            lead = head[tempnode->s[0] - 97]->next, follow = head[tempnode->s[0] - 97];
            while (lead != NULL)
            {
                fprintf(t, "lead = %s\t temp = %s\n", lead->s, tempnode->s);
                if (strcmp(lead->s, tempnode->s) == 0) //如果遇到重复的单词
                {
                    lead->times++;
                    fprintf(t, "Done: times ++\n\n");
                    break;
                }
                if (strcmp(lead->s, tempnode->s) > 0 && (strcmp(follow->s, tempnode->s) < 0 || follow == head[tempnode->s[0] - 97]))
                //如果单词的顺序应该排在前后者中间
                {
                    tempnode->next = lead;
                    follow->next = tempnode;
                    if (follow != head[tempnode->s[0] - 97])
                        fprintf(t, "Done: put in the middle of \"%s\" and \"%s\"\n\n", follow->s, lead->s);
                    else
                        fprintf(t, "Done: put in the middle of head and \"%s\"\n\n", lead->s);
                    break;
                }
                follow = lead, lead = lead->next;
            }
            if (lead == NULL) //如果单词的顺序在最后
            {
                fprintf(t, "Done: put in the tail\n\n");
                follow->next = tempnode;
            }
        }
    }
    //统计总词数
    int total = 0;
    for (int i_ = 0; i_ < 26; i_++)
    {
       lead = head[i_]->next;
        while (lead != NULL)
        {
            total++;
            lead = lead->next;
        }
    }

    //输出结果
    FILE *p2 = fopen("labwork4-1-out.md", "w"); //打开输出文件
    fprintf(p2, "|序号|单词|次数|列|行|频度|\n|-|---|--|--|--|--|\n");
    i = 1;
    for (int i_ = 0; i_ < 26 ; i_++)
    {
        lead = head[i_]->next;
        double t2 = (double)total; //转化浮点数
        while (lead != NULL)
        {
            double t1 = (double)lead->times; //转化浮点数
            fprintf(p2, "|%2d|%s|%d|%d|%d|%f|\n", i, lead->s, lead->times, lead->col, lead->row, t1 / t2);
            lead = lead->next;
            i++;
        }
    }
    //关闭文件
    fclose(p);
    fclose(p2);
    fclose(t);
    return 0;
}
