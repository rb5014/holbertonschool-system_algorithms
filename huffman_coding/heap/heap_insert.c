#include "heap.h"

/**
 * parent - find parent index of a given node in prio queue
 * @i: index of the node
 * Return: the parent's index
*/
size_t parent(size_t i)
{

	return ((i - 1) / 2);
}

/**
 * swap_nodes_data - Swaps the data between two binary tree nodes
 * @node1: Pointer to the first node
 * @node2: Pointer to the second node
 */
void swap_nodes_data(binary_tree_node_t *node1, binary_tree_node_t *node2)
{
	void *tmp_data;

	/* Swap the data between the two nodes */
	tmp_data = node1->data;
	node1->data = node2->data;
	node2->data = tmp_data;
}

/**
 * heapify_up - Maintains the heap property by
 * moving a node upwards in the heap
 * @heap: Pointer to the heap structure
 * @node: Pointer to the node from which the heapification starts
 *
 * Description:
 * This function moves the given node upwards in the heap, swapping it with its
 * parent if necessary to maintain the heap property. It continues this process
 * until either the node becomes the root of the heap or it satisfies the heap
 * property.
 */
void heapify_up(heap_t *heap, binary_tree_node_t *node)
{
	/* Continue as long as the node has a parent and violates the heap property */
	while (node->parent && (heap->data_cmp(node->data, node->parent->data) < 0))
	{
		/* Swap the data of the current node with its parent */
		swap_nodes_data(node, node->parent);

		node = node->parent; /* Move to the parent node for further heapification */
	}
}

/**
 * find_parent_for_insertion - Find the parent node for inserting a new node
 * @root: Pointer to the root node of the binary tree
 *
 * Return: Pointer to the parent node where the new node should be inserted
 */
binary_tree_node_t *find_parent_for_insertion(binary_tree_node_t *root)
{
	binary_tree_node_t *prio_queue[100];
	int front = -1, rear = 0;

	/* If the tree is empty, return NULL */
	if (root == NULL)
		return (NULL);

	prio_queue[rear] = root;

	while ((front != rear) && (rear < 99))
	{
		if (prio_queue[++front] == NULL)
			return (prio_queue[parent(front)]);
		prio_queue[++rear] = prio_queue[front]->left;
		prio_queue[++rear] = prio_queue[front]->right;
	}

	return (NULL);
}

/**
 * heap_insert - inserts a value in a Min Binary Heap
 * @heap: pointer to the heap in which the node has to be inserted
 * @data: pointer containing the data to store in the new node
 * The size of the heap must be incremented if the function succeeds
 * If heap is NULL, function should fail
 * If data is NULL, function should fail
 * If heap->root is NULL, new node must take its place
 * Return: pointer to the created node containing data, or NULL if it fails
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *new_node, *parent;

	if (!heap || !data)
		return (NULL);

	/* Create the new node */
	new_node = binary_tree_node(NULL, data);
	if (new_node == NULL)
		return (NULL);

	/* If the heap is empty, set the new node as the root */
	if (!heap->root)
	{
		heap->root = new_node;
		heap->size++;
		return (new_node);
	}
	/* Find the parent node where the new node should be inserted */
	parent = find_parent_for_insertion(heap->root);

	/* Insert the new node as a child of the found parent */
	if (parent->left == NULL)
		parent->left = new_node;
	else
		parent->right = new_node;
	new_node->parent = parent;
	heap->size++;

	/* Restore the heap property by percolating up */
	heapify_up(heap, new_node);

	return (new_node);
}
