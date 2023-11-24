#include "shell.h"

/**
 * displayCommandHistory - displays the command history list with line numbers.
 * @shellInfo: Pointer to the ShellInfo struct.
 * Return: Always 0
 */
int displayCommandHistory(shellinfo *shellInfo)
{
	print_listint(shellInfo->commandHistory);
	return (0);
}

/**
 * mimicAlias - Mimics the behavior of the alias builtin.
 * @shellInfo: Pointer to the ShellInfo struct.
 * Return: Always 0.
 */
int mimicAlias(shellinfo *shellInfo)
{
	int i;
	char *aliasName, *aliasValue;

    if (shellInfo->argc == 0)
    {
	print_aliases(&shellInfo);
        return (0);
    }

    for (i = 0; i < (*shellInfo->argc); i++)
    {
        aliasName = strtok((char *)shellInfo->argv[i], "=");
        aliasValue = strtok(NULL, "=");

        if (aliasName == NULL || aliasValue == NULL)
        {
            write(STDERR_FILENO, "alias: invalid alias name\n", 26);
            return (-1);
        }

        if (set_alias(shellInfo, aliasName) != NULL)
        {
            upddate_aliases(shellInfo, aliasName, aliasValue);
        }
        else
        {
            set_alias(shellInfo, aliasName, aliasValue);
        }
    }

    return (0);
}

/**
 * display_alias - displays an alias string
 * @alias_node: pointer to the alias node
 *
 * Return: 0 on success, 1 on error
 */
int display_alias(list_t *alias_node)
{
    if (alias_node == NULL)
    {
        return (1);
    }
    write(STDOUT_FILENO, alias_node->name, _strlen(alias_node->name));
    write(STDOUT_FILENO, "='", 2);
    write(STDOUT_FILENO, alias_node->value, _strlen((char *)(alias_node->value)));
    write(STDOUT_FILENO, "'\n", 2);
    return (0);
}

/**
 * set_alias - sets alias to string
 * @info: Structure containing relevant information.
 * @alias_str: The string representing the alias.
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *alias_str)
{
	alias_t *alias = malloc(sizeof(alias));

    if (info == NULL || alias_str == NULL)
    {
        return (1);
    }

    if (alias == NULL)
    {
        return (1);
    }

    alias->str = strdup(alias_str);
    if (alias->str == NULL)
    {
        free(alias);
        return (1);
    }

    alias->next = (struct alias *)info->alias;
    info->alias = (char *)alias;

    return (0);
}

/**
 * unset_alias - Removes an alias from the alias linked list.
 * @info: Pointer to the structure containing potential arguments.
 * @str: The string representing the alias to be removed.
  *
 * Return: Always 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
	char **current = &info->alias;
	char **prev = NULL;

    if (info == NULL || str == NULL)
    {
        return (1);
    }

    while (*current != NULL)
    {
        if (strcmp(*current, str) == 0)
	{
            if (prev == NULL)
	    {
                info->alias = (char *)( *(current + 1));
            }
	    else
	    {
               *prev = *(current + 1);
            }

            free(*current);
              
            return (0);
        }

        prev = current;
        current = (char **)(*(current));
    }

    return (1);
}
