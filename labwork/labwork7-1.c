#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _edgenode
{ // type of edge node
    int adjvex;
    int weight;
    struct _edgenode *next;
} edgenode;

typedef struct _vertexnode
{ // type of vertex node
    int vertex;
    int indegree;
    edgenode *next;
} vertexnode;

typedef struct __graphtype
{ // type of graph
    vertexnode vtx_node[100];
    int vtx_total;
    int edge_total;
} graphtype;

graphtype *init_graph(graphtype *graph);
void paint_graph(graphtype *graph);
int main();

graphtype *init_graph(graphtype *graph) // init graph structure from input file
{
    int tempstart, tempend, tempweight;
    char ch;
    FILE *input = fopen("labwork7-1-input.txt", "r"); // open input file
    graph = (graphtype *)malloc(sizeof(graphtype));

    // scan the total number of v and a from first line
    fscanf(input, "%d %d", &graph->vtx_total, &graph->edge_total);

    // init all vertex nodes
    for (int i = 0; i < graph->vtx_total; i++)
    {
        graph->vtx_node[i].vertex = i + 1;
        graph->vtx_node[i].indegree = 0;
        graph->vtx_node[i].next = NULL;
    }

    while ((ch = fgetc(input)) != EOF)
    {
        fscanf(input, "%d %d %d", &tempstart, &tempend, &tempweight);
        for (int i = 0; i < graph->vtx_total; i++) // increase in-degrees
            if (graph->vtx_node[i].vertex == tempend)
            {
                graph->vtx_node[i].indegree += 1;
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
                    while (pointer_->next != NULL)
                        pointer_ = pointer_->next;
                    pointer_->next = newedge;
                }
                break;
            }
    }
    fclose(input);
    return graph;
}

void paint_graph(graphtype *graph)
{
    FILE *paint = fopen("labwork7-1-paint.txt", "w");
    fprintf(paint, "vertex:%d\tedge:%d\n", graph->vtx_total, graph->edge_total);
    for (int i = 0; i < graph->vtx_total; i++)
    {
        edgenode *pointer;
        fprintf(paint, "[%d|%d] -> ", graph->vtx_node[i].vertex, graph->vtx_node[i].indegree); // paint vertex node
        pointer = graph->vtx_node[i].next;                                                     // load pointer
        while (pointer != NULL)                                                                // paint edge nodes
        {
            fprintf(paint, "[%d|%d] -> ", pointer->adjvex, pointer->weight);
            pointer = pointer->next;
        }
        fprintf(paint, "^\n"); // paint endline;
    }
    fclose(paint);
    return;
}

int main()
{
    graphtype *graph;
    graph = init_graph(graph);
    paint_graph(graph);
    return 0;
}