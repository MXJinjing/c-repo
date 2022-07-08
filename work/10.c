#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10000
#define MAXM 1000000

long long trie[MAXN][26]; //字典树
int cnt[MAXN];            //结束点

void insert(char *string);
int find();
void clear();

int main()
{
    long long n, times;
    char string[MAXM], article[MAXM];
    scanf("%lld", &times);
    n = 0;
    for (long long i = 0; i < times; i++)
    {
        //清理并初始化字典树
        clear();
        for (long long j = 0; j < n; j++)
        {
            scanf("%s", string);
            printf("%s\n", string);
            insert(*string);
        }
        scanf("%s", article);
        printf("%s\n", article);
        find();
    }
    return 0;
}

void insert(char *string)
{
    return;
}

void find()
{
}