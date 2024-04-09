#include "graphs.h"

/**
 * graph_delete - delete all the vertices and edges of the graph,
 * and the graph itself
 * @graph: poiter to the graph to delete
*/
void graph_delete(graph_t *graph)
{
	vertex_t *tmp_v;
	edge_t *tmp_e;

	if (!graph)
		return;

	if (graph->vertices)
	{
		while (graph->vertices)
		{
			tmp_v = graph->vertices->next;
			if (graph->vertices->edges)
			{
				while (graph->vertices->edges)
				{
					tmp_e = graph->vertices->edges->next;
					free(graph->vertices->edges);
					graph->vertices->edges = tmp_e;
				}
			}
			free(graph->vertices->content);
			free(graph->vertices);
			graph->vertices = tmp_v;
		}
	}
	free(graph);

}
