/*
    最基础，无任何优化的PRIME算法 O(n) = n*n
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define TRUE 1
#define FALSE 0
#define MARKED -1
#define MAXN 10000
#define NOWAY (llu)1000000001

typedef unsigned long long llu;

llu map[MAXN][MAXN], lowcost[MAXN], total_weight;
long et;
int vt, nearvex[MAXN];

llu prime(void);
void create_graph(void);

int main()
{
    create_graph();
    total_weight = prime();
    printf("%d", total_weight);
    return 0;
}

llu prime(void)
{
    int v, minpre, times;
    // prepare
    total_weight = 0, v = 0, times = 0;
    for (int i = 0; i < vt; i++)
        lowcost[i] = map[v][i], nearvex[i] = v;
    nearvex[v] = MARKED, times++;
    while (times < vt)
    {
        // recalculate lowcost and nearvex
        for (int i = 0; i < vt; i++)
        {
            if (nearvex[i] != MARKED)
                if (lowcost[i] > map[v][i])
                    lowcost[i] = map[v][i];
            for (int j = 0; j < vt; j++)
                if (nearvex[j] == MARKED && nearvex[i] != MARKED && map[j][i] < map[v][i])
                    nearvex[i] = j;
        }

        // find mincost of all lowcosts
        minpre = TRUE;
        for (int i = 0; i < vt; i++)
            if (nearvex[i] != MARKED)
            {
                if (minpre == TRUE)
                    v = i, minpre = FALSE;
                else if (lowcost[v] > lowcost[i])
                    v = i;
            }
        nearvex[v] = MARKED, times++, total_weight += lowcost[v];
    }
    return total_weight;
}

void create_graph(void)
{
    scanf("%d %ld", &vt, &et);
    for (int i = 0; i < vt; i++) //初始化邻接矩阵
    {
        for (int j = 0; j < vt; j++)
            map[i][j] = NOWAY;
        map[i][i] = 0;
    }
    int u, v;
    llu weight;
    for (int i = 0; i < et; i++)
    {
        scanf("%d %d %llu", &u, &v, &weight);
        map[u - 1][v - 1] = weight;
        map[v - 1][u - 1] = weight; //添加无向边
    }
    return;
}
