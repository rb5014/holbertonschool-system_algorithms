#include "huffman.h"
void binary_tree_print(const binary_tree_node_t *heap, int (*print_data)(char *, void *));
int symbol_print(char *buffer, void *data);
/**
 * huffman_tree - builds the Huffman tree
 * @data: array of characters of size size
 * @freq: array containing the associated frequencies (of size size too)
 * @size: size of the two arrays
 * Return: pointer to the root node of the Huffman tree, or NULL if it fails
*/
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *min_heap = huffman_priority_queue(data, freq, size);

	if (min_heap == NULL)
		return (NULL);
	while (min_heap->size > 1)
	{
		if (huffman_extract_and_insert(min_heap) == 0)
			return (NULL);

	}
	free(min_heap->root);
	free(min_heap);
	return (min_heap->root->data);
}
