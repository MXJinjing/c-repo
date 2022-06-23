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

typedef struct graph_of_adjacency_list
{ // type of graph
    vertexnode vtx_node[100];
    int vtx_total;
    int edge_total;
} graph_adjlist;

graph_adjlist *init_graph(graph_adjlist *graph);
void paint_graph(graph_adjlist *graph);
int *topological_sort(graph_adjlist *graph, int *saved);
int main();

graph_adjlist *init_graph(graph_adjlist *graph) // init graph structure from input file
{
    int tempstart, tempend, tempweight;
    char ch;
    FILE *input = fopen("labwork7-1-input.txt", "r"); // open input file
    graph = (graph_adjlist *)malloc(sizeof(graph_adjlist));

    fscanf(input, "%d %d", &graph->vtx_total, &graph->edge_total); // scan from first line
    for (int i = 0; i < graph->vtx_total; i++)                     // init all vertex nodes
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
                    while (pointer_->next != NULL) // go to the end of linked nodes
                        pointer_ = pointer_->next;
                    pointer_->next = newedge;
                }
                break;
            }
    }
    fclose(input);
    return graph;
}

void paint_graph(graph_adjlist *graph)
{
    FILE *paint = fopen("labwork7-1-paint.txt", "w");
    fprintf(paint, "vertex:%d\tedge:%d\n", graph->vtx_total, graph->edge_total);
    for (int i = 0; i < graph->vtx_total; i++)
    {
        edgenode *pointer;
        fprintf(paint, "[%d|%d] -> ", graph->vtx_node[i].vertex, graph->vtx_node[i].indegree); // paint vertex node
        pointer = graph->vtx_node[i].next;                                                     // load pointer
        while (pointer != NULL)
        {
            fprintf(paint, "[%d|%d] -> ", pointer->adjvex, pointer->weight); // paint edge node
            pointer = pointer->next;                                         // goto next edge node;
        }
        fprintf(paint, "^\n"); // paint end of line;
    }
    fclose(paint);
    return;
}

int *topological_sort(graph_adjlist *graph, int *saved)
{
    saved = (int *)malloc(sizeof(int) * (graph->vtx_total + 1));
    int ignored[100], tempindegree[100], top = -1, visited = 0;
    for (int i = 0; i < graph->vtx_total; i++) // init ignored array and tempindegree array
        ignored[i] = 0, tempindegree[i] = graph->vtx_node[i].indegree;
    do
    {
        int i;
        for (i = 0; i < graph->vtx_total; i++)
            if (ignored[i] + tempindegree[i] == 0) // if not visited and indegree is 0
            {
                saved[++top] = graph->vtx_node[i].vertex; // put vertex into stack 'saved'
                visited += 1;
                ignored[i] = 1; // ignored this vertexnode and its edge nodes
                if (graph->vtx_node[i].next != NULL)
                {
                    edgenode *pointer;
                    pointer = graph->vtx_node[i].next; // init pointer
                    while (pointer != NULL)
                    {
                        for (int j = 0; j < graph->vtx_total; j++) // find the corresponding vertex node
                            if (graph->vtx_node[j].vertex == pointer->adjvex)
                            {
                                tempindegree[j] -= 1; // discrease indegrere
                                break;
                            }
                        pointer = pointer->next;
                    }
                }
                if (i == graph->vtx_total)
                    i = 0; // reset i
            }
        if (i = graph->vtx_total && visited < graph->vtx_total)
        {
            printf("error: Could not complete topological sort, there is a cycle\n");
            return NULL;
        }
    } while (visited < graph->vtx_total);
    return saved; // return saved results
}

int main()
{
    graph_adjlist *graph;
    graph = init_graph(graph);
    paint_graph(graph);
    int *saved = topological_sort(graph, saved);

    for (int i = 0; i < graph->vtx_total; i++) // write topological_sort
        printf("v%d ", *(saved + i));
    return 0;
}