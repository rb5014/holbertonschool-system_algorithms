#include "nary_trees.h"

/**
 * nary_tree_insert - inserts a node in a N-ary tree
 * @parent: pointer to the parent node
 * @str: string to be stored in the created node. It must be duplicated
 * If parent is not NULL, the created node must be added at
 * the beginning of the parent’s children linked list
 * Return: pointer to the created node, or NULL on failure
*/
nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str)
{
	nary_tree_t *new;

	new = malloc(sizeof(nary_tree_t));
	if (new == NULL)
		return (NULL);

	new->content = (str != NULL) ? strdup(str) : NULL;

	/* Link parent to new node by putting it */
	/* in 1st position in parent's children's list */
	if (parent != NULL)
	{
		new->parent = parent;
		new->next = parent->children;

		parent->children = new;
		parent->nb_children++;
	}
	else
	{
		new->parent = NULL;
		new->next = NULL;
	}

	new->nb_children = 0;
	new->children = 0;

	return (new);
}
