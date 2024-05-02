#include "heap.h"

/**
 * heap_create - creates a Heap data structure
 * This function takes two void * parameters,
 * each one being the data stored in a node.
 * This function will return the difference between
 * the two data stored at those pointers.
 * It will be used to determine if a node’s value is
 * greater or lower than another, so we can build our heap
 * root must be set to NULL
 * size must be set to 0
 * @data_cmp: pointer to a comparison function
 * Return: pointer to the created heap_t structure, or NULL if it fails
 */
heap_t *heap_create(int (*data_cmp)(void *, void *))
{
	heap_t *new; /* Pointer to the new heap structure */

	/* Allocate memory for the new heap structure */
	new = malloc(sizeof(heap_t));
	if (new == NULL)
		return (NULL); /* Memory allocation failed */

	/* Initialize the new heap structure */
	new->root = NULL;		  /* Set root to NULL since the heap is empty */
	new->size = 0;			  /* Set size to 0 since there are no nodes yet */
	new->data_cmp = data_cmp; /* Set the comparison function pointer */

	return (new); /* Return a pointer to the created heap */
}
