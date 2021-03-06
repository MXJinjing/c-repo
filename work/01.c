/*
    散列算法
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define SIZEMAX 10000000
typedef unsigned long long ull;

int main(void)
{
    char *main, *target;
    ull *hash, target_hash, pow, BASE = 123;
    main = (char *)malloc(SIZEMAX * sizeof(char));
    target = (char *)malloc(SIZEMAX * sizeof(char));
    hash = (ull *)malloc(SIZEMAX * sizeof(ull));
    gets(main);
    gets(target);
    int i,times = 0, len_main = strlen(main), len_target = strlen(target);
    //计算主串的哈希数组
    hash[0] = (ull)main[0];
    for (i = 1; i < len_main; i++)
    {
        hash[i] = hash[i - 1] * BASE + (ull)(main[i]);
    }

    //计算模式串散列
    target_hash = (ull)target[0];
    pow = BASE;
    for (i = 1; i < len_target; i++)
        target_hash = target_hash * BASE + (ull)target[i], pow = pow * BASE;

    //查找相同长度串
    ull cut_hash;
    for (int i = strlen(target) - 1, j; i < strlen(main); i++)
    {
        j = i - strlen(target);
        cut_hash = hash[i];
        if (j >= 0)
            cut_hash -= hash[j] * pow;
        if (cut_hash == target_hash)
            times++;
    }
    
    printf("%d\n", times);
    return 0;
}