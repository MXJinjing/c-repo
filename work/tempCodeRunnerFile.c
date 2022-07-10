#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50000
#define MAXM 1000000

long long trie[MAXN][26]; //字典树 静态
long long next[MAXN];     //↑fail
int cnt[MAXN];            //结束点

char string[MAXM], article[MAXM];
long long id, count;
long long p, q, front, rear, queue[MAXN];
void insert(char *string);
void find(char *target);
void clear();

int main()
{
    int n, times;
    //printf("input your times\n");
    scanf("%d", &times);
    //printf("times = %d\n", times);
    for (; times > 0; --times)
    {
        id = 0;
        //printf("input n\n");
        scanf("%d", &n);
        //printf("n = %d\n", n);
        for (; n > 0; --n)
        {
            //printf("No.%d:\t", n);
            scanf("%s", string);
            //printf("string = %s\n", string);
            insert(string);
            
            //printf("string inserted\n");
        }
        
        for (long long i = 0; i <= id; i++)
        { 
            //printf("cnt[%lld] = %d\n", i, cnt[i]);
            for (int j = 0; j < 26; j++)
                if (trie[i][j] != 0)
                    //printf("%lld %c -> %lld\n", i, j + 'a', trie[i][j]);
        }

        //printf("input article:\n");
        scanf("%s", article);
        //printf("article = %s\n",article);
        find(article);
        printf("%lld\n", count);
    }
    return 0;
}

void insert(char *string)
{
    char *flag = string;
    p = 0;
    for (; *flag != '\0'; flag++)
    {
        int letter = *flag - 'a';
        if (trie[p][letter] == 0) //如果节点没有被创建
        {
            //printf("1.p = %lld, letter = %d, trie = %lld\n",p,letter,trie[p][letter]);
            trie[p][letter] = ++id;
        }
        {
            //printf("2. p: %lld->%lld\n",p,trie[p][letter]);
            p = trie[p][letter]; //移动到下一个节点
        }
    }
    cnt[p] += 1;
    return;
}

void find(char *target)
{
    front = 0, rear = 0;
    for (int i = 0; i < 26; i++)
        if (trie[0][i] != 0)
        {
            next[trie[0][i]] = 0;
            queue[front++] = trie[0][i];
        }

    while (front > rear)
    {
        p = queue[rear++];
        for (int i = 0; i < 26; i++)
            if (trie[p][i] != 0) //字节点不为空，寻找最大后缀
            {
                next[trie[p][i]] = trie[next[p]][i];
                queue[front++] = trie[p][i];
            }
            else //字节点为空，则指向fail指针的字节点
                trie[p][i] = trie[next[p]][i];
    }
    int letter;
    char *flag = target;
    p = 0, letter = 0;
    for (; *flag != '\0';flag++) 
    {
        letter = *flag - 'a';
        p = trie[p][letter]; //没有子数会返回根节点
        for (q = p; q != 0 && next[q] != -1; q = next[q])
        {
            count += cnt[q];
            cnt[q] = -1; //标记访问过
        }
    }
    return;
}