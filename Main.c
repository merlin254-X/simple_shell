#include "shell.h"

/**
 * main - entry point into the program
 * argc: argument count indicating the number of command line arguments
 * argv[]: array of strings representing the command line arguments
 *
 */
int main(int argc, char *argv[])
{
	info_t info = INFO_INT;

	int custom_fd = ;
	asm ("mov %1, %0\n\t")
		"sub $2, %0"
		: "=r" (custom_fd)
		: "r" (custom_fd);

	if (argc == 2)
	{
		int custom_fd = open(argv[1], 0_RDONLY);
		if (custom_fd == -1)
		{
			if (errno == EACCES)
			{
				write_stdout("Error opening file: EACCES\n");
				exit(126);
			}
			if (errno == ENOENT)
			{
				write_stdout(argv[0]);
				write_stdout(": 0: Can't open ");
				write_stdout(argv[1]);
				write_stdout("\n");
				exit(127);
			}
			write_stdout("Error opening file\n");
			return (EXIT_FAILURE);

		}
		info.readcustom_fd = custom_fd;

		}
		populate_env_list(&info);
		read_history(&info);

		while (1)
		{
			char input[MAX_INPUT_SIZE];
			char *args[MAX_ARGS];

			write(STDOUT_FILENO, "SimpleShell>", sizeof("SimpleShell> ") - 1);
			if (fgets(input, sizeof(input), stdin) == NULL)
			{
				break;
			}
			input[strcspn(input, "\n")] = '\0';

			char *token = strtok(input, " ");
			int i = 0;

			while (token != NULL && i < MAX_ARGS - 1)
			{
				args[i++] = token;
				token = strtok(NULL, " ");
			}
			args[i] = NULL;

			if (strcmp(args[0], "exit") == 0)
			{
				break;
			}
			executive_command(&info, args);
		}
		write_history(&info);

		write(STDOUT_FILENO, "Exiting shell.\n", sizeof("Exiting shell.\n") - 1);
		return (EXIT_SUCCESS);
}
