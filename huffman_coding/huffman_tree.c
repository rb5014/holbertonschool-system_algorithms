#include "huffman.h"
/**
 * huffman_tree - builds the Huffman tree
 * @data: array of characters of size size
 * @freq: array containing the associated frequencies (of size size too)
 * @size: size of the two arrays
 * Return: pointer to the nested root node of the Huffman tree,
 * or NULL if it fails
*/
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *min_heap = huffman_priority_queue(data, freq, size);
	binary_tree_node_t *nested;

	if (min_heap == NULL)
		return (NULL);

	while (min_heap->size > 1)
	{
		if (huffman_extract_and_insert(min_heap) == 0)
			return (NULL);

	}
	nested = min_heap->root->data;
	free(min_heap->root);
	free(min_heap);
	return (nested);
}
