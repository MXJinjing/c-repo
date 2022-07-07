#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXN 5000010
#define NOWAY 32767
#define TRUE 1
#define FALSE 0

int map[MAXN][MAXN], visited[MAXN], dis[MAXN], start, end, vt, et;
void create_graph(void);
void paint_graph(FILE *paint);
void dijkstra(FILE *file);
void print_dis(FILE *file);

int main()
{
    FILE *file = fopen("paint2.md", "w");
    create_graph();
    paint_graph(file);
    dijkstra(file);
    fclose(file);
    printf("%d", dis[end - 1]);
    return 0;
}

void dijkstra(FILE *file)
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
        fprintf(file, "### No.%d\nnow visit: v%d\n", 1 + times, 1 + u_now);
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
        print_dis(file);
        fprintf(file, "min: v%d = %d\n\n", min, dis[min]);
    }
    return;
}

void print_dis(FILE *file)
{
    for (int j = 0; j < vt; j++)
        fprintf(file, "|v%d", j + 1);
    fprintf(file, "|\n");
    for (int j = 0; j < vt; j++)
        fprintf(file, "|:-:");
    fprintf(file, "|\n");
    for (int j = 0; j < vt; j++)
        if (dis[j] != NOWAY)
            fprintf(file, "|%d", dis[j]);
        else
            fprintf(file, "|∞");
    fprintf(file, "|\n\n");
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
    for (int i = 0; i < et; i++)
    {
        scanf("%d %d %d", &u, &v, &weight);
        map[u - 1][v - 1] = weight;
        map[v - 1][u - 1] = weight; //添加无向边
    }
    return;
}

void paint_graph(FILE *paint)
{
    fprintf(paint, "## vertex:%d\tedge:%d\tstart:v%d\tend:v%d\n```mermaid\ngraph TB;\n", vt, et, start, end);
    for (int i = 0; i < vt; i++)
        for (int j = i; j < vt; j++)
            if (map[i][j] != NOWAY && map[i][j] != 0)
                fprintf(paint, "    v%d-.%d.-v%d\n", i + 1, map[i][j], j + 1);
    fprintf(paint, "```\n");
    return;
}