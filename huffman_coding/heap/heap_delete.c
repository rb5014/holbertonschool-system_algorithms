#include "heap.h"
/**
 * free_node - free nodes recursively
 * @node: pointer to the node to free
 * @free_data: pointer to the function to free the node's data
 * If free_data is NULL, data isn't freed
*/
void free_node(binary_tree_node_t *node, void (*free_data)(void *))
{
	if (node->left)
		free_node(node->left, free_data);
	if (node->right)
		free_node(node->right, free_data);
	if (free_data)
		free_data(node->data);
	free(node);
}

/**
 * heap_delete - deallocates a heap
 * @heap: pointer to the heap to delete
 * @free_data: pointer to a function that will be used
 * to free the content of a node
 * If free_data is NULL, the data stored in the nodes must not be freed
*/
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (heap && heap->root)
		free_node(heap->root, free_data);
	free(heap);
}
