#include "graphs.h"

/**
 * create_vertex - create and initialize a vertex, also incrementing the number
 * of vertices in the graph
 * @nb_vertices: pointer to number of vertices to increment
 * @str: string to store in the new vertex
 * Return: pointer to the created vertex, or NULL on failure
*/
vertex_t *create_vertex(size_t *nb_vertices, const char *str)
{
	vertex_t *new = malloc(sizeof(vertex_t));

	if (!new)
		return (NULL);
	new->content = str != NULL ? strdup(str) : strdup("");
	new->index = (*nb_vertices)++;
	new->edges = NULL;
	new->nb_edges = 0;
	new->next = NULL;

	return (new);
}

/**
 * graph_add_vertex - adds a vertex to an existing graph
 * The vertex must store a copy of the string str
 * If a vertex in graph already stores the string str,
 * the function must fail, and there must be no leak
 * @graph: pointer to the graph to add the vertex to
 * @str: string to store in the new vertex
 * Return: pointer to the created vertex, or NULL on failure
*/
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *new = NULL, *tmp = NULL;

	if (!graph)
		return (NULL);
	if (!graph->vertices)
	{
		graph->vertices = create_vertex(&(graph->nb_vertices), str);
		return (graph->vertices);
	}
	else
		tmp = graph->vertices;
	while (tmp)
	{
		if (str && (strcmp(str, tmp->content) == 0))
			break;
		if (!tmp->next)
		{
			new = create_vertex(&(graph->nb_vertices), str);
			tmp->next = new;
			break;
		}
		tmp = tmp->next;
	}
	return (new);
}

