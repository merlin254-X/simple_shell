#include "shell.h"
/**
 * print_listint - prints all the elements of a listint_t list
 * @k: pointer to head of list
 * Return: number of nodes
 */
size_t print_listint(const listint_t *k)
{
	size_t count = 0;

	while (k != NULL)
	{
		int num = k->n;

		if (num < 0)
		{
			_write_char('-');
			num = -num;
		}
		if (num / 10)
			print_listint(num / 10);
		char digit = num % 10 + '0';

		write(1, &digit, 1);
		write(1, "\n", 1);

		k = k->next;
		count++;
	}
	return (count);
}

/**
 * find_index_of_node - finds the index of a node in the linked list
 * @head_node: pointer to the head of the list
 * @target_node: pointer to the head for which the index is to be found
 * Return: index of the node in the list, or -1 if the node is not found
 */
ssize_t find_index_of_node(Node *head_node, Node *target_node)
{
	ssize_t index = 0;
	Node *current = head_node;

	while (current != NULL)
	{
		if (current == target_node)
		{
			return (index);
		}
		index++;
		current = current->next;
	}
	return (-1);
}
/**
 * find_node_with_prefix - returns a node whose string starts
 * with a given prefix
 * @head_node: pointer to the head of the list
 * @search_prefix: prefix to match
 * @next_character: next character after the prefix to match to match
 * Return: pointer to the found node, or NULL if not found
 */
Node *find_node_with_prefix(Node *head_node, const char *search_prefix,
		char next_character)
{
	Node *current = head_node;

	while (current != NULL)
	{
		if (strncmp(current->str, search_prefix, strlen(search_prefix)) == 0 &&
				current->str[strlen(search_prefix)] == next_character)
		{
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

/**
 * convert_list_to_strings - converts linked list nodes to an array oof strings
 * @head_node: pointer to the head node of the linked list
 * Return: array of strings or NULL on failure
 */
char **convert_list_to_strings(listNode *head_node)
{
	if (head_node == NULL)
	{
		return (NULL);
	}

	int count = 0;

	listNode *current = head_node;

	while (current != NULL)
	{
		count++;
		current = current->next;
	}

	char **result = (char **)malloc(count * sizeof(char *));

	if (result == NULL)
	{
		return (NULL);
	}
	current = head_node;
	for (int i = 0; i < count; i++)
	{
		result[i] = (char *)malloc(strlen(current->data) + 1);
		if (results[i] == NULL)
		{
			while (i > 0)
			{
				free(results[i - 1]);
				i--;
			}
			free(result);
			return (NULL);
		}
		strcpy(result[i], current->data);
		current = current->next;
	}

	return (result);
}

/**
 * get_list_length - determines the length of a linked list
 * @head_node: pointer to the first node of the list
 * Return: the size of the list
 */
size_t get_list_length(const Node *head_node)
{
	size_t count = 0;
	const Node *current = head_node;

	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}
