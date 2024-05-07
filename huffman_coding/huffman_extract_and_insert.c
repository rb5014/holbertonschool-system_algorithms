#include "huffman.h"
void free_nested(void *data);
/**
 * huffman_extract_and_insert - extracts the two nodes of
 * the priority queue and insert a new one
 * @priority_queue: pointer to the priority queue to extract from
 * Return: 1 on success or 0 on failure
*/
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *node_1, *node_2, *new_nested;
	symbol_t *symbol_1, *symbol_2, *new_symbol;
	size_t freq;

	if (!priority_queue || (priority_queue->size < 2))
		return (0);


	node_1 = heap_extract(priority_queue);
	node_2 = heap_extract(priority_queue);
	if (!node_1 || !node_2)
		return (0);
	symbol_1 = (symbol_t *) node_1->data;
	symbol_2 = (symbol_t *) node_2->data;

	freq = symbol_1->freq + symbol_2->freq;
	new_symbol = symbol_create(-1, freq);
	if (!new_symbol)
		return (0);
	new_nested = binary_tree_node(NULL, new_symbol);
	if (!new_nested)
		return (free(new_symbol), 0);
	new_nested->left = node_1;
	new_nested->right = node_2;
	node_1->parent = new_nested;
	node_2->parent = new_nested;
	if (!heap_insert(priority_queue, new_nested))
	{
		heap_delete(priority_queue, free_nested);
		return (free(new_symbol), free(new_nested), 0);
	}
	return (1);
}
