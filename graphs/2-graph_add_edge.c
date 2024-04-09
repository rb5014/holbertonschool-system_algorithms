#include "graphs.h"

/**
 * create_edge - create and initialize an edge
 * @dest: Pointer to the connected vertex
 * Return: pointer to the created edge, or NULL on failure
*/
edge_t *create_edge(vertex_t *dest)
{
	edge_t *new = malloc(sizeof(edge_t));

	if (!new)
		return (NULL);
	new->dest = dest;
	new->next = NULL;

	return (new);
}

/**
 * vertice_add_edge - adds an edge in a vertice's edge list
 * @src: the vertex to make the connection from
 * @dest: the vertex to connect to
 * @type: the type of edge
 * If type is BIDIRECTIONAL, recursively add src to dest's edge list
 * Return: 1 if success, 0 otherwise
*/
int vertice_add_edge(vertex_t *src, vertex_t *dest, edge_type_t type)
{
	edge_t *tmp_edge;

	if (!src->edges)
		src->edges = create_edge(dest);
	else
	{
		tmp_edge = src->edges;
		while (tmp_edge->next)
			tmp_edge = tmp_edge->next;
		tmp_edge->next = create_edge(dest);
		if (!tmp_edge->next)
			return (0);
	}
	if (type == BIDIRECTIONAL)
		return (vertice_add_edge(dest, src, UNIDIRECTIONAL));
	return (1);
}

/**
 * graph_add_edge - adds an edge between two vertices to an existing graph
 * @graph: pointer to the graph to add the edge to
 * @src: the string identifying the vertex to make the connection from
 * @dest: the string identifying the vertex to connect to
 * @type: the type of edge
 * UNIDIRECTIONAL: Only one edge created connecting src to dest
 * BIDIRECTIONAL: Two edges created, connecting src to dest AND dest to src.
 * Return: 1 on success, or 0 on failure. On failure,
 * no edge must have be created, and there must be no memory leak.
 * If either src or dest are not found in any vertex of graph,
 * function must fail, and there must be no leak
*/
int graph_add_edge(
	graph_t *graph, const char *src, const char *dest, edge_type_t type)
{
	vertex_t *tmp = NULL, *tmp_src = NULL, *tmp_dest = NULL;

	if (!graph || !graph->nb_vertices || !src || !dest)
		return (0);

	tmp = graph->vertices;

	while (!(tmp_src && tmp_dest))
	{
		if (!tmp)
			return (0);
		if (strcmp(src, tmp->content) == 0)
			tmp_src = tmp;
		if (strcmp(dest, tmp->content) == 0)
			tmp_dest = tmp;
		tmp = tmp->next;
	}
	return (vertice_add_edge(tmp_src, tmp_dest, type));
}
