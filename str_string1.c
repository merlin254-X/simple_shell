#include "shell.h"

/**
 * _strncpy - copies a string
 * @dest: desttination buffer
 * @src: source buffer
 * @n: imput function(characters to copy)
 * Return: dest
 */
char *_strncpy(char *dest, char *src, int n)
{
	int j = 0;

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
 * custom_strdup - duplicates a string
 * @string: the string to be duplicated
 * Return: pointer to be duplicated string, or NULL on failure
 */
char *custom_strdup(const char *string)
{
char *new_string = NULL;
        size_t i;
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

	for (i = 0; i < length; i++)
	{
		new_string[i] = string[i];
	}
	new_string[length] = '\0';

	return (new_string);
}

/**
 * custom_puts - prints the input string to the standard output
 * @str: the string to be printed
 * Return: void
 */
void custom_puts(const char *str)
{
	if (str == NULL)
		return;

	while (*str != '\0')
	{
		putchar(*str);
		str++;
	}
}

/**
 * custom_putchar - writes the character c to stdout
 * @s: the character to print
 * Return: on success 1, on error -1 is returned, and errno is set
 * appropriately
 */
int custom_putchar(char s)
{
	static int index;
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
