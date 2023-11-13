#include "shell.h"

/**
 * _custom_putsfd - Writes a string to a specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written on success, -1 on failure.
 */
int _custom_putsfd(char *str, int fd)
{
    int i = 0;

    if (str == NULL || fd < 0)
    {
        return (-1);
    }

    while (*str)
    {
        i += write(fd, str++, 1);
    }

    return (i);
}

/**
 * writeCharToFileDescriptor - Writes the character to the given file descriptor.
 * @character: The character to write.
 * @fileDescriptor: The file descriptor to write to.
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int writeCharToFileDescriptor(char character, int fileDescriptor)
{
    static int bufferIndex = 0;
    static char buffer[WRITE_BUF_SIZE];

    if (fileDescriptor < 0)
    {
        return (-1);
    }

    if (character == '\0' || bufferIndex >= WRITE_BUF_SIZE - 1)
    {
        write(fileDescriptor, buffer, bufferIndex);
        bufferIndex = 0;
        if (character == '\0')
	{
            return (0);
        }
    }

    buffer[bufferIndex++] = character;

    return (1);
}

/**
 * custom_eputchar - writes the character to stderr
 * @c: The character to print
 *
 * Return: On success 1. On error, -1 is returned,
 * and errno is set appropriately.
 */
int custom_eputchar(char c)
{
    static int i = 0;
    static char buf[BUF_SIZE];

    if (i >= BUF_SIZE || c == BUF_FLUSH)
    {
        if (write(2, buf, i) == -1)
	{
            return (-1);
        }
        i = 0;

        if (c == BUF_FLUSH)
	{
            return (1);
        }
    }

    buf[i++] = c;

    return (1);
}

/**
 * _custom_eputs - prints a string to stderr
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _custom_eputs(char *str)
{
    while (*str != '\0')
    {
        write(2, str, 1);
        str++;
    }
}
