#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/cdefs.h>
#define MAXN 1000050
typedef long long ll;

ll trie[MAXN][26];  //字典树
int cnt[MAXN]; //结束点


void insert(char *string);
int find();

int main()
{
    int times,n;
    char *string[MAXN],* article;
    scanf("%d",times)
    for(int i=0; i<times; i++)
    {
        scanf("%d",n);
        for(int j=0; j<n; j++)
        {
            gets(string[j]);
            printf("%s\n",string[j]);
        }
    }
    return 0;
}
