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

/**
 * struct info - structure representing information relating to shell command
 * @args: arry of strings representing information relating to shell
 */
typedef struct info
{
	char *args;
	char *env;
	int someField;
} info_t;

/**
 * struct shellinfo - structure containing information specific to a shell
 * @args: array of string representing information relating to shell
 */
typedef struct shellinfo
{
	char *args;
} shellinfo;

/**
 * struct data - structure containing generic data
 * @args: array of strings representing data
 */
typedef struct data
{
	char *args;
} data;


typedef struct Node
{
	int data;
	struct Node* next;
} Node;





#define WRITE_BUF_SIZE 1024  /* Define the buffer size for output */
#define BUF_FLUSH '\0'
#define DELIMITER ' '

#define CMD_AND
#define CMD_OR


/* list_list.c */
Node *add_node_at_start(Node **head_ref, const char *data, int index);
Node *append_node(Node **head, const char *str, int num);
size_t print_strings_in_list(const Node *head);
int delete_node_at_the_given_index(Node **head_ref, unsigned int index);
void free_listint(listint_t *head);

/* list_list1.c */

size_t print_listint(const listint_t *k);
ssize_t find_index_of_node(Node *head_node, Node *target_node);
Node *find_node_with_prefix(Node *head_node,
		char *search_prefix, char next_character);
char **convert_list_to_strings(Node *head_node);
size_t get_list_length(const Node *head_node);

/* str_string1.c */

char *_strncpy(char *dest, char *src, int n);
char *custom_strdup(const char *string);
void custom_puts(const char *str);
int custom_putchar(char s);

/* str_string.c */

int _strlen(char *s);
char *_strcat(char *dest, char *src);
char *custom_starts_with(const char *str, const char *substr);
int custom_str_cmp(char *string1, char *string2);


/** tokenz.c */

char **strtow(char *str, char d);
char **custom_strtow2(char *str, char d);

/* Pplaceholders.c */

void evaluateChainCondition(info_t *data, char *buffer, size_t *position,
				size_t startIndex, size_t length);
int check_delimiter(info_t *info, char *buf, int *pos);
int process_variables(struct info *info);
int update_string(char **str, const char *new_str);
int update_aliases(info_t *info);

/* ca-calloc.c */

char *custom_memset(char *mem, char byte, unsigned int size);
void *resize_memory(void *vold_ptr, size_t old_size, size_t new_size);
void freeStringArray(char **ff);

/*analy- analyzer.c */

char *duplicateSubstring(const char *sourceStr, int startIndex, int endIndex);
char *locatePath(const char *pathString, const char *command);
int isExecutableCommand(shellinfo *shellInfo, char *filePath);

/* memory_utilis.c */

int ffrees(void **pointer);

/* custom_getline.c */

ssize_t bufferChainedCommands(shellinfo *shellInfo, char **buffer,
		size_t *bufferLength);
ssize_t getNextCommand(shellinfo *shellInfo, char **command,
		size_t *commandLen);
ssize_t readBuffer(shellinfo *shellInfo, char *buffer, size_t *size);
int getLine(shellinfo *shellInfo, char **buffer, size_t *size);
void customSigintHandler(__attribute__((unused)) int signalNumber);

/* info_handler.c */

void reset_info(info_t *info);
void initialize_info(info_t *info, char **av);
void release_info(info_t *info, int free_all);

/* Ggetenv.c */

int set_environment_variable(info_t *info, char *variable, char *value);
int _unsetenv(info_t *info, char *variable);
char **duplicate_environ(info_t *info);

/* Eexit.c */

char *_strchr(char *s, char c);
char *_strncat(char *dest, char *src, int n);
char *_strncpy(char *dest, char *src, int n);

/* er_error1.c */

int _custom_atoi(char *s);
void print_error(info_t *info, char *error_type);
int custom_print_d(int num, int output_fd);
char *custom_number_conversion(long int input_num, int target_base,
		int conversion_flags);
void removeComments(char *inputString);

/* er_error.c */

int _custom_putsfd(char *str, int fd);
int writeCharToFileDescriptor(char character, int fileDescriptor);
int custom_eputchar(char c);
void _custom_eputs(char *str);

/* Envvirons.c */

int create_env_list(info_t *info);
int removeEnvironmentVariable(info_t *argumentInfo);
int _mysetenv(info_t *info);
char *_getenv(info_t *info, const char *variable_name);
int _myenv(info_t *info);

/* builtsin1.c */

int displayCommandHistory(shellinfo *shellInfo);
int mimicAlias(shellinfo *shellInfo);
int display_alias(list_t *alias_node);
int set_alias(info_t *info, char *alias_str);
int unset_alias(info_t *info, char *str);

/* builtsin.c */

int _myexit(info_t *info);
int custom_cd(info_t *info);
int _myhelp(info_t *info);

/* Main.c */


#endif
