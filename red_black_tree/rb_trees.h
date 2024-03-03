#ifndef _RB_TREES_H_
#define _RB_TREES_H_

#include <stdlib.h>

#define LEFT  0
#define RIGHT 1
#define childDir(N) (N == (N->parent)->right ? RIGHT : LEFT)
#define RotateDir(N, dir) rotate_dir_root(T, N, dir)
#define RotateLeft(N)    rotate_dir_root(T, N, LEFT)
#define RotateRight(N)   rotate_dir_root(T, N, RIGHT)
/**
 * enum rb_color_e - Possible color of a Red-Black tree
 *
 * @RED: 0 -> Red node
 * @BLACK: 1 -> Black node
 * @DOUBLE_BLACK: 2 -> Double-black node (used for deletion)
 */
typedef enum rb_color_e
{
	RED = 0,
	BLACK,
	DOUBLE_BLACK
} rb_color_t;


/**
 * struct rb_tree_s - Red-Black tree node structure
 *
 * @n: Integer stored in the node
 * @parent: Pointer to the parent node
 * @left: Pointer to the left child node
 * @right: Pointer to the right child node
 * @color: Color of the node (RED or BLACK)
 */
typedef struct rb_tree_s
{
	int n;
	rb_color_t color;
	struct rb_tree_s *parent;
	struct rb_tree_s *left;
	struct rb_tree_s *right;
} rb_tree_t;

rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color);
int rb_tree_is_valid(const rb_tree_t *tree);
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value);
void balance_tree(rb_tree_t **T, rb_tree_t **node);
rb_tree_t *rotate_dir_root(rb_tree_t **T, rb_tree_t *P, int dir);
void case_i56(rb_tree_t **T, rb_tree_t *P, rb_tree_t *N, rb_tree_t *G, int dir);
#endif /* _RB_TREES_H_ */
