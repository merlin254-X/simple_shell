#include "shell.h"

/**
 * _strncpy - copies a string
 * @dest: imput function(destination)
 * @src: imput function(source)
 * @n: imput function
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
 * custom_strdup - Duplicates a string
 * @str: The string to be duplicated
 *
 * Return: Pointer to the duplicated string, or NULL on failure
 */
char *custom_strdup(const char *string)
{
		char *new_string = NULL;
		size_t length = 0;

	while (string[length] != '\0')
	{
		length++;
	}

	new_string = malloc(sizeof(char) * (length + 1));
	if (new_string == NULL)
	{
		return (NULL);
	}

	for (size_t i = 0; i < length; i++)
	{
		new_string[i] = string[i];
	}
	new_string[length] = '\0';

	return (new_string);
}

/**
 * custom_puts - Prints the input string to the standard output
 * @str: The string to be printed
 *
 * Return: Void (prints the string to standard output)
 */
void custom_puts(const char *str)
{
		if (str == NULL)
				return;

		while (*str != '\0')
		{
				_putchar(*str);
				str++;
		}
}

/**
 * custom_putchar - Writes the character c to stdout
 * @s: The character to print
 *
 * Return: On success 1. On error, -1 is returned, and errno
 * is set appropriately.
 */
int custom_putchar(char s)
{
	static int index = 0;
	static char buffer[WRITE_BUF_SIZE];

	if (s == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(STDOUT_FILENO, buffer, index);
		index = 0;
	}

	if (s != BUF_FLUSH)
	{
		buffer[index++] = s;
	}

	return (1);
}
