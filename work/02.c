/*
    KMP算法
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZEMAX 1000000

int kmp(char *main, char *target);
int main()
{
    char *main, *target;
    main = (char *)malloc(SIZEMAX * sizeof(char));
    target = (char *)malloc(SIZEMAX * sizeof(char));
    scanf("%s%s", main, target);
    if (strlen(target) >= 1 && strlen(target) <= SIZEMAX && strlen(main) >= 1 && strlen(main) <= SIZEMAX)
    {
        int times = kmp(main, target);
        printf("%d", times);
    }
    else printf("error\n");
    return 0;
}

int kmp(char *main, char *target)
{
    int i, j, main_size, target_size, *next, m, k, times = 0;
    next = (int *)malloc(SIZEMAX * sizeof(int));
    i = 0, j = 0;                                           // i为主串的下标，j为模式串的下标，进行初始化
    main_size = strlen(main), target_size = strlen(target); //计算两串的长度
    if (main_size < target_size)
        return 0;
    //运算next数组以备回退
    m = 0, k = -1;
    next[0] = -1; //初始化next值
    target[target_size] = '0';
    target[target_size + 1] = '\0';
    while (m < main_size)
    {
        if (k == -1 || main[m] == main[k]) //如果前后缀相同
            next[++m] = ++k;
        else
            k = next[k]; //如果不同，k减小到相同处继续
    }
    while (i < main_size) //主串没有结束
    {
        // printf("i = %d\n", i);
        if (j == -1 || main[i] == target[j]) //如果回退到最初,下标所对应字符串相等的情况
            i++, j++;
        else //不相等的情况，进行回退
            j = next[j];
        if (j == target_size) //如果匹配到一次，进行回退
        {
            // printf("now d = %d\n", i-target_size);
            times++, j = next[j - 1], i -= 1;
        }
    }
    free(next);
    return times;
}
