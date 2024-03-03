#include "rb_trees.h"

/**
 * rb_tree_is_valid - Checks if a binary tree is a valid Red-Black Tree
 * @tree: pointer to the root node of the tree to check
 * Return: 1 if tree is a valid Red-Black Tree, and 0 otherwise
 * If tree is NULL, return 0
 * Properties of a Red-Black Tree:
 * A Red-Black Tree is a BST
 * Every node has a color either red or black.
 * Root of tree is always black.
 * There are no two adjacent red nodes
 * (A red node cannot have a red parent or red child).
 * Every path from root to a NULL node has same number of black nodes.
*/
int rb_tree_is_valid(const rb_tree_t *tree)
{
	int is_valid = 1;

	/* Only checked first time because NULL checked before recursion */
	if (tree == NULL)
		is_valid = 0;
	/* Check root node color */
	else if ((tree->parent == NULL) && (tree->color != BLACK))
		is_valid = 0;
	/* Check if there are adjacent RED nodes */
	else if ((tree->color == RED) &&
		(
			(tree->parent->color == RED) ||
			((tree->left != NULL) && (tree->left->color == RED)) ||
			((tree->right != NULL) && (tree->right->color == RED))
		)
	)
		is_valid = 0;
	else
	{
		if ((is_valid == 1) && (tree->left != NULL))
		{
			if ((tree->right == NULL) && (tree->left->color != RED))
				is_valid = 0;
			else
				is_valid = rb_tree_is_valid(tree->left);
		}
		if ((is_valid == 1) && (tree->right != NULL))
		{
			if ((tree->left == NULL) && (tree->right->color != RED))
				is_valid = 0;
			else
				is_valid = rb_tree_is_valid(tree->right);
		}
	}
	return (is_valid);
}
