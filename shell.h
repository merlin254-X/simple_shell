#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
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
	int value;
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
	int *value;
	char *name;
	unsigned int len;
	struct list_s *next;
} list_t;

typedef struct alias {
    char *name;
    char *value;
    char *str;
    struct alias *next;
} alias_t;

/**
 * struct info - structure representing information relating to shell command
 * @args: arry of strings representing information relating to shell
 */
typedef struct info
{
	char *args;
	char **env;
        char *alias;
	int err_num;
	int someField;
	int status;
	int errorNumber;
	char path;
	char *command;
	char arguments;
	char **argv;
	
	int lineCount;
	int lineCountFlag;
	char interactive;
	
	char *address;
	int *history;
	int contactNumber;
	char argc;
	char **environ;
	char ** environment;
	int env_size;
	list_t *env_list;
	char *name;
	char *arg;
	int error;
	int command_buffer_type;
	
	

} infot_t;

/**
 * struct shellinfo - structure containing information specific to a shell
 * @args: array of string representing information relating to shell
 */
typedef struct shellinfo
{
	char *argc;
	int *commandHistory;
	char *inputBuffer;
	char *inputBufferLength;
	int *currentPosition;
	char *inputBufferSize;
	char *fileDescriptor;
	char *argv;
	char *args;
	char *command;
	char *history;
	char *historyFileName;
	char *path;
	char *inputIndex;
} shellinfo;




typedef struct Node
{
        char *data;
	struct Node* next;
	int index;
	char *str;
} Node;


typedef struct history_node
{
    char *command;	
    struct history_t *next;
} history_t;






#define WRITE_BUF_SIZE 1024  /* Define the buffer size for output */
#define BUF_FLUSH '\0'
#define DELIMITER ' '


#define CMD_OR 1
#define CMD_AND 1

/* list_list.c */
Node *add_node_at_start(Node **head_ref, const char *data, int index);
void add_node_at_end(Node **head, const char *str, int num);
size_t print_strings_in_list(const Node *head);
int delete_node_at_the_given_index(Node **head_ref, unsigned int index);
void free_listint(listint_t *head);

/* list_list1.c */

size_t print_listint(const listint_t *k);
ssize_t find_index_of_node(Node *head_node, Node *target_node);
Node *find_node_with_prefix(Node *head_node,
		const char *search_prefix, char next_character);
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
char **custom_strtow2(char *str);

/* Pplaceholders.c */

void evaluateChainCondition(infot_t  *data, char *buffer, size_t *position,
				size_t startIndex, size_t length);
int check_delimiter(char *buf, int *pos);
int process_variables(struct info *info);
int update_string(char **str, const char *new_str);
int update_aliases(infot_t *info);

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

void reset_info(infot_t *info);
void initialize_info(infot_t *info, char **av);
void release_info(infot_t *info, int free_all);

/* Ggetenv.c */

int set_environment_variable(infot_t *info, char *variable, char *value);
int _unsetenv(infot_t *info, char *variable);
char **duplicate_environ(infot_t *info);

/* Eexit.c */

char *_strchr(char *s, char c);
char *_strncat(char *dest, char *src, int n);
char *_strncpy(char *dest, char *src, int n);

/* er_error1.c */

int _custom_atoi(char *s);
void print_error(infot_t *info, char *error_type);
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

int create_env_list(infot_t *info);
int removeEnvironmentVariable(infot_t *argumentInfo);
int _mysetenv(infot_t *info);
char *_getenv(const infot_t *info, const char *variable_name);
int _myenv(infot_t *info);

/* builtsin1.c */

int displayCommandHistory(shellinfo *shellInfo);
int mimicAlias(shellinfo *shellInfo);
int display_alias(list_t *alias_node);
int set_alias(infot_t *info, char *alias_str);
int unset_alias(infot_t *info, char *str);

/* builtsin.c */

int _myexit(infot_t *info);
int custom_cd(infot_t *info);
int _myhelp(infot_t *info);

/* main.c */

int main(int argc, char *argv[]);

/** Eeventlog.c */

char *generateHistoryFilePath(shellinfo *shellInfo);
int write_history(shellinfo *shellInfo);
int readHistoryFromFile(shellinfo *shellInfo);
int addToHistoryList(infot_t *info, char *buffer, int lineCount);
int renumberHistoryList(infot_t *info);
#endif
