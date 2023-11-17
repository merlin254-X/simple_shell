#include "shell.h"

#define char *args[MAX_ARGS];

/**
 * _myhelp - Displays a message indicating that the help function
 * is not yet implemented.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int _myhelp(info_t *info)
{
	(void)info;
	puts("help call works. Function not yet implemented\n");
	return (0);
}

/**
 * custom_cd - Changes the current directory of the process.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int custom_cd(info_t *info)
{
	char *target_path;
	int change_status;

	if (info->args != NULL)
	{
		target_path = getenv("HOME");
	}
	else
	{
		target_path = &info->args[1];
	}
	change_status = chdir(target_path);
	if (change_status == -1)
	{
		perror("custom_cd");
		return (1);
	}
	return (0);
}

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 * (-2) if there is an error in conversion
 */
int _myexit(info_t *info)
{
	int status = 0;
	int exitcheck;

	if (strcmp(info->args[0], "exit") != 0)
	{
		return (0);
	}
	if (info->args[1] != NULL)
	{
		char num_str;		
		long int num;

		num_str = '1';
		num = strtol(&num_str, NULL, 10);

		if (*num_str != '\0')
		{
			info->err_num = 2;
			return (-2);
		}
		status = exitcheck;
	}
	reset_info(info);
	exit(status);
}
