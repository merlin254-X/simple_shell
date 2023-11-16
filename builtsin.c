#include "shell.h"

/**
 * _myhelp - Displays a message indicating that the help function
 * is not yet implemented.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int _myhelp(info_t *info)
{
	(void)info;
	_puts("help call works. Function not yet implemented\n");
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

	if (info->argc == 1)
	{
		target_path = getenv("HOME");
	}
	else
	{
		target_path = info->argv[1];
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

	if (_strcmp(info->argv[0], "exit") != 0)
	{
		return (0);
	}
	if (info->argv[1] != NULL)
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->err_num = 2;
			return (-2);
		}
		status = exitcheck;
	}
	free_info(info);
	exit(status);
}
