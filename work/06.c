#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXN 5000010
#define NW -1

typedef struct _edgenode
{ // type of edge node
    int adjvex;
    int weight;
    struct _edgenode *next;
} edgenode;

typedef struct _vertexnode
{ // type of vertex node
    int vertex;
    int degree;
    edgenode *next;
} vertexnode;

typedef struct graph_of_adjacency_list
{ // type of graph
    vertexnode vtx_node[MAXN];
    int vtx_total;
    int edge_total;
    int start;
    int end;
} graph_adjlist;

int dis[MAXN]; //用于存储每个点到起点的最短距离
int st[MAXN];   //用于在更新最短距离时 判断当前的点的最短距离是否确定 是否需要更新

graph_adjlist *init_graph(graph_adjlist *graph);
void paint_graph(graph_adjlist *graph);
int dijkstra(graph_adjlist *graph);

int main()
{
    graph_adjlist *graph;
    graph = init_graph(graph);
    paint_graph(graph);
    return 0;
}

int dijkstra(graph_adjlist *graph)
{

    return 0;
}

//下面都是构建有向图的通用代码
graph_adjlist *init_graph(graph_adjlist *graph) // init graph structure from input file
{
    int tempstart, tempend, tempweight;
    char ch;
    graph = (graph_adjlist *)malloc(sizeof(graph_adjlist));

    scanf("%d %d %d %d", &graph->vtx_total, &graph->edge_total, &graph->start, &graph->end); // scan from first line
    for (int i = 0; i < graph->vtx_total; i++)                                               // init all vertex nodes
    {
        graph->vtx_node[i].vertex = i + 1;
        graph->vtx_node[i].degree = 0;
        graph->vtx_node[i].next = NULL;
    }

    for (int k = 0; k < graph->edge_total; k++)
    {
        scanf("%d %d %d", &tempstart, &tempend, &tempweight);
        for (int i = 0; i < graph->vtx_total; i++) // increase in-degrees
            if (graph->vtx_node[i].vertex == tempend)
            {
                graph->vtx_node[i].degree += 1;
                break;
            }
        for (int i = 0; i < graph->vtx_total; i++)      // link edge nodes after vertex nodes
            if (graph->vtx_node[i].vertex == tempstart) // find the corresponding vertex node
            {
                edgenode *newedge = (edgenode *)malloc(sizeof(edgenode)); // init new edgenode
                newedge->adjvex = tempend;
                newedge->weight = tempweight;
                newedge->next = NULL;

                vertexnode *pointer = &graph->vtx_node[i]; // load pointers
                edgenode *pointer_;

                if (pointer->next == NULL) // insert edge after vertex node
                    pointer->next = newedge;
                else // insert edge after edge node
                {
                    pointer_ = pointer->next;
                    while (pointer_->next != NULL) // go to the end of linked nodes
                        pointer_ = pointer_->next;
                    pointer_->next = newedge;
                }
                break;
            }
    }
    return graph;
}

void paint_graph(graph_adjlist *graph)
{
    FILE *paint = fopen("paint.md", "w");
    fprintf(paint, "## vertex:%d\tedge:%d\tstart:v%d\tend:v%d\n", graph->vtx_total, graph->edge_total, graph->start, graph->end);
    fprintf(paint, "```mermaid\ngraph LR;\n");
    for (int i = 0; i < graph->vtx_total; i++)
    {
        edgenode *pointer;
        pointer = graph->vtx_node[i].next; // load pointer
        while (pointer != NULL)
        {
            fprintf(paint, "    v%d--%d-->v%d\n", graph->vtx_node[i].vertex, pointer->weight, pointer->adjvex); // paint edge node
            pointer = pointer->next;                                                                                                          // goto next edge node;
        }
    }
    fprintf(paint, "```\n|vertex|indegree|\n|:---:|:--:|\n");
    for (int i = 0; i < graph->vtx_total; i++)
        fprintf(paint,"|v%d|%d|\n",graph->vtx_node[i].vertex,graph->vtx_node[i].degree);
    fclose(paint);
    return;
}
