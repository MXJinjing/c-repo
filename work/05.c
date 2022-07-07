#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAXN 5000010
#define M 90073
typedef unsigned long long ull;

typedef struct datanode
{
    ull hash;
    int times;
    struct datanode *next;
} node;
int main()
{
    char *string;
    int lenth, i, j, max_appeared = 0, this_appeared, *appeared;
    ull *hash, temp, BASE = 123;
    node *head, *lead, *follow, *tempnode;
    head = malloc(sizeof(node));
    head->next = NULL;
    hash = (ull *)malloc(MAXN * sizeof(ull));
    string = (char *)malloc(MAXN * sizeof(char));
    appeared = (int *)malloc(MAXN * sizeof(int));
    for (i = 0; i < MAXN; i++)
        appeared[i] = 0;

    gets(string);
    scanf("%d", &lenth);
    //检查输入
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] != 'A' && string[i] != 'T' && string[i] != 'C' && string[i] != 'G')
        {
            printf("error: string输入错误.包含：%c\n", string[i]);
            return 0;
        }
    }
    if (lenth > strlen(string) || lenth < 0)
    {
        printf("error: n范围错误\n");
        return 0;
    }
    // printf("输入合法\n");

    //计算字符串的散列数组
    hash[0] = (ull)(string[0] + 1 - 'A');
    for (i = 1; i < strlen(string); i++)
    {
        hash[i] = hash[i - 1] * BASE + (ull)(string[i] + 1 - 'A');
        // printf("hash[%d]=%llu\n", i, hash[i]);
    }

    //计算ull整型的指数
    ull pow = 1;
    for (i = 0; i < lenth; i++)
        pow *= BASE;
    // printf("pow = %llu\n", pow);

    //计算相关长度字符串的散列
    for (i = lenth - 1; i < strlen(string); i++)
    {
        j = i - lenth;
        temp = hash[i];
        if (j >= 0)
            temp -= hash[j] * pow;
        appeared[temp%M] += 1;
        this_appeared = appeared[temp%M];
        max_appeared = this_appeared>max_appeared?this_appeared:max_appeared;
    }
    printf("%d",max_appeared);
    return 0;
}