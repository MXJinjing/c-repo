#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10000
#define MAXM 1000000

long long trie[MAXN][26]; //字典树 静态
int cnt[MAXN];            //结束点
long long id;

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
        gets(article);
        find();
    }
    return 0;
}

void insert(char *string)
{
    char *flag = string;
    int p = 0, letter = 0;
    id = 0;
    for (; *flag != '\0'; flag++)
    {
        letter = *flag - 'a'; 
        if (trie[p][letter] == 0) //如果节点没有被创建
        {
            id ++;
            trie[p][letter] = id;
        }
        p = id; //移动到下一个节点
    }
    cnt[p] = 1;
    return;
}

void find(char *string, char *target)
{
    char *
}