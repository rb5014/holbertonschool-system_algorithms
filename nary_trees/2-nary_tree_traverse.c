#include "nary_trees.h"

/**
 * nary_tree_traverse - goes through an N-ary tree, node by node
 * @root: pointer to the root node of the tree to traverse
 * @action: pointer to a function to execute for each node being traversed.
 * Its arguments are:
 *		node: pointer to the node being traversed
 *		depth: depth of the node being traversed
 * Return: the biggest depth of the tree pointed to by root
*/
size_t nary_tree_traverse(nary_tree_t const *root,
						  void (*action)(nary_tree_t const *node, size_t depth))
{
	static size_t current_depth;
	static size_t biggest_depth;

	if (!root)
		return (biggest_depth);

	if (current_depth > biggest_depth)
		biggest_depth = current_depth;

	action(root, current_depth);

	if (root->children)
	{
		current_depth++;
		nary_tree_traverse(root->children, action);
		current_depth--;
	}
	if (root->next)
		nary_tree_traverse(root->next, action);

	return (biggest_depth);
}
