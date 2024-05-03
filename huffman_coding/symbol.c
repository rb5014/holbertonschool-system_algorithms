#include "huffman.h"

/**
 * symbol_create - creates a symbol_t data structure
 * @data: data to be stored in the structure
 * @freq: data's associated frequency
 * Return: pointer to the created structure, or NULL if it fails
*/
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *new_s = malloc(sizeof(symbol_t));

	if (new_s == NULL)
		return (NULL);
	new_s->data = data;
	new_s->freq = freq;

	return (new_s);
}
