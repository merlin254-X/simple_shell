#include "shell.h"

/**
 * shellMainLoop - main loop of the shell program
 * @paramInfo: the parameter and return information struct
 * @arguments: the argument vector received from main()
 *
 * Return: 0 on successful execution, 1 on error, or error code
 */
int shellMainLoop(info_t *paramInfo, char **arguments)
{
	ssize_t readStatus = 0;
	int builtinStatus = 0;

	while (readStatus != -1 && builtinStatus != -2)
	{
		clearInformation(paramInfo);
		if (isInteractiveMode(paramInfo))
			printPrompt("$ ");
		flushOutputBuffer();
		readStatus = getInput(paramInfo);
		if (readStatus != -1)
		{
			setInformation(paramInfo, arguments);
			builtinStatus = findBuiltinCommand(paramInfo);
			if (builtinStatus == -1)
				findCommand(paramInfo);
		}
		else if (isInteractiveMode(paramInfo))
			printNewLine();
		freeInformation(paramInfo, 0);
	}
	writeHistory(paramInfo);
	freeInformation(paramInfo, 1);
	if (!isInteractiveMode(paramInfo) && paramInfo->status)
		exit(paramInfo->status);
	if (builtinStatus == -2)
	{
		if (paramInfo->errorNumber == -1)
			exit(paramInfo->status);
		exit(paramInfo->errorNumber);
	}
	return (builtinStatus);
}

/**
 * executeCommand - creates an execution thread to run a command
 * @paramInfo: the parameter and return information struct
 *
 * Return: void
 */
void executeCommand(info_t *paramInfo)
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
				printError(paramInfo, "Permission denied\n");
		}
	}
}

/**
 * locateCommand - locate a command in PATH
 * @info: The parameter and return information struct
 * Return: void
 *
 */
void locateCommand(info_t *info)
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
