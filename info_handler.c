#include "shell.h"

/**
 * reset_info - Resets an info_t struct to default values.
 * @info: Pointer to the info_t struct.
 */
void reset_info(info_t *info)
{
	if (info != NULL)
	{
		info->argc = 0;
		info->argv = '\0';
		info->path = '\0';
		info->args = NULL;
	}
}

/**
 * initialize_info - Initializes the fields of an info_t struct with values
 * derived from the provided argument vector.
 * @info: Pointer to the info_t struct to be initialized
 * @av: Argument vector containing program-related information.
 */
void initialize_info(info_t *info, char **av)
{
	int i;
	int j;

	if (info == NULL || av == NULL)
	{
		return;
	}
	info->name = &av[0][0];

	info->argc = 0;
	info->argv = '\0';
	while (av[(unsigned char)info->argc] != NULL)
	{
		info->argc++;
	}
	info->argv = (char **)malloc(sizeof(char *) * (info->argc + 1));
	if (info->argv == NULL)
	{
		return;
	}
	for (i = 0; i < info->argc; i++)
	{
		info->argv[i] = strdup(av[i]);
		if (info->argv[i] == NULL)
		{
			for (j = 0; j < i; j++)
			{
				free(info->argv[j]);
			}
			free(info->argv);
			info->argv = NULL;
			return;
		}
	}
	info->argv[(int)info->argc] = NULL;
}

/**
 * release_info - deallocates memory occupied by info_t struct
 * @info: struct pointer
 * @free_all: true to free all fields, false otherwise
 */
void release_info(info_t *info, int free_all)
{
	if (info == NULL)
		return;

	if (info->name != NULL)
	{
		free(info->name);
		info->name = NULL;
	}
	if (info->address != NULL)
	{
		free(info->address);
		info->address = NULL;
	}
	if (info->contactNumber != NULL)

	{
		free(info->contactNumber);
		info->contactNumber = NULL;
	}

	if (free_all)
	{
		free(info);
		return;
	}
}
