#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXN 50010
#define NOWAY 32767
#define TRUE 1
#define FALSE 0

int map[MAXN][MAXN], visited[MAXN], dis[MAXN], start, end, vt, et;
void create_graph(void);
void dijkstra(void);

int main()
{
    create_graph();
    dijkstra();
    printf("%d",dis[end-1]);
}

void dijkstra(void)
{
    int min, getminstart, u_now, times;
    for (int j = 0; j < vt; j++)
        visited[j] = FALSE;

    //初始化dis数组
    dis[start - 1] = 0;
    u_now = start - 1;
    for (int v = 0; v < vt; v++)
        dis[v] = map[u_now][v];
    times = 0;

    while (times < vt)
    {
        visited[u_now] = TRUE;
        times++;
        getminstart = FALSE;
        for (int v = 0; v < vt; v++)
        {
            if (visited[v] == FALSE)
            {
                //确定不确定的数据
                if (dis[v] > map[u_now][v] + dis[u_now])
                         dis[v] = map[u_now][v] + dis[u_now];

                //计算最小值进入下一个节点
                if (getminstart == FALSE)
                        min = v, getminstart = TRUE;
                else
                        min = dis[min] < dis[v] ? min : v;
            }
        }
        u_now = min;
    }
    return;
}


void create_graph(void)
{
    scanf("%d %d %d %d", &vt, &et, &start, &end);
    for (int i = 0; i < vt; i++) //初始化邻接矩阵
    {
        for (int j = 0; j < vt; j++)
            map[i][j] = NOWAY;
        map[i][i] = 0;
    }
    int u, v, weight;
    for (int i = 0; i < et; i++) //添加有向边
    {
        scanf("%d %d %d", &u, &v, &weight);
        map[u - 1][v - 1] = weight;
        map[v - 1][u - 1] = weight;
    }
    return;
}
