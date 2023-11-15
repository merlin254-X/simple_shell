#include "shell.h"

/**
 * duplicate_environ - duplicates the environ array
 * @info: structures containing potential arguments
 * Return: pointer to the copied array of strings
 */
char **duplicate_environ(info_t *info)
{
	char **env_copy;
	int i, len;

	env_copy = malloc(sizeof(char *) * (info->env_size + 1));
	if (env_copy == NULL)
		return (NULL);

	for (i = 0; i < info->env_size; i++)
	{
		len = _strlen(info->environ[i]);
		env_copy[i] = malloc(sizeof(char) * (len + 1));
		if (env_copy[i] == NULL)
		{
			free_env(env_copy);
			return (NULL);
		}
		_strcpy(env_copy[i], info->environ[i]);
	}
	env_copy[i] = NULL;

	return (env_copy);

}

/**
 * _unsetenv - removes an environment variable
 * @info: structure containing potential arguments
 * @variables: the string representing the environment variable
 * Return: 1 on successiful removal, 0 otherwise
 */
int _unsetenv(info_t *info, char *variable)
{
	char **environment = info->environment;
	int i, j, length;

	if (variable == NULL || *variable == '\0')
		return (0);

	length = _strlen(variable);
	for (i = 0; environment[i] != NULL; i++)
	{
		if (_strncmp(environment[i], variable, length) == 0 && environment[i][length] == '=')
		{
			free(environment[i]);
			for (j = i; environment[j] != NULL; j++)
				environment[j] = environment[j + 1];
			return (1);
		}
	}
	return (0);
}

/**
 * set_environment_variable = set or modify an environment variable
 * @info: structure containing potential arguments
 * @variable: the name of the environment
 * @value: the value to set for the environment variable
 * Return: 0 on success, -1 on failure
 */
int set_environment_variable(info_t *info, char *variable, char *value)
{
	char *new_var;
	int length;

	if (info == NULL || variable == NULL || value == NULL)
		return (-1);

	length = _strlen(variable) + _strlen(value) + 2;

	new_var = malloc(sizeof(char) * length);
	if (new_var == NULL)
		return (-1);

	_strcpy(new_var, variable);
	_strcat(new_var, "=");
	_strcat(new_var, value);

	if (_putenv(new_var) == -1)
	{
		free(new_var);
		return (-1);
	}
	free(new_var);

	return (0);
}
