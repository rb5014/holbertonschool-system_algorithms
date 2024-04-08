#include "graphs.h"

/**
 * graph_create - allocates memory to store a graph_t structure,
 * and initializes its content
 * Return: pointer to the allocated structure, or NULL on failure
*/
graph_t *graph_create(void)
{
	graph_t *new = malloc(sizeof(graph_t));

	if (!new)
		return (NULL);
	new->nb_vertices = 0;
	new->vertices = NULL;
	return (new);
}
