#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: string
 * Return: length
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
 *_strcat -  concatenates two strings.
 * @dest: imput value(destination buffer)
 * @src: imput value(source buffer)
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
		{
				*dest = *src;
				dest++;
				src++;
		}
		dest = '\0';

		return (original_dest);
}


/**
 * custom_starts_with - checks if a string starts with a specific substring
 * @str: The string to search
 * @substr: The substring to find at the beginning of 'str'
 *
 * Return: Pointer to the next character of 'str' if 'substr' is
 * found at the beginning, otherwise NULL
 */
char *custom_starts_with(const char *str, const char *substr)
{
		while (*substr != '\0')
		{
		if (*substr != *str)
		{
			return (NULL);
		}
		substr++;
		str++;
	}
	return ((char *)str);
}

/**
 * custom_str_cmp - Performs string comparison of two strings.
 * @string1: The first string to compare
 * @string2: The second string to compare
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int custom_str_cmp(char *string1, char *string2)
{
		 while (*string1 != '\0' || *string2 != '\0')
		 {
		if (*string1 != *string2)
		{
			return (*string1 - *string2);
		}
		string1++;
		string2++;
	}

	if (*string1 != '\0')
	{
		return (*string1);
	}
	else if (*string2 != '\0')
	{
		return (-(*string2));
	}

	return (0);
}
