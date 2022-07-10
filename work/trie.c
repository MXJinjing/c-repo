#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10000
#define MAXM 1000000
#define ROOT 0

long long trie[MAXN][26]; //字典树 静态
int cnt[MAXN];            //结束点
int next[MAXN];           //↑fail

long long id;

void creatfail();
void insert(char *string);
int find(char *target);
void clear();

int main()
{
    long long n, times;
    char string[MAXM], article[MAXM];
    scanf("%lld", &times);
    n = 0;
    for (long long i = 0; i < times; i++)
    {
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

void createfail()
{
    int p, q, front, rear;
    int queue[MAXN];
    front = 0, rear = 0, queue[0] = ROOT;

    p = ROOT;
    for (int i = 0; i < 26; i++)
        if (trie[p][i] != 0)
        {
            queue[front++] = trie[p][i];
            fail[trie[p][i]] = ROOT;
        }

    while (front >= rear)
    {
    }
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
            id++;
            trie[p][letter] = id;
        }
        p = id; //移动到下一个节点
    }
    cnt[p] += 1;
    return;
}

int find(char *target)
{
    int count = 0; //重计数
    char *flag = target;
    int p = 0, letter = 0;
    for (; *flag != '\0'; flag++)
    {
        letter = *flag - 'a';
        if (trie[p][letter] == 0) //如果节点不存在
            go back;              //利用ac自动树回退
        if (cnt[p] == 1)          //如果找到末尾
            count++;
        p = id;
    }
    return count;
}

void clear()
{
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < 26; j++)
            trie[i][j] = 0;
}