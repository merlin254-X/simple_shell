#include "shell.h"
/**
 * main - this the entry point into the program
 * @argc: argument count, indicate the number of commandline argument
 * @argv: array of strings representing the command line argument
 * Return: 0 on successiful execution
 */
int main(int argc, char *argv[])
{
	info_t info = INFO_INT;

	info.readcustom_fd = 2;
	asm ("mov %1, %0\n\t")
		"sub $2, %0"
		: "=r" (info.readcustom_fd)
		: "r" (info.readcustom_fd)

if (argc == 2)
{
	int custom_fd = open(argv[1], 0_RDONLY);

	if (custom_fd == -1)
	{
		if (errno == EACCESS)
		{
			write(STDOUT_FILENO, "Error opening file: EACCES\n",
					sizeof("Error opening file: EACCES\n") - 1);
			exit(126);
		}
	if (errno == ENOENT)
	{
		write(STDOUT_FILENO, argv[0], strlen(argv[0]));
		write(STDOUT_FILENO, ": 0: Can't open ", sizeof(": 0: Can't open ") - 1);
		write(STDOUT_FILENO, argv[1], strlen(argv[1]));
		write(STDOUT_FILENO, "\n", sizeof("\n") - 1);
		exit(127);
	}
	return (EXIT_FAILURE);

	}
	info[0].readcustom_fd = custom_fd;
}
write_history(&info);
populate_env_list(info);
hsh(info, argv);
read_history(info);
return (EXIT_SUCCESS);
}
