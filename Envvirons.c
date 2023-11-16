#include "shell.h"

/**
 * _myenv - prints thye current environment
 * @info: structure containing potential arguments
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	char **env = info->environ;

	if (env == NULL)
	{
		write(2, "Environment is NULL\n", 21);
		return (-1);
	}

	for (int i = 0; env[i] != NULL; i++)
	{
		write(1, env[i], _strlen(env[i]));
		write(1, "\n", 1);
	}

	return (0);
}

/**
 * _getenv - gets the value of an environment variable
 * @info: structure containing potential arguments
 *
 * @variable_name: env var name
 *
 * Return: the value of environ variable
 */
char *_getenv(info_t *info, const char *variable_name)
{
	char **env = info->env;
	int i, j;

	if (variable_name == NULL || env == NULL)
		return (NULL);

	for (i = 0; env[i] != NULL; i++)
	{
		for (j = 0; variable_name[j] != '\0'; j++)
		{
			if (variable_name[j] != env[i][j])
				break;
		}
		if (variable_name[j] == '\0' && env[i][j] == '=')
			return (env[i] + j + 1);
	}
	return (NULL);
}

/**
 * _mysetenv - initializes a new environment variables
 * @info: pointer to a structure containing potential arguments
 * Return: Always 0
 *
 */
int _mysetenv(info_t *info)
{
	char *name = info->argv[1];
	char *value = info->argv[2];
	char *var;
	int len;

	if (name == NULL || value == NULL)
	{
		write(STDERR_FILENO, "Usage: setenv NAME VALUE\n", 25);
		return (0);
	}

	len = _strlen(name) + _strlen(value) + 2;
	var = malloc(sizeof(char) * len);
	if (var == NULL)
	{
		perror("setenv");
		return (0);
	}

	_strcpy(var, name);
	_strcpy(var, "=");
	_strcpy(var, value);

	if (setenv(name, value, 1) == -1)
	{
		perror("setenv");
		free(var);
		return (0);
	}

	free(var);
	return (0);

}

/**
 * removeEnvironmentVariable - Removes an environment variable
 * @argumentInfo: structure containing potential arguments
 * Return: Always 0
 */
int removeEnvironmentVariable(info_t *argumentInfo)
{
	char *variableName;
	int i, j;
	size_t nameLength;

	if (argumentInfo == NULL || argumentInfo->someField == NULL ||
			argumentInfo->arg[0] == NULL)
		return (0);

	variableName = argumentInfo->args[0];
	nameLength = _strlen(variableName);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(variableName, environ[i],
					nameLength) == 0 && environ[i][nameLength] == '=')
		{
			free(environ[i]);

			for (j = i; environ[j] != NULL; j++)
				environ[j] = environ[j + 1];

			break;
		}
	}
	return (0);
}

/**
 * create_env_list - creates and populate a linked list with
 * environment variables
 * @info: structures containing potential arguments
 * Return: Always 0
 */
int create_env_list(info_t *info)
{
	list_t *env_list = NULL;
	size_t index;

	for (index = 0; environ[index] != NULL; index++)

	{
		add_node_end(&env_list, environ[index], 0);

	}

	info->env = env_list;

	return (0);
}
