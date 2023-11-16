#include "shell.h"

/**
 * ffrees - Frees the memory pointed to by a pointer and
 * sets the pointer to NULL.
 * @pointer: address of the pointer t be freed
 * Return: 1 if the memory is successfully freed, otherwise 0.
 *
 */
int ffrees(void **pointer)
{
	if (pointer == NULL || *pointer == NULL)
		return (0);

	free(*pointer);
	*pointer = NULL;
	return (1);
}
