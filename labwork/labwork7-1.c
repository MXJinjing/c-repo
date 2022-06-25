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
    int degree;
    edgenode *next;
} vertexnode;

typedef struct graph_of_adjacency_list
{ // type of graph
    vertexnode vtx_node[100];
    int vtx_total;
    int edge_total;
} graph_adjlist;

graph_adjlist *init_graph(graph_adjlist *graph, int mode);
void paint_graph(graph_adjlist *graph, int number);
int *topological_sort(graph_adjlist *graph, int *ve);
int *inverse_topological_sort(graph_adjlist *graph, int *vl, int *ve);
int *calculate_ae(graph_adjlist *graph, int *ve, int *ae);
int *calculate_al(graph_adjlist *graph, int *vl, int *al);
void critical_path(graph_adjlist *graph, int *ae, int *al);
int main();

graph_adjlist *init_graph(graph_adjlist *graph, int mode) // init graph structure from input file
{
    int tempstart, tempend, tempweight;
    char ch;
    FILE *input = fopen("labwork7-1-input.txt", "r"); // open input file
    graph = (graph_adjlist *)malloc(sizeof(graph_adjlist));

    fscanf(input, "%d %d", &graph->vtx_total, &graph->edge_total); // scan from first line
    for (int i = 0; i < graph->vtx_total; i++)                     // init all vertex nodes
    {
        graph->vtx_node[i].vertex = i + 1;
        graph->vtx_node[i].degree = 0;
        graph->vtx_node[i].next = NULL;
    }

    while ((ch = fgetc(input)) != EOF)
    {
        if (mode == 0)
            fscanf(input, "%d %d %d", &tempstart, &tempend, &tempweight);
        if (mode == 1)
            fscanf(input, "%d %d %d", &tempend, &tempstart, &tempweight);
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
    fclose(input);
    return graph;
}

void paint_graph(graph_adjlist *graph, int number)
{
    char s[100] = "labwork7-1-paint-0.txt";
    s[17] = number + 48;
    FILE *paint = fopen(s, "w");
    fprintf(paint, "vertex:%d\tedge:%d\n", graph->vtx_total, graph->edge_total);
    for (int i = 0; i < graph->vtx_total; i++)
    {
        edgenode *pointer;
        fprintf(paint, "[%d|%d] -> ", graph->vtx_node[i].vertex, graph->vtx_node[i].degree); // paint vertex node
        pointer = graph->vtx_node[i].next;                                                   // load pointer
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

int *topological_sort(graph_adjlist *graph, int *ve)
{
    ve = (int *)malloc(sizeof(int) * (graph->vtx_total + 1));
    int saved[100], ignored[100], tempindegree[100], top = -1, visited = 0;
    for (int i = 0; i < graph->vtx_total; i++) // init ignored, tempindegree, vw array
        ignored[i] = 0, tempindegree[i] = graph->vtx_node[i].degree, ve[i] = 0;
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
                                ve[j] = (ve[j] > ve[i] + pointer->weight) ? ve[j] : (ve[i] + pointer->weight); // find longeset path
                                tempindegree[j] -= 1;                                                          // discrease indegrere
                                break;
                            }
                        pointer = pointer->next;
                    }
                }
                if (i == graph->vtx_total)
                    i = 0; // reset i
            }
        if (i > graph->vtx_total && visited < graph->vtx_total)
        {
            printf("error: Could not complete topological sort, there is a cycle\n");
            return NULL;
        }
    } while (visited < graph->vtx_total);
    for (int i = 0; i < graph->vtx_total; i++)
    {
        printf("ve[%d] = %d\n", i, ve[i]);
    }
    return ve; // return saved results
}

