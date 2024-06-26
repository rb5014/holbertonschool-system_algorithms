#include "graphs.h"

/**
 * breadth_first_traverse - goes through a graph using breadth-first algorithm
 * @graph: pointer to the graph to traverse.
 * The traversal must start from the first vertex in the vertices list.
 * @action: pointer to a function to be called for each visited vertex,
 * its parameters are:
 *		v -> A const pointer to the visited vertex
 *		depth -> The depth of v, from the starting vertex
 * Return: the biggest vertex depth, or 0 on failure
*/
size_t
breadth_first_traverse(const graph_t *graph,
					   void (*action)(const vertex_t *v, size_t depth))
{
	edge_t *tmp_edge = NULL;
	vertex_t *current_vertex = NULL;
	vertex_t **queue;
	size_t *visited;
	size_t *depth;
	size_t front = 0, rear = 0, current_depth = 0, max_depth = 0;

	if (!graph || !graph->vertices)
		return (0);
	queue = malloc(sizeof(vertex_t *) * graph->nb_vertices);
	visited = calloc(graph->nb_vertices, sizeof(size_t));
	depth = calloc(graph->nb_vertices, sizeof(size_t));
	if (!queue || !visited || !depth)
		goto free_all;
	queue[rear++] = graph->vertices;
	visited[graph->vertices->index] = 1;
	while (front != rear)
	{
		current_vertex = queue[front];
		current_depth = depth[front];
		if (current_depth > max_depth)
			max_depth = current_depth;
		action(current_vertex, current_depth);
		front++;
		tmp_edge = current_vertex->edges;
		while (tmp_edge)
		{
			if (!visited[tmp_edge->dest->index])
			{
				visited[tmp_edge->dest->index] = 1;
				queue[rear] = tmp_edge->dest;
				depth[rear] = current_depth + 1;
				rear++;
			}
			tmp_edge = tmp_edge->next;
		}
	}
free_all:
	if (visited)
		free(visited);
	if (queue)
		free(queue);
	if (depth)
		free(depth);
	return (max_depth);
}
