#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _edgenode {
    int adjvex;
    int weight;
    struct _edgenode *next;
} edgenode;

typedef struct _vertexnode {
    int vertex;
    int indegree;
    edgenode *next;
} vertexnode;

typedef struct __graphtype {
    vertexnode vnode[100];
    int v_total;
    int a_total;
} graphtype;

void init_graph(graphtype *graph)
{

    int tempstart, tempend, tempweight;
    char ch;
    FILE *input = fopen("labwork7-1-input.txt", "r");
    printf("open input file\n", input);
    graph = (graphtype *)malloc(sizeof(graphtype));
    fscanf(input, "%d %d", &graph->v_total, &graph->a_total);
    printf("%d %d\n", graph->v_total, graph->a_total);

    printf("init graph\n");
    for (int i = 0; i < graph->v_total; i++)
    {
        printf("i = %d\n", i);
        graph->vnode[i].vertex = i + 1;
        graph->vnode[i].next = NULL;
    }
    while ((ch = fgetc(input)) != EOF)
    {
        fscanf(input, "%d %d %d", &tempstart, &tempend, &tempweight);
        printf("%d %d %d\n", tempstart, tempend, tempweight);
        for (int i = 0; i < graph->v_total; i++)
        {
            if (graph->vnode->vertex == tempstart)
            {
                insert_edge(graph->vnode[i]);
                break;
            }
        }
    }
    fclose(input);
    return;
}

void insert_edge(vertexnode node)
{
    return;
}

int main()
{
    graphtype *graph;
        init_graph(graph);
    return 0;
}