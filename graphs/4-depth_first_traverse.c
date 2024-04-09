#include "graphs.h"
static size_t *visited_indexes, n_visited, max_depth;

/**
 * is_visited - Check if vertice already visited
 * @index: index of the vertice to check
 * Return: 1 if already visited, 0 otherwise
*/
int is_visited(size_t index)
{
	size_t i;

	for (i = 0; i < n_visited; i++)
	{
		if (index == visited_indexes[i])
			return (1);
	}
	return (0);
}

/**
 * visit_vertice - visit vertex recursively
 * @v: vertice to visit
 * @depth: current depth of the edge
 * @action: pointer to a function to be called for each visited vertex
*/
void visit_vertice(vertex_t *v, size_t depth,
				   void (*action)(const vertex_t *v, size_t depth))
{
	size_t i;
	edge_t *tmp;

	n_visited++;
	visited_indexes[n_visited - 1] = v->index;
	action(v, depth);

	if (depth > max_depth)
		max_depth = depth;
	tmp = v->edges;
	for (i = 0; i < v->nb_edges; i++)
	{
		if (is_visited(tmp->dest->index) == 0)
		{
			depth++;
			visit_vertice(tmp->dest, depth, action);
			depth--;
		}
		tmp = tmp->next;
	}
}

/**
 * depth_first_traverse - goes through a graph using the depth-first algorithm
 * @graph: pointer to the graph to traverse.
 * The traversal must start from the first vertex in the vertices list.
 * @action: pointer to a function to be called for each visited vertex,
 * its parameters are:
 *		v -> A const pointer to the visited vertex
 *		depth -> The depth of v, from the starting vertex
 * Return: the biggest vertex depth, or 0 on failure
*/
size_t
depth_first_traverse(const graph_t *graph,
					 void (*action)(const vertex_t *v, size_t depth))
{
	size_t i;
	vertex_t *tmp;

	if (!graph || !graph->vertices)
		return (0);

	visited_indexes = malloc(sizeof(size_t) * graph->nb_vertices);

	tmp = graph->vertices;
	for (i = 0; i < graph->nb_vertices; i++)
	{
		if (is_visited(tmp->index) == 0)
		{
			visit_vertice(tmp, 0, action);
			tmp = tmp->next;
		}
	}
	free(visited_indexes);
	return (max_depth);
}
