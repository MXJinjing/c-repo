#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char s[1000010], t[10010];
int next[10010];
void getnext(char *t, int *next)//得到next数组
{
    next[0] = -1;
    int i = 0, k = -1, len = strlen(t);
    while (i < len)
    {
        if (k == -1 || t[i] == t[k])
        {
            i++;
            k++;
            next[i] = k;
        }
        else
        {
            k = next[k];
        }
    }
}
int kmp(char *s, char *t)
{
    int ans = 0, len = strlen(s), lend = strlen(t), j = 0, i = 0;
    while(i <= len)
    {
        if (j == -1 || s[i] == t[j])
        {
            j++;
            i++;
        }
        else
        {
            j = next[j];
        }
        if (j == lend)
        {
            ans++;
            j = next[j];
        }
    }
    return ans;
}
int main()
{

        scanf("%s%s", t, s);
        getnext(t, next);
        printf("%d\n", kmp(s, t));
    return 0;
}