#include "nary_trees.h"


/**
 * calculate_height_and_diameter - calculate height and diameter of tree
 * @node: pointer to node to calculate height and diameter from
 * @diameter: pointer to diameter var
 * Return: the diameter of the tree;
*/
size_t calculate_height_and_diameter(nary_tree_t const *node, size_t *diameter)
{
	size_t max1 = 0, max2 = 0;
	nary_tree_t *child;

	if (!node)
		return (0);

	for (child = node->children; child; child = child->next)
	{
		size_t height = calculate_height_and_diameter(child, diameter);

		if (height > max1)
		{
			max2 = max1;
			max1 = height;
		}
		else if (height > max2)
			max2 = height;

		*diameter = (*diameter > (max1 + max2) ? *diameter : (max1 + max2));

	}
	return (max1 + 1);
}

/**
 * nary_tree_diameter - computes the diameter of an N-ary tree
 * @root: pointer to the root node of the tree to compute the diameter of
 * Return: the diameter of the tree pointed to by root
*/
size_t nary_tree_diameter(nary_tree_t const *root)
{
	size_t diameter = 0;

	calculate_height_and_diameter(root, &diameter);
	return (diameter + 1);
}
