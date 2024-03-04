#include "rb_trees.h"

/**
 * array_to_rb_tree - builds a Binary Search Tree from an array
 * @array: pointer to the first element of the array to be converted
 * @size: number of elements in the array
 * Return: pointer to the root node of the created R-B tree, or NULL on failure
 */
rb_tree_t *array_to_rb_tree(int *array, size_t size)
{
	size_t i;
	rb_tree_t *root = NULL;

	for (i = 0; i < size; i++)
		rb_tree_insert(&root, array[i]);
	return (root);
}
