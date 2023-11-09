#include "shell.h"

/**
 * add_node_at_start - Adds a node to the beginning of the linked list
 * @head_ref: Address of a pointer to the head node
 * @data: String field of the new node
 * @index: Index used by history
 *
 * Return: Pointer to the newly added node, NULL on failure
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
 * append_node - Appends a node to the end of the linked list
 * @head: Pointer to a pointer to the head node
 * @str: String field of the new node
 * @num: Node index used for history
 *
 * Return: Pointer to the newly appended node, or NULL on failure
 */
node_t *append_node(node_t **head, const char *str, int num)
{
	if (head == NULL || str == NULL)
	{
		return (NULL);
	}

	node_t *new_node = (node_t *)malloc(sizeof(node_t));
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
 * print_strings_in_list - prints only the string
 * elements of a linked list
 * @head: pointer to the first node
 *
 * Return: The total count of nodes in the linked
 * list processed during the print operation
 */
size_t print_strings_in_list(const Node *head)
{
		size_t count = 0;

		while (head != NULL)
		{
				if (head->data != NULL)
				{
						printf("%s\n", head->data);
				}
				else
				{
						printf("(nil)\n");
				}
				head = head->next;
				count++;
		}

		return (count);
}


/**
 * delete_node_at_the_given_index - Deletes a node at the given
 * index in a linked list
 * @head_ref: Address of a pointer to the first node of the linked list
 * @index: Index of the node to be deleted
 * Return: 0 when not successful or 1 on success
 */
int delete_node_at_the_given_index(Node **head_ref, unsigned int index)
{
	Node *current = *head_ref;
	Node *prev = NULL;

	if (current == NULL)
	{
		return (0);
	}

	if (index == 0)
	{
		*head_ref = current->next;
		free(current);
		return (1);
	}

	unsigned int count = 0;
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
 * free_listint - Frees a listint_t list.
 * @head: Pointer to the head of the linked list to be freed.
 */
void free_listint(listint_t *head)
{

				listint_t *current, *next_node;

				current = head;

				while (current != NULL)
				{
						next_node = current->next;
						free(current);
						current = next_node;
				}
}
