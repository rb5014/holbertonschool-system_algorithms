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

	binary_tree_print(min_heap->root->data, symbol_print);

	while (min_heap->root->left && min_heap->root->right)
	{
		huffman_extract_and_insert(min_heap);
	}
	return (min_heap->root->data);
}
