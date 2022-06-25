            if (l_e[j] == 0)
            {
                printf("path[%d] = %d\n", j, l_e[j]);
                printf("now start = %d, end = %d\n", graph->vtx_node[i].vertex, pointer->adjvex);
            }
            for (int k = 0; k < top; k++)
            {
                if (cvex[k] == graph->vtx_node[i].vertex)
                {
                    saved = 1;
                    break;
                }
            }
            if (saved == 0)
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
            if (saved == 0)
                cvex[top++] = pointer->adjvex;
            else
                saved = 0;