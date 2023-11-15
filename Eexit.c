#include "shell.h"

/**
 * _strncpy - copies a string
 * @dest: destination string
 * @src: source string
 * @m: characters to be copied
 * Return: dest
 */
char *_strncpy(char *dest, char *src, int m)
{
	int j;

	j = 0;

	while (j < m && src[j] != '\0')
	{
		dest[j] = src[j];
		j++;
	}
	while (j < m)
	{
		dest[j] = '\0';
		j++;
	}
	return (dest);
}

/**
 * _strncat - concatenate up to n characters
 * from the source string src to the end of the destination string dest
 * @dest: pointer to the destination string
 * @src: pointer to the source string
 * @k: maximum number of characters from src to concatenate
 * Return: a pointer to the resulting concatenated string, starting at the original address of dest
 */
char *_strncat(char *dest, char *src, int k)
{
	char *original_dest = dest;

	while (*dest != '\0')
	{
		dest++;
	}

	while (*src != '\0' && k > 0)
	{
		*dest = *src;
		dest++;
		src++;
		k--;
	}

	*dest = '\0';
	return (original_dest);
}

/**
 * _strchr - locates a character in a string
 * @str: the string to search
 * @ch: the character to find
 * Return: a pointer to the first occurrence of the character c
 * on s, or NULL if the character is not found
 */
char *_strchr(char *str, char ch)
{
	while (*str != '\0')
	{
		if (*str == ch)
		{
			return (str);
		}
		str++;
	}
	return (NULL);
}
