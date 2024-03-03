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
	rb_tree_t *new_N, **C = tree;
	int dir;

	new_N = rb_tree_node(NULL, value, RED);
	if (new_N == NULL)
		return (NULL);

	if (tree == NULL)
		return (NULL);

	if (*tree == NULL)
	{
		new_N->color = BLACK;
		*tree = new_N;
		return (*tree);
	}

	while (1)
	{
		if (value == (*C)->n)
			return (NULL);
		dir = ((value < (*C)->n) ? 0 : 1);
		new_N->parent = *C;
		C = (dir == 0) ? &(*C)->left : &(*C)->right;
		if (*C == NULL)
		{
			*C = new_N;
			break;
		}
	}

	balance_tree(tree, C);
	(*tree)->color = BLACK;
	return (new_N);
}

/**
 * balance_tree - balance the tree after node insertion
 * @T: pointer of pointer of tree
 * @node: pointer of pointer of node
*/
void balance_tree(rb_tree_t **T, rb_tree_t **node)
{
	rb_tree_t *N = *node;
	rb_tree_t *P = N->parent;
	rb_tree_t *G = (P != NULL) ? P->parent : NULL;
	rb_tree_t *U;
	int dir;

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
		dir = child_dir(P); /* the side of parent G on which node P is located */
		U = (dir == 0) ? G->right : G->left;
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
	return;
Case_I4: /* P is the root and red: */
	P->color = BLACK;
	return;

Case_I56: /* P red && U black: */
	case_i56(T, P, N, G, dir);
}

/**
 * case_i56 - Handle the case where parent is red and uncle is black
 * @T: double pointer of red-black tree
 * @N: Node to reorganize
 * @P: parent of node
 * @G: parent of parent of node
 * @dir: dir ∈ { LEFT, RIGHT }
*/
void case_i56(rb_tree_t **T, rb_tree_t *P, rb_tree_t *N, rb_tree_t *G, int dir)
{
	if ((dir == 0) && (P->right == N))
	{						/* Case_I5 (P red && U black && N inner grandchild of G): */
		rotate_dir_root(T, P, 0); /* P is never the root */
		N = P;				/* new current node */
		P = G->left;		/* new parent of N */
							/* fall through to Case_I6 */
	}
	else if ((dir == 1) && (P->left == N))
	{						 /* Case_I5 (P red && U black && N inner grandchild of G): */
		rotate_dir_root(T, P, 1); /* P is never the root */
		N = P;				 /* new current node */
		P = G->right;		 /* new parent of N */
							 /* fall through to Case_I6 */
	}
	/* Case_I6 (P red && U black && N outer grandchild of G): */
	rotate_dir_root(T, G, 1 - dir); /* G may be the root */
	P->color = BLACK;
	G->color = RED;
	return; /* insertion complete */
}

/**
 * rotate_dir_root - rotate nodes
 * @T: double pointer of red-black tree
 * @P: root of subtree (may be the root of T)
 * @dir: dir ∈ { LEFT, RIGHT }
 * Return: new root of subtree
*/
rb_tree_t *rotate_dir_root(rb_tree_t **T, rb_tree_t *P, int dir)
{
	rb_tree_t *G = P->parent;
	rb_tree_t *S = (dir == 0) ? P->right : P->left;
	rb_tree_t *C;

	C = (dir == 0) ? S->left : S->right;
	if (dir == 0)
		P->right = C;
	else
		P->left = C;
	if (C != NULL)
		C->parent = P;
	if (dir == 0)
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

/**
 * child_dir - return the direction of the node
 * @N: node to get the direction
 * Return: RIGHT if N == N->parent->right, LEFT otherwise
*/
int child_dir(rb_tree_t *N)
{
	return (N->parent->right == N ? 1 : 0);
}
