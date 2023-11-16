
include "shell.h"

/**
 * _isalphabet - function to check for alphabet character
 * @k: character input
 * Return: 1 if alphabet, 0 if otherwise
 */
int _isalphabet(int k)
{
	if (k >= 'a' && k <= 'z')
	{
		return (1);
	}
	else if (k >= 'A' && k <= 'Z')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * isDelimeter - checks if a charcter is a delimeter
 * @character: character to check
 * @delimiterString: the string of delimiters
 * Return: 1 if true, 0 if false
 */
int isDelimeter(char character, char *delimiterString)
{
	while (*delimiterString)
	{
		if (*delimiterString++ == character)
		{
			return (1);
		}


	}
	return (0);
}

/**
 * strToInt - converts string to integer
 * @str: input string
 * Return: the converted integer value
 */
int strToInt(char *str)
{
	int sign = 1;
	int result = 0;
	int started = 0;

	while (*str)
	{
		if (*str == '-')
		{
			sign *= -1;
		}
		else if (*str >= '0' && *str <= '9')
		{
			result = result * 10 + (*str - '0');
			started = 1;
		}
		else if (started)
		{
			break;
		}
		str++;
	}
	return (result * sign);
}

/**
 * checkInteractiveMode - checks if the shell is in interactive mode
 * @data: struct containing relevant information
 * Return: 1 if in interactive mode, 0 if otherwise
 */
int checkInteractiveMode(info_t *data)
{
	if (isatty(STDIN_FILENO))
	{
		data->interactive = 1;
		return (1);
	}
	else
	{
		data->interactive = 0;
		return (0);
	}
}
