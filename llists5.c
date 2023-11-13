#include "shell.h"

/**
 * print_listint - prints all the elements of a listint_t list
 * @k: pointer to head of list
 *
 * Return: number of nodes
 */
size_t print_listint(const listint_t *k)
{
		size_t count = 0;

		while (k != NULL)
		{
				printf("%d\n", k->n);
				k = k->next;
				count++;
		}

		return (count);
}
/**
 * print_listint - prints all the elements of a listint_t list
 * @k: pointer to head of list
 *
 * Return: number of nodes
 */
size_t print_listint(const listint_t *k)
{
    size_t count = 0;

    while (k != NULL)
    {
        int num = k->n;

        // Write the integer to stdout
        if (num < 0)
        {
            write(1, "-", 1);
            num = -num;
        }

        if (num / 10)
            print_listint(num / 10);

        char digit = num % 10 + '0';
        write(1, &digit, 1);

        // Write newline character
        write(1, "\n", 1);

        k = k->next;
        count++;
    }

    return count;
}


}

/**
 * find_index_of_node - Finds the index of a node in the linked list
 * @head_node: Pointer to the head of the list
 * @target_node: Pointer to the node for which the index is to be found
 *
 * Returns: Index of the node in the list, or -1 if the node is not found
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
 * find_node_with_prefix - Returns a node whose string starts with a given prefix
 * @head_node: Pointer to the head of the list
 * @search_prefix: Prefix to match
 * @next_character: Next character after the prefix to match
 */

Node *find_node_with_prefix(Node *head_node, char *search_prefix, char next_character)
{
	Node *current = head_node;

	while (current != NULL)
	{
		if (strncmp(current->str, search_prefix, strlen(search_prefix)) == 0)
		{
			if (current->str[strlen(search_prefix)] == next_character)
			{
				return (current);
			}
		}
		current = current->next;
	}

	return (NULL);
}

/**
 * find_node_with_prefix - Returns a node whose string starts with a given prefix
 * @head_node: Pointer to the head of the list
 * @search_prefix: Prefix to match
 * @next_character: Next character after the prefix to match
 * Return: Pointer to the found node, or NULL if not found
 */
Node *find_node_with_prefix(Node *head_node, const char *search_prefix, char next_character)
{
    Node *current = head_node;

    while (current != NULL)
    {
        if (strncmp(current->str, search_prefix, strlen(search_prefix)) == 0 &&
            current->str[strlen(search_prefix)] == next_character)
        {
            return current;
        }

        current = current->next;
    }

    return NULL;
}


/**
 * convert_list_to_strings - Converts linked list
 * nodes to an array of strings
 * @head_node: Pointer to the head node of the linked list
 *
 * Return: Array of strings or NULL on failure
 */
char **convert_list_to_strings(ListNode *head_node)
{
	if (head_node == NULL)
	{
		return (NULL);
	}

	int count = 0;
	ListNode *current = head_node;
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
		if (result[i] == NULL)
		{
			while (i > 0)
			{
				free(result[i - 1]);
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
 * get_list_length - Determines the length of a linked list
 * @head_node: Pointer to the first node of the list
 * Returns: The size of the list
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
