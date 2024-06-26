#include "nary_trees.h"

/**
 * path_exists - checks if a path exists in an N-ary tree
 * @root: pointer to the root node of the tree
 * @path: NULL terminated array of strings
 * The string at the index i can be the content of one
 * of the nodes of the tree at the depth i.
 * Return: 1 if all elements of path are present in the tree and
 * if for an element of path at the index i is present in one
 * of the nodes at the depth i.
 * And of course, all the nodes must be linked to form a path.
*/
int path_exists(nary_tree_t const *root, char const * const *path)
{
	size_t path_index;

	/* Check for invalid input parameters */
	if (!root || !path || !*path)
		return (0);

	/* Iterate through each element of the path */
	for (path_index = 0; path[path_index]; ++path_index, root = root->children)
	{
		/* Search for the current element in the current level of the tree */
		while (root && strcmp(root->content, path[path_index]) != 0)
			root = root->next;

		/* Current element is not found at the current level, path does not exist */
		if (!root)
			return (0);
	}

	/* All elements of the path are found in the tree, and they form a path */
	return (1);
}
