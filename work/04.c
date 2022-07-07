/*
字符串哈希
    字符串哈希就是将一个字符串映射为一个整数，该整数就可以用于vis标记有没有出现过，就不用遍历所有字符串了。
    哈希函数
        hash(string) = sum(string[i] * base^i) (mod M)
    M 为质数,当M取大质数(或M取大数，b取质数时)2个字符串只有很小的概率会映射到同一个值上
    对于一个字符串的字串，用l表示字串的左端点、用r表示字串的右端点，可得到如下的式子
        hash(l,r) = sum(i=1->r,string[i] * base^(r-i)) (mod M)
             = hash(1,r) - hash(1, l-1)* base^(r-l+1)
    预处理出字符串 s 的哈希函数数组 hash[]，hash[i]表示hash(1,i),len=r-l+1：
        hash(l,r) = hash[r] - hash[l] * base^(len)
    查询2个子串拼接成的字符串的哈希值
        hash(l_1,r_2) = hash(l_1,r_1) * base^(r_2-l_2+1) + hash(l_2,r_2)
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAXN 1000000
#define M 10501
#define BASE 123

typedef ull unsigned long long;
int *gethash(char *s, int *hash);
int main()
{
    int *hash;
    char string[MAXN];
    gets(string);
    gethash(string, hash);
    return 0;
}

int *gethash(char *s, int *hash)
{
    int size = strlen(s);
    ull int sum;
    hash = (int*)malloc(sizeof(int)*size);
    for(int i=0; i<size; i++)
    {
        sum = 0;
        for(int j=0; j<i; j++)
            sum += (s[i]-'a') * pow(BASE,(double)j);
        hash[i] = sum % M;
        printf("hash[%d] = %d\n", i, hash[i]);
    }
    return hash;
}


