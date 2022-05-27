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

void graph_dfs(node * graph, int row, FILE * file)
{
    if(graph == NULL)return;//return if graph is empty
    int judge[50] = {0}, top = -1, visited = 0;
    node * flag = graph;//a flag for wondering the graph
    node * prev[50];//a stack to save prev nodes
    
    while(visited < row)//repeat until all nodes are visited
    {
        if(judge[flag->key] == 0)//if node not visited
        {
            judge[flag->key] = 1;//set node to visited
            prev[++ top] = flag;
            fprintf(file,"%d",flag->key);
            visited ++;
            flag = (graph + flag->key);//travel to another head
        }
        else //if node has been visited
        {
            if(flag->next != NULL)
                flag = flag->next;
            else
                flag = prev[top --];//return back to previous node
        }
    }
    fprintf(file, "\n");
    return;
}

void graph_bfs (node * graph, int row, FILE * file)
{
    if(graph == NULL)return;
    int judge[50] = {0}, head = 0, tail = 0, queue[50];
    node * flag;
    //visit first node
    queue[0] = graph->key;
    judge[queue[0]] = 1;
    //visit the other nodes
    while(head <= tail)//repeat until all nodes are visited
    {
        //find the exact match node according to the keyword
        for(int i = 0; i < row; i ++)
            if((graph + i)->key == queue[head])
            {
                flag = graph + i;
                break;
            }
        fprintf(file,"%d",flag->key);
        flag = flag->next;
        while(flag != NULL)
        {
            //if not visited, put into the queue
            if(judge[flag->key] == 0)
            {
                queue[++tail] = flag->key;
                judge[flag->key] = 1;//set to visited
            }
            flag = flag->next;
        }
        head ++;
    }
    fprintf(file,"\n");
    return;
}

void create_graph(node * graph_out, int * graph_in, int row)
{
    //init graph_out
    for(int i = 0; i < row; i ++)
    {
        graph_out[i].key = i+1;
        graph_out[i].next = NULL;
    }
    //link all the nodes
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
                        head = head->next;
                    head->next =temp;
            }
        }
    }
    //print the new graph
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
    FILE * out = fopen("labwork6-1-out.txt","w");//open output file
    int row = 5;
    node graph[5];

    int _graph[5][5] =
    {
        {0,1,1,0,0},
        {1,0,1,0,1},
        {1,1,0,1,0},
        {0,0,1,0,1},
        {0,1,0,1,0},
    };//new table of the graph

    create_graph(graph,(int *)_graph,row);
    graph_dfs(graph,row,out);
    graph_bfs(graph,row,out);
    return 0;
}
