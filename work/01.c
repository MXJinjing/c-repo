/*
    KMP算法
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZEMAX 10000

int main()
{
    char main[SIZEMAX], target[SIZEMAX];
    gets(main);   //获取主串
    gets(target); //获取模式串
    int position = kmp(mian, target);
    if (position > -1)
        printf("%d", position);
    else
        printf("None found.\n");
    return 0;
}

int kmp(char *main, char *target)
{
    int i, j, main_size, target_size, next[SIZEMAX];
    i = 0, j = 0;                                           // i为主串的下标，j为模式串的下标，进行初始化
    main_size = strlen(main), target_size = strlen(target); //计算两串的长度
    cal_next(next, target, target_size);                    //运算next数组以备回退
    while (j < target_size && i < main_size)                //当没有匹配到或主串没有结束
    {
        if (j == -1) //如果回退到最初
            i++, j++;
        if (main[i] == target[j]) //下标所对应字符串相等的情况
            i++, j++;
        else //不相等的情况，进行回退
            j = next[j];
    }
    if (j == target_size) //如果匹配到主串
        return i - target_size;
    else //模式串在主串中没有匹配值
        return -99;
}

int cal_next(int *next, char *target, int target_size)
{
    next[0] = -1;
    
}