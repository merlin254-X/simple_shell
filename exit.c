#include "shell.h"

/**
 * _strncpy - copies a string
 * @dest: destination string
 * @src: source string
 * @n: characters to be copied
 * Return: dest
 */
char *_strncpy(char *dest, char *src, int n)
{
	int j;

	j = 0;
		while (j < n && src[j] != '\0')
		{
			dest[j] = src[j];
			j++;
		}
	while (j < n)
	{
		dest[j] = '\0';
		j++;
	}
	return (dest);
}

/**
 * _strncat - Concatenate up to n characters
 * from the source string src to the
 *            end of the destination string dest.
 * @dest: Pointer to the destination string.
 * @src: Pointer to the source string.
 * @n: Maximum number of characters from src to concatenate.
 *
 * Return: A pointer to the resulting concatenated string, starting at the
 *         original address of dest.
 */

char *_strncat(char *dest, char *src, int n)
{
	char *original_dest = dest;

	while (*dest != '\0')
	{
		dest++;
	}
	while (*src != '\0' && n > 0)
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}
	*dest = '\0';

	return (original_dest);
}

/**
 * _strchr - Locates a character in a string.
 * @s: The string to search.
 * @c: The character to find.
 *
 * Return: A pointer to the first occurrence of the character c in s,
 *         or NULL if the character is not found.
 */
char *_strchr(char *s, char c)
{
    while (*s != '\0')
    {
        if (*s == c)
        {
            return (s);
        }
        s++;
    }
    return (NULL);
}
