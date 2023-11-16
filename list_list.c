#include "shell.h"

/**
 * add_node_at_start - Adds a node to the beginning of the linked lis
 * @head_ref: Address of a pointer to the head node
 * @data: string field of the new node
 * @index: index used by history
 * Return: pointer to the newly added node, NULL on failure
 */
Node *add_node_at_start(Node **head_ref, const char *data, int index)
	{
		Node *new_node = (Node *)malloc(sizeof(Node));

		if (new_node == NULL)
		{
			return (NULL);
		}
		strcpy(new_node->data, data);
		new_node->index = index;

		new_node->next = *head_ref;
		*head_ref = new_node;

		return (new_node);
	}
/**
 * append_node - appends a node to the end of the linked list
 * @head: pointer to a pointer to a head node
 * @str: string field of the new node
 * @num: node index used for history
 *
 * Return: pointer to the newly appended node, or NULL on failure
 */
node_t *append_node(node_t **head, const char *str, int num)
	{
		if (head == NULL || str == NULL)
		{
			return (NULL);
		}
		node_t *new_node == (node_t *)malloc(sizeof(node_t));

		if (new_node == NULL)

		{
			return (NULL);
		}

		new_node->data = strdup(str);
		new_node->index = num;
		new_node->next = NULL;

		if (*head == NULL)
		{
			*head = new_node;
			return (new_node);
		}

		node_t *current_node = *head;

		while (current_node->next != NULL)
		{
			current_node = current_node->next;
		}
		current_node->next = new_node;

		return (new_node);


	}

/**
 * write_strings_in_list - prints only the string
 * elements of a linked list
 * @head: pointer to the first node
 * Return: the total count of the nodes in th linked list
 * proceede during the print execution
 */
size_t write_strings_in_list(const Node *head)
{
	size_t count = 0;

	while (head != NULL)
	{
		if (head->data != NULL)
		{
			write(1, head->data, _strlen(head->data));
			write(1, "\n", 1);
		}
		else
		{
			write(1, "(nil)\n", 6);
		}
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * delete_node_at_the_given_index - deletes a node at the given
 * index in a linked list
 * @head_ref: address of a pointer to the first node of the linked list
 * @index: index of the node to be deleted
 * Return: 0 when not successiful or 1 on success
 */
int delete_node_at_the_given_index(Node **head_ref, unsigned int index)
{
	unsigned int count = 0;
	Node *current = *head_ref;
	Node *prev = NULL;

	if (current == NULL)
	{
		return (0);
	}

	if (index == 0)
	{
		*head_ref = curent->next;
		free(current);
		return (1);
	}

	count = 0;
	while (current != NULL && count != index)
	{
		prev = current;
		current = current->next;
		count++;
	}

	if (current == NULL)
	{
		return (0);
	}

	prev->next = current->next;
	free(current);
	return (1);
}

/**
 * free_listint - frees a listint_t list
 * @head: pointer to the head of the linked list to be freed
 */
void free_listint(listint_t *head)
{
	listint_t *current_node, *next_node;

	current_node = head;

	while (current_node != NULL)
	{
		next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}
}
