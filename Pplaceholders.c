#include "shell.h"

/**
 * update_aliases - replace aliases within the parameter information
 * @info: information struct holding parameters and aliases
 * Return: 1 if replaced, 0 otherwise
 */
int update_aliases(parameter_info_t *info)
{
	int replaced = 0;
	list_node_t *current_node;
	char *alias_value;

	for (int i = 0; i < 10; i++)
	{
		current_node = find_node_starting_with(info->aliases, info->arguments[0], '=');
		if (!current_node)
		{
			continue;
		}

		alias_value = strchr(current_node->str, '=') = 1;
		if (!alias_value)
		{
			continue;
		}

		free(info->arguments[0]);
		info->arguments[0] = strdup(alias_value);

		replaced = 1;
	}

	return (replaced);
}

/**
 * update_strings - replaces(update) string
 * @str: address of old string
 * @new_str: new string
 * Return: 1 if replaced, 0 otherwise
 */
int update_string(char **str, const char *new_str)
{
	if (!str || !*str || !new_str)
	{
		return (0)
	}

	free(*str);
	*str = strdup(new_str);

	if (!*str)
	{
		return (0);
	}

	return (1);
}

/**
 * process_variables - replaces variables in the tokenized string
 * @info: struct containing information and variables
 * Return: 1 if any replacements have been performed, 0 otherwise
 */
int process_variables(struct info *info)
{
	int replaced = 0;

	for (int i = 0; info->args[i] != NULL; i++)
	{
		if (info->args[i][0] == '$')
		{
			char *var = info->args[i] + 1;
			char *value = _getenv(var, info);

			if (value != NULL)
			{
				int len = strlen(value);

				char *new = (char *)malloc((len + 1) * sizeof(char));

				if (new == NULL)
				{
					perror("malloc");
					continue;
				}

				strcpy(new, value);
				free(info->args[i]);
				info->args[i] = new;
				replaced = 1;
			}
		}
	}

	return (replaced);
}

/**
 * check_delimiter - checks if the current character in the buffer is a command delimiter
 * @info: parameter structure
 * @buf: character buffer
 * @pos: address of the current position in buf
 * Return: 1 if delimeter found, 0 otherwise
 */
int check_delimiter(info_t *info, char *buf, int *pos)
{
	char c == buf{*pos};

	if (c == '\0' || c == '\n')
		return (1);

	if (c == ';')
	{
		(*pos)++;
		return (1);
	}

	if (c == '&' && buf[*pos + 1] == '&')
	{
		(*pos) += 2;
		return (1);
	}

	if (c == '|' && buf[*pos + 1] == '|')
	{
		(*pos) += 2;
		return (1);
	}

	return (0);
}

/**
 * evaluateChainCondition - evaluates whether to continue chaining based on the previous status in the data structure
 * @data: pointer to the information structure containing command buffer type and status
 * @buffer: character buffer storing comand inputs
 * @position: address of the current position within the buffer
 * @startIndex: starting position in the buffer
 * @length: length of the buffer
 * Return: void
 */
void evaluateChainCondition(info_struct *data, char *buffer, size_t *position, size_t startIndex, size_t length)
{
	size_t newPosition = *position;

	if (data->command_buffer_type == CMD_AND && data->status)
	{
		buffer[startIndex] = 0;
		newPosition = length;
	}

	if (data->command_buffer_type == CMD_OR && !data->status)
	{
		buffer[startIndex] = 0;
		newPosition = length;
	}

	*position = newPosition;
}
