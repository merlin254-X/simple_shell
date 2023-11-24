#include "shell.h"

/**
 * removeComments - replaces first instance of '#' with '\0'
 * if preceded by space or at the beginning of the line
 * @inputString: address of the string to modify
 * Return: void
 */
void removeComments(char *inputString)
{
	int index = 0;

	if (inputString == NULL)
		return;

	for (; inputString[index] != '\0'; index++)
	{
		if (inputString[index] == '#' &&
				(index == 0 || inputString[index - 1] == ' '))
		{
			inputString[index] = '\0';
			break;
		}
	}

}

/**
 * custom_number_conversion - converts a long integer to a
 * string in a specified base
 * @input_num: the number to be converted
 * @target_base: the base to which the number should be converted
 * @conversion_flags: flags to control the conversion process
 * Return: a pointer to the resulting string
 */
char *custom_number_conversion(long int input_num,
		int target_base, int conversion_flags)
{
	static const char character_set[] = "0123456789abcdef";
	static char result_buffer[33];
	char *result_ptr = &result_buffer[32];
	*result_ptr = '\0';

	if (input_num == 0)
	{
		return ("0");
	}

	if (input_num < 0 && target_base == 10)
	{
		conversion_flags |= 1;
		input_num = -input_num;
	}

	while (input_num != 0)
	{
		result_ptr--;
		*result_ptr = character_set[input_num % target_base];
		input_num /= target_base;
	}

	if (conversion_flags & 1)
	{
		result_ptr--;
		*result_ptr = '-';
	}

	return (result_ptr);
}

/**
 * custom_print_d - prints a decimal (integer) number (base 10)
 * @num: the input number to be printed
 * @output_fd: the file descriptor to write to
 * Return: the number of characters printed
 */
int custom_print_d(int num, int output_fd)
{
	char digit_buffer[12];
	int buffer_index = 0;
	int characters_printed = 0;
	int is_negative = 1;

	if (num == 0)
	{
		digit_buffer[buffer_index++] = '0';
	}
	else
	{
		if (num < 0)
		{
			is_negative = -1;
			num = -num;
		}

		while (num > 0)
		{
			digit_buffer[buffer_index++] = (num % 10) + '0';
			num /= 10;
		}
	}

	if (is_negative < 0)
	{
		write(output_fd, "-", 1);
		characters_printed++;
	}

	while (buffer_index > 0)
	{
		write(output_fd, &digit_buffer[--buffer_index], 1);
		characters_printed++;
	}

	return (characters_printed);
}

/**
 * print_error - outputs an error message to standard error
 * @info: pointer to info_t struct
 * @error_type: string describing the type of error
 * Return: void
 */

void print_error(info_t *info, char *error_type)
{
	if (info == NULL)
	{
		return;
	}

	write(STDERR_FILENO, info->name, _strlen(info->name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, error_type, _strlen(error_type));
	write(STDERR_FILENO, ": ", 2);

	if (info->arg != NULL)
	{
		write(STDERR_FILENO, info->arg, _strlen(info->arg));
	}

	write(STDERR_FILENO, "\n", 1);
	info->error++;
}

/**
 * _custom_atoi - converts a string tp an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, convert number otherwise,-1 on error
 */
int _custom_atoi(char *s)
{
	int result = 0;
	int sign = 1;
	int started = 0;

	if (s == NULL)
	{
		return (-1);
	}
	while (*s != '\0')
	{
		if (isdigit(*s))
		{
			int digit = *s - '0';

			if (result > (INT_MAX - digit) / 10)
			{
				return (-1);
			}
			result = result * 10 + digit;
			started = 1;
		}
		else if (*s == '+' || *s == '-')
		{
			if (started)
			{
				break;
			}
			sign = (*s = '+') ? 1 : -1;
		}
		else
		{
			if (started)
			{
				break;
			}
		}
		s++;
	}

	return (sign * result);
}
