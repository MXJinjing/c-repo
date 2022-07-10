#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50000
#define MAXM 1000000

long long trie[MAXN][26]; //字典树 静态
long long next[MAXN];     //↑fail
int cnt[MAXN];            //结束点

long long id, count;
long long p, q, front, rear, queue[MAXN];
void insert(char *string);
void find(char *target);
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
        scanf("%lld", &n);
        for (long long j = 0; j < n; j++)
        {
            scanf("%s", string);
            insert(string);
        }
        gets(article);

        // for (long long i = 0; i <= id; i++)
        // {
        //     printf("cnt[%lld] = %lld\n", i, cnt[i]);
        //     for (int j = 0; j < 26; j++)
        //         if (trie[i][j] != 0)
        //             printf("%lld %c -> %lld\n", i, j + 'a', trie[i][j]);
        // }

        find(article);
        printf("%lld\n", count);
    }
    return 0;
}

void insert(char *string)
{
    char *flag = string;
    long long p;
    int letter = 0;
    p = 0;
    for (; *flag != '\0'; flag++)
    {
        letter = *flag - 'a';
        if (!trie[p][letter]) //如果节点没有被创建
        {
            trie[p][letter] = ++id;
        }
        p = trie[p][letter]; //移动到下一个节点
    }
    cnt[p] += 1;
    return;
}

void find(char *target)
{
    front = 0, rear = 0, queue[0] = 0;
    p = 0;
    for (int i = 0; i < 26; i++)
        if (trie[p][i] != 0)
        {
            queue[front++] = trie[p][i];
            next[trie[p][i]] = 0;
        }

    while (front > rear)
    {
        p = queue[rear++];

        for (int i = 0; i < 26; i++)
            if (trie[p][i] != 0)
            {
                //printf("fail[%lld] = %lld\n", trie[p][i], trie[next[p]][i]);
                queue[front++] = trie[p][i];
                next[trie[p][i]] = trie[next[p]][i];
            }
            else
            {
                // printf("fail[%lld] = 0(root)\n", trie[p][i]);
                next[trie[p][i]] = 0;
            }
    }
    int letter;
    char *flag = target;
    p = 0, letter = 0;
    for (; *flag != '\0';)
    {
        letter = *flag - 'a';
        if (p != 0 && trie[p][letter] == 0)
        {
            p = next[p];
        }
        else
        {
            p = trie[p][letter];
            flag++;
        }
        if (cnt[p] > 0)
        {
            count += cnt[p];
            //printf("cnt[%d] = %d\n", p, cnt[p]);
        }
    }
    return;
}

void clear()
{
    id = 0;
    count = 0;
    for (int i = 0; i < MAXN; i++)
    {
        for (int j = 0; j < 26; j++)
            trie[i][j] = 0;
        next[i] = 0;
        cnt[i] = 0;
    }
    return;
}
