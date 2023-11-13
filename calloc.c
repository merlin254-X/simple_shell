#include "shell.h"

/** 
 * freeStringArray - frees a string of strings 
 * @ff: string of strings 
 */
void freeStringArray(char **ff)
{
    int i = 0;
    if (ff == NULL)
        return;
    while (ff[i] != NULL)
    {
        free(ff[i]);
	i++;
    }
    free(ff);
}

/**
 * resize_memory - Resizes memory allocation from an
 * old block to a new block
 * @old_ptr: Pointer to the old block of memory
 * @old_size: Size of the old block
 * @new_size: Size of the new block
 *
 * Returns: a pointer to the new memory block or NULL
 * if an error occurs during the creation of the new block.
 *
 */
void* resize_memory(void* old_ptr, size_t old_size, size_t new_size)
{
    void* new_ptr = calloc(new_size, 1);

    if (new_ptr == NULL)
    {
        return (NULL);
    }

    if (old_ptr != NULL && new_size > 0)
    {
        size_t min_size = (old_size < new_size) ? old_size : new_size;
        memcpy(new_ptr, old_ptr, min_size);
    }

    if (old_ptr != NULL)
    {
        free(old_ptr);
    }

    return (new_ptr);

/**
 * custom_memset - Fills the memory with a constant byte
 * @mem: Pointer to the memory area to be filled
 * @byte: The byte value used to fill the memory
 * @size: The number of bytes to be filled
 *
 * Return: A pointer to the memory area `mem`.
 */
char *custom_memset(char *mem, char byte, unsigned int size)
{
    unsigned int index;
    char *pointer = mem;

    for (index = 0; index < size; index++)
    {
        *pointer = byte;
        pointer++;
    }

    return (mem);
}