int *inverse_topological_sort(graph_adjlist *graph, int *vl, int *ve)
{
    vl = (int *)malloc(100 * sizeof(int));
    int saved[100], ignored[100], tempoutdegree[100], top = -1, visited = 0, vemax = 0;
    for (int i = 0; i < graph->vtx_total; i++) // find max ve
        vemax = (vemax > ve[i]) ? vemax : ve[i];
    for (int i = 0; i < graph->vtx_total; i++) // init ignored, tempoutdegree, vl array
        ignored[i] = 0, tempoutdegree[i] = graph->vtx_node[i].degree, vl[i] = vemax;
    do
    {
        int i;
        for (i = 0; i < graph->vtx_total; i++)
        {
            if (ignored[i] + tempoutdegree[i] == 0) // if not visited and outdegree is 0
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
                                vl[j] = (vl[j] < vl[i] - pointer->weight) ? vl[j] : (vl[i] - pointer->weight); // find shortest path
                                tempoutdegree[j] -= 1;                                                         // discrease indegrere
                                break;
                            }
                        pointer = pointer->next;
                    }
                }
                if (i == graph->vtx_total)
                    i = 0; // reset i
            }
        }
        if (i > graph->vtx_total && visited < graph->vtx_total)
        {
            printf("i = %d, visited = %d\n", i, visited);
            printf("error: Could not complete topological sort, there is a cycle\n");
            return NULL;
        }
    } while (visited < graph->vtx_total);
    for (int i = 0; i < graph->vtx_total; i++)
    {
        printf("vl[%d] = %d\n", i, vl[i]);
    }
    return vl; // return saved results
}

int *calculate_ae(graph_adjlist *graph, int *ve, int *ae)
{
    ae = (int *)malloc((graph->edge_total + 1) * sizeof(int));
    int j = 0;
    for (int i = 0; i < graph->vtx_total; i++)
    {
        edgenode *pointer;
        pointer = graph->vtx_node[i].next; // init pointer
        while (pointer != NULL)
        {
            ae[j++] = ve[i];
            pointer = pointer->next;
        }
    }
    for (int i = 0; i < graph->edge_total; i++)
    {
        printf("ae[%d] = %d\n", i, ae[i]);
    }
    return ae; // return saved results
}

int *calculate_al(graph_adjlist *graph, int *vl, int *al)
{
    al = (int *)malloc((graph->edge_total + 1) * sizeof(int));
    int m = 0;
    for (int i = 0; i < graph->vtx_total; i++)
    {
        edgenode *pointer;
        pointer = graph->vtx_node[i].next; // init pointer
        while (pointer != NULL)
        {
            for (int j = 0; j < graph->vtx_total; j++) // find the corresponding vertex node
                if (graph->vtx_node[j].vertex == pointer->adjvex)
                    al[m++] = vl[j] - pointer->weight;
            pointer = pointer->next;
        }
    }
    for (int i = 0; i < graph->edge_total; i++)
    {
        printf("al[%d] = %d\n", i, al[i]);
    }
    return al; // return saved results
}

void critical_path(graph_adjlist *graph, int *ae, int *al)
{
    FILE *output = fopen("labwork7-1-output.txt", "w");
    int l_e[100], cvex[100], top = 0, top_ = 0, saved = 0;

    for (int i = 0; i < graph->edge_total; i++)
    {
        l_e[i] = al[i] - ae[i];
        printf("l_e[%d] = %d\n", i, l_e[i]);
    }
    int j = 0;
    for (int i = 0; i < graph->vtx_total; i++)
    {
        edgenode *pointer;
        pointer = graph->vtx_node[i].next; // init pointer
        while (pointer != NULL)
        {
            if (l_e[j] == 0)
            {
                for (int k = 0; k < top; k++)
                {
                    if (cvex[k] == graph->vtx_node[i].vertex)
                    {
                        saved = 1;
                        break;
                    }
                }
                if (saved == 0) //saved the start vertex if not saved
                    cvex[top++] = graph->vtx_node[i].vertex;
                else
                    saved = 0;
                for (int k = 0; k < top; k++)
                {
                    if (cvex[k] == pointer->adjvex)
                    {
                        saved = 1;
                        break;
                    }
                }
                if (saved == 0) //saved the end vertex if not saved
                    cvex[top++] = pointer->adjvex;
                else
                    saved = 0;
            }
            j++, pointer = pointer->next;
        }
    }
    for (int i = 0; i < top; i++)
        fprintf(output, "v%d ", cvex[i]);
    fclose(output);
    return;
}

int main()
{
    graph_adjlist *graph, *graph_;
    graph = init_graph(graph, 0);
    graph_ = init_graph(graph, 1);
    paint_graph(graph, 0);
    paint_graph(graph_, 1);
    int *ve = topological_sort(graph, ve);
    int *vl = inverse_topological_sort(graph_, vl, ve);
    int *ae = calculate_ae(graph, ve, ae);
    int *al = calculate_al(graph, vl, al);
    critical_path(graph, ae, al);
    return 0;
}