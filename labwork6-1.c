/*
    要求图用邻接表方式存储，输入一个图，进行图的深度优先遍历及广度优先遍历。
    扩展问题：
    (1)用邻接矩阵实现，程序有哪些不同？
    (2)用图的遍历算法解决迷宫问题的最短路径，如果不存在路径，提示。
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct adjacency_table_node{
    int key;
    struct adjacency_table_node * next;
}node;

void graph_dfs(node * graph, int row)
{
    if(graph == NULL)return;
    int s[50],top = 0, visited = 1, judge;
    node * flag = graph->next;
    node * prev[50];

    //first node of graph
    s[top ++]  = graph->key;
    printf("%d Now Visited\n",graph->key);

    //the other nodes of graph
    while(visited < row)
    {
        judge = 0;
        for(int i = 0; i < visited; i++)
        {
            if(s[i] == flag->key)
            {
                printf("s[%d] = %d & flag->key = %d\n", i, s[i],flag->key);
                judge = 1;
            }
        }
        if(judge == 0)
        {
            printf("%d Now Visited\n",flag->key);
            s[visited ++] = flag->key;
            prev[top++] = flag;
            flag = (graph + flag->key - 1)->next;
        }
        else 
        {
            printf("%d Visited and skip\n",flag->key);
             if(flag->next != NULL)
                flag = flag->next;
             else
                flag = prev[--top];
        }
    }
    for(int i = 0; i < row; i++)
        printf("%d ", s[i]);
    printf("\n");
    return;
}

void create_graph(node * graph_out, int * graph_in, int row)
{
    //init graph_out
    for(int i = 0; i < row; i++)
    {
        graph_out[i].key = i+1;
        graph_out[i].next = NULL;
    }
    for(int i = 0; i < row; i ++)
    {
        for(int j = 0; j < row; j++)
        {
            if(* (graph_in + i*row + j) != 0)
            {
                    node * head, * temp = (node *)malloc(sizeof(node));
                    head = &graph_out[i];
                    temp->key = j + 1;
                    temp->next = NULL;
                    while( head->next != NULL)
                    {
                        head = head->next;
                    }
                    head->next =temp;
            }
        }
    }
    for(int i = 0; i < row; i++)
    {
        node * head = &graph_out[i];
        while(head != NULL)
        {
            printf("%d->",head->key);
            head = head->next;
        }
        printf("^\n");
    }
}
int main()
{
    int row = 5;
    node graph[5];

    int _graph[5][5] =
    {
        {0,1,1,0,0},
        {1,0,1,0,1},
        {1,1,0,1,0},
        {0,0,1,0,1},
        {0,1,0,1,0},
    };

    create_graph(graph,(int *)_graph,row);
    graph_dfs(graph,row);
    return 0;
}