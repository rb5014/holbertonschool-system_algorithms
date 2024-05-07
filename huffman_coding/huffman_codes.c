#include "huffman.h"

/**
 * print_huffman_codes - print the huffman codes recursively
 * @root: root of the huffman tree
 * @code: code to build and print
 * Return: 1 if it succeed, 0 if it fails
*/
int print_huffman_codes(binary_tree_node_t *root, size_t code)
{
	symbol_t *symbol;

	if (!root)
		return (0);

	symbol = root->data;
	if (!symbol)
		return (free(root), 0);

	if (symbol->data == -1)
	{
		if (!print_huffman_codes(root->left, code * 10) ||
			!print_huffman_codes(root->right, (code * 10) + 1))
			return (0);
	}
	else
		printf("%c: %lu\n", symbol->data, code);

	return (free(symbol), free(root), 1);
}

/**
 * huffman_codes - build the Huffman tree and
 * print the resulting Huffman codes for each symbol
 * @data: array of characters of size size
 * @freq: array containing the associated frequencies (of size size too)
 * @size: size of the two arrays
 * Return: 1 if it succeed, 0 if it fails
*/
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root = huffman_tree(data, freq, size);

	if (!root || !print_huffman_codes(root, 0))
		return (0);
	return (1);
}
