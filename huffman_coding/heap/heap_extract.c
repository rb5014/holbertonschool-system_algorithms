#include "heap.h"

/**
 * get_last_node - return last node
 * @root: pointer to the root of the heap
 * @size: size of the heap
 * Return: pointer to the data of the last node, or NULL on failure
*/
void *get_last_node(binary_tree_node_t *root, size_t size)
{
	binary_tree_node_t *queue[100];
	int front = -1, rear = 0;

	/* If the tree is empty, return NULL */
	if ((root == NULL) || (size <= 1))
		return (NULL);

	queue[rear] = root;

	while ((front != rear) && (rear < (int)size))
	{
		front++;
		if (queue[front]->left)
			queue[++rear] = queue[front]->left;
		if (queue[front]->right)
			queue[++rear] = queue[front]->right;
	}

	return (queue[size - 1]);
}

/**
 * get_min_child - get the minimum child of a node
 * @node: pointer to the node from which we check the children
 * @data_cmp: pointer to a comparison function
 * Return: pointer to the minimum child of the parent node,
 * or the only child (if one of them is NULL),
 * or NULL if both children are NULL
*/
binary_tree_node_t *get_min_child(binary_tree_node_t *node,
								  int (*data_cmp)(void *, void *))
{
	binary_tree_node_t *min_child;

	if (node->left && node->right)
	{
		if (data_cmp(node->left->data, node->right->data) <= 0)
			min_child = node->left;
		else
			min_child = node->right;
	}
	else if (node->left)
		min_child = node->left;
	else if (node->right)
		min_child = node->right;
	else
		min_child = NULL;
	return (min_child);
}

/**
 * heapify_down - Maintains the heap property by
 * moving a node downwards in the heap
 * @node: Pointer to the node
 * @data_cmp: pointer to a comparison function
 * Description:
 * This function moves the given node downwards in the heap,
 * swapping it with its
 * parent if necessary to maintain the heap property. It continues this process
 * recursively until either the node becomes a leaf of the heap or
 * it satisfies the heap property.
 */
void heapify_down(binary_tree_node_t *node, int (*data_cmp)(void *, void *))
{
	binary_tree_node_t *min_child = get_min_child(node, data_cmp);

	if (min_child && (data_cmp(min_child->data, node->data) < 0))
	{
		swap_nodes_data(min_child, node);
		heapify_down(min_child, data_cmp);
	}
}

/**
 * heap_extract - extracts the root value of a Min Binary Heap
 * @heap: pointer to the heap from which to extract the value
 * Return: pointer to the data that was stored in the root node of the heap,
 * or NULL if function fails or heap is NULL
 * Once the data is extracted, the root node must be freed,
 * and replaced by the last node of the heap.
 * Then the heap must be rebuilt if necessary
*/
void *heap_extract(heap_t *heap)
{
	binary_tree_node_t *last_node, *parent;
	void *root_data;

	if (!heap || !heap->root)
		return (NULL);

	root_data = heap->root->data;
	if (heap->size == 1)
	{
		free(heap->root);
		heap->root = NULL;
		heap->size = 0;
		return (root_data);
	}

	last_node = get_last_node(heap->root, heap->size);

	heap->root->data = last_node->data;

	parent = last_node->parent;
	if (parent->left == last_node)
		parent->left = NULL;
	else
		parent->right = NULL;
	heap->size--;
	free(last_node);
	heapify_down(heap->root, heap->data_cmp);
	return (root_data);
}
