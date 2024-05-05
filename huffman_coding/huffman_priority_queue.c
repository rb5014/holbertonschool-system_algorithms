#include "huffman.h"

/**
 * data_cmp - Compares two symbols frequency
 *
 * @p1: First pointer
 * @p2: Second pointer
 *
 * Return: Difference between the frequecies
 */
int data_cmp(void *p1, void *p2)
{
	binary_tree_node_t *n1, *n2;
	symbol_t *s1, *s2;

	n1 = (binary_tree_node_t *)p1;
	n2 = (binary_tree_node_t *)p2;
	s1 = (symbol_t *)n1->data;
	s2 = (symbol_t *)n2->data;

	return ((int)(s1->freq - s2->freq));
}

/**
 * huffman_priority_queue - creates a priority queue for
 * the Huffman coding algorithm
 * @data: array of characters of size size
 * @freq: array containing the associated frequencies (of size size too)
 * @size: size of the arrays
 * Return: pointer to the created min heap (also called priority queue)
 * Each node of this priority queue stores
 * a heap leaf node containing a symbol_t *
 *		node->data is a binary_tree_node_t * (let’s call it nested)
 *		nested->data is our symbol_t *
*/
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *heap;
	binary_tree_node_t *nested;
	symbol_t *symbol;
	size_t i;

	if (size == 0)
		return (NULL);

	heap = heap_create(data_cmp);

	for (i = 0; i < size; i++)
	{
		symbol = symbol_create(data[i], freq[i]);
		nested = binary_tree_node(NULL, symbol);
		heap_insert(heap, nested);
	}
	return (heap);
}
