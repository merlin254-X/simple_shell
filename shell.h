#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/**
 * struct listint_s - singly linked list
 * @n: integer
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 *
 */
typedef struct listint_s
{
    int n;
    struct listint_s *next;
} listint_t;

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct list_s
{
    char *str;
    unsigned int len;
    struct list_s *next;
} list_t;

#define WRITE_BUF_SIZE 1024  /* Define the buffer size for output */
#define BUF_FLUSH '\0'
#define DELIMITER ' '


/* llists.c */
Node *add_node_at_start(Node **head_ref, const char *data, int index);
node_t *append_node(node_t **head, const char *str, int num);
size_t print_strings_in_list(const Node *head);
int delete_node_at_the_given_index(Node **head_ref, unsigned int index);
void free_listint(listint_t *head);

/* llists5.c */
size_t print_listint(const listint_t *k);
ssize_t find_index_of_node(Node *head_node, Node *target_node);
Node *find_node_with_prefix(Node *head_node, char *search_prefix, char next_character);
char **convert_list_to_strings(ListNode *head_node);
size_t get_list_length(const Node *head_node);

/* sstring1.c */

char *_strncpy(char *dest, char *src, int n);
char *custom_strdup(const char *string);
void custom_puts(const char *str);
int custom_putchar(char s);

/* sstring.c */

int _strlen(char *s);
char *_strcat(char *dest, char *src);
char *custom_starts_with(const char *str, const char *substr);
int custom_str_cmp(char *string1, char *string2);


/** tokenz.c */

char **strtow(char *str, char d);
char **custom_strtow2(char *str, char d);


#endif
