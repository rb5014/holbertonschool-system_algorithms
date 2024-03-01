#include "rb_trees.h"

/**
 * rb_tree_insert - Inserts a value in a Red-Black Tree
 * @tree: Double pointer to the root node of the Red-Black tree to
 * insert the value in
 * @value: Value to store in the node to be inserted
 * Return: Pointer to the created node, or NULL on failure
 * If the address stored in tree is NULL,
 * the created node must become the root node.
 * If the value is already present in the tree, it must be ignored
 * The resulting tree after insertion, must be a Red-Black Tree
 * You are allowed to have up to 7 functions in your file
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	static int *values, nb_values;
	int i, inserted = 0, balanced = 0;
	rb_tree_t *new_N, **C = tree;
	int dir;

	for (i = 0; i < nb_values; i++)
	{
		if (value == values[i])
			return (NULL);
	}

	new_N = rb_tree_node(NULL, value, RED);
	if (new_N == NULL)
		return (NULL);

	nb_values++;
	values = (int *)realloc(values, nb_values);
	values[nb_values - 1] = value;

	if (*tree == NULL)
	{
		new_N->color = BLACK;
		*tree = new_N;
		return (*tree);
	}

	while (inserted == 0)
	{
		dir = ((value < (*C)->n) ? dir = LEFT : RIGHT);
		C = (dir == LEFT) ? &(*C)->left : &(*C)->right;
		if (*C == NULL)
		{
			*C = new_N;
			inserted = 1;
		}
	}

	balance_tree(tree, C, dir);
	return (new_N);
}

void balance_tree(rb_tree_t **T, rb_tree_t **node, int dir)
{
	rb_tree_t *N = *node;
	rb_tree_t *P = N->parent;
	rb_tree_t *G = (P != NULL) ? P->parent : NULL;
	rb_tree_t *U;

	while (P != NULL)
	{
		/* CASE 1 (P BLACK)*/
		if (P->color == BLACK)
			return;

		/* From now on P can only be RED */
		G = P->parent;
		if (G == NULL)
			goto Case_I4; /* P RED and root */
		/* else: P red and G != NULL */
		dir = childDir(P); /* the side of parent G on which node P is located */
		U = (dir == LEFT) ? G->right : G->left;
		if ((U == NULL) || (U->color == BLACK)) /* Considered BLACK */
			goto Case_I56;						/* P RED && U BLACK */
		/* Case 2 (P+U RED) */
		P->color = BLACK;
		U->color = BLACK;
		G->color = RED;
		N = G; /* New current node */
		/* iterate 1 black level higher */
		/*   (= 2 tree levels) */
		P = N->parent;
	}

Case_I4: /* P is the root and red: */
	if (P != NULL)
		P->color = BLACK;
	return;

Case_I56: /* P red && U black: */
	if ((dir == LEFT) && (N == P->right))
	{						/* Case_I5 (P red && U black && N inner grandchild of G): */
		RotateDir(P, LEFT); /* P is never the root */
		N = P;				/* new current node */
		P = G->left;		/* new parent of N */
							/* fall through to Case_I6 */
	}
	else if ((dir == RIGHT) && (N == P->left))
	{						 /* Case_I5 (P red && U black && N inner grandchild of G): */
		RotateDir(P, RIGHT); /* P is never the root */
		N = P;				 /* new current node */
		P = G->right;		 /* new parent of N */
							 /* fall through to Case_I6 */
	}
	/* Case_I6 (P red && U black && N outer grandchild of G): */
	RotateDirRoot(T, G, 1 - dir); /* G may be the root */
	P->color = BLACK;
	G->color = RED;
	return; /* insertion complete */
} /* end of RBinsert1 */

rb_tree_t *RotateDirRoot(rb_tree_t **T, /* red–black tree */
	rb_tree_t *P,  /* root of subtree (may be the root of T) */
	int dir)
{ /* dir ∈ { LEFT, RIGHT } */
	rb_tree_t *G = P->parent;
	rb_tree_t *S = (dir == LEFT) ? P->right : P->left;
	rb_tree_t *C;

	assert(S != NULL); /* pointer to true node required */
	C = (dir == LEFT) ? S->left : S->right;
	if (dir == LEFT)
		P->right = C;
	else
		P->left = C;
	if (C != NULL)
		C->parent = P;
	if (dir == LEFT)
		S->left = P;
	else
		S->right = P;
	P->parent = S;
	S->parent = G;
	if (G != NULL)
	{
		if (G->right == P)
			G->right = S;
		else
			G->left = S;
	}
	else
		*T = S;
	return (S); /* new root of subtree */
}