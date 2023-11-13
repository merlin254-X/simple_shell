#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: string
 * Return: string length
 */
int _strlen(char *s)
{
	int length = 0;

	while (*s != '\0')
	{
		length++;
		s++;
	}
	return (length);
}

/**
 * _strcat - contatenates two strings
 * @dest: imput value(destination buffer)
 * @imput value(source buffer)
 * Return: original_dest
 */
char *_strcat(char *dest, char *src)
{
	char *original_dest = dest;

	while (*dest != '\0')
	{
		dest++;
	}
	while (*src != '\0')
	// Copy characters from src to dest
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }

    // Null-terminate the concatenated string
    *dest = '\0';

    return original_dest;
}
