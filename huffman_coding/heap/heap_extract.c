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
 * heapify_down - Maintains the heap property by
 * moving a node downwards in the heap
 * @heap: Pointer to heap
 *
 * Description:
 * This function moves the given node downwards in the heap, swapping it with its
 * parent if necessary to maintain the heap property. It continues this process
 * until either the node becomes a leaf of the heap or it satisfies the heap
 * property.
 */
void heapify_down(heap_t *heap)
{
	binary_tree_node_t *root = heap->root;

	/* Continue as long as the node has childs and violates the heap property */
	while (root->left || root->right)
	{
		if (root->left)
		{
			if (heap->data_cmp(root->left->data, root->data) < 0)
			{
				/* Swap the data of the current node with its left child */
				swap_nodes_data(root, root->left);
				root = root->left;
				continue;
			}
		}
		if (root->right)
		{
			if (heap->data_cmp(root->right->data, root->data) < 0)
			{
				/* Swap the data of the current node with its right child */
				swap_nodes_data(root, root->right);
				root = root->right;
			}
			else
				break;
		}
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

	last_node = get_last_node(heap->root, heap->size);

	parent = last_node->parent;
	if (parent->left == last_node)
		parent->left = NULL;
	else
		parent->right = NULL;

	last_node->parent = NULL; /* root parent is NULL */
	last_node->left = heap->root->left;
	last_node->right = heap->root->right;
	heap->root = last_node;
	heap->size--;
	heapify_down(heap);
	return (root_data);
}
