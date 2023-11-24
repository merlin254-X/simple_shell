#include "shell.h"

/**
 * shellMainLoop - main loop of the shell program
 * @paramInfo: the parameter and return information struct
 * @arguments: the argument vector received from main()
 *
 * Return: 0 on successful execution, 1 on error, or error code
 */
int shellMainLoop(infot_t *paramInfo, char **arguments)
{
	char *line = NULL;
	char **args = NULL;
	int status = 0;

	if (paramInfo == NULL || arguments == NULL)
	{
		fputs("Invalid parameters.\n", stderr);
		return (1);
	}

	do
	{
		line = shellReadLine(paramInfo);

		if (line == NULL)
		{
			fputs("Error reading input.\n", stderr);
			return (1);
		}
		args - shellParseLine(line);

		if (args == NULL)
		{
			fputs("Error parsing input.\n", stderr);
			free(line);
			return (1);
		}
		status = shellExecute(args, paramInfo, arguments);

		free(line);
		free(args);
	}
	while (status == 0);

	return (status);
}

/**
 * executeCommand - creates an execution thread to run a command
 * @paramInfo: the parameter and return information struct
 *
 * Return: void
 */
void executeCommand(infot_t *paramInfo)
{
	pid_t childProcessID;

	childProcessID = fork();
	if (childProcessID == -1)
	{
		perror("Error:");
		return;
	}
	if (childProcessID == 0)
	{
		if (execve(paramInfo->path, paramInfo->arguments,
					getEnvironment(paramInfo)) == -1)
		{
			freeInformation(paramInfo, 1);
			if (errno == EACCES)
				exit(127);
			exit(1);
		}
	}
	else
	{
		wait(&(paramInfo->status));
		if (WIFEXITED(paramInfo->status))
		{
			paramInfo->status = WEXITSTATUS(paramInfo->status);
			if (paramInfo->status == 126)
				print_error(paramInfo, "Permission denied\n");
		}
	}
}

/**
 * locateCommand - locate a command in PATH
 * @info: The parameter and return information struct
 * Return: void
 *
 */
void locateCommand(infot_t *info)
{
	char *commandPath = NULL;
	int argCounter = 0, wordCounter = 0;

	info->path = info->argv[0];
	if (info->lineCountFlag == 1)
	{
		info->lineCount++;
		info->lineCountFlag = 0;
	}
	for (argCounter = 0, wordCounter = 0; info->arg[argCounter]; argCounter++)
	{
		if (!isDelimiter(info->arg[argCounter], " \t\n"))
		{
			wordCounter++;
		}
	}
	if (!wordCounter)
	{
		return;
	}
	commandPath = retrieveCommandPath(info, fetchEnvironmentVar(info, "PATH="),
			info->argv[0]);
	if (commandPath)
	{
		info->path = commandPath;
		executeCommand(info);
	}
	else
	{
		if ((interactive(info) || fetchEnvironmentVar(info, "PATH=")
					|| info->argv[0][0] == '/') && isCommand(info, info->argv[0]))
		{
			executeCommand(info);
		}
		else if (*(info->arg) != '\n')
		{
			info->status = 128;
			displayError(info, "not found\n");
		}
	}
}
