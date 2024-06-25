#include "nary_trees.h"

/**
 * nary_tree_delete - deallocates an entire N-ary tree
 * @tree: pointer to tree to delete
*/
void nary_tree_delete(nary_tree_t *tree)
{
	if (!tree)
		return;

	free(tree->content);

	if (tree->children)
		nary_tree_delete(tree->children);

	if (tree->next)
		nary_tree_delete(tree->next);

	free(tree);
	tree = NULL;
}
