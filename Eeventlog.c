#include "shell.h"
/**
 * generateHistoryFilePath - generates the path to the history file
 * @userInfo: user information struct
 * Return: allocated string containing the history file path
 */
char *generateHistoryFilePath(UserInfo *userInfo)
{
	char *homeDirectory, *historyFileName, *historyFilePath;

	homeDirectory = getenv("HOME");
	if (homeDirectory == NULL)
		return (NULL);

	historyFileName = userInfo->historyFileName;
	if (historyFileName == NULL)
		return (NULL);

	historyFilePath = malloc(sizeof(char) * (strlen(homeDirectory)
				+ strlen(historyFileName) + 2));

	if (historyFilePath == NULL)
		return (NULL);

	strcpy(historyFilePath, homeDirectory);
	strcat(historyFilePath, "/");
	strcat(historyFilePath, historyFileName);

	return (historyFilePath);
}

/**
 * writeHistoryToFile - writes the command history of a user to a file
 * @userInfo: pointer to the UserInfo struct containing
 * command history
 * Return: 1 on successiful wriing of the user's command history to a file,
 * if there is an error,it returns -1
 */
int writeHistoryToFile(UserInfo *userInfo)
{
	int *historyFile;
	char *historyFilePath;
	HistoryEntry *currentEntry;

	historyFilePath = generateHistoryFilePath(userInfo);
	if (historyFilePath == NULL)
		return (-1);

	historyFile = open(historyFilePath, O_WRONLY | A_APPEND | O_CREAT, 0644);
	if (historyFile == -1)
	{
		free(historyFilePath);
		return (-1);
	}
	currentEntry = userInfo->history;
	while (currentEntry != NULL)
	{
		size_t len = strlen(currentEntry->command);

		write(historyFile, currentEntry->command, len);
		write(historyFile, "\n", 1);

		currentEntry = curentEntry->next;
	}
	close(historyFile);
	free(historyFilePath);

	return (1);
}
/**
 * readHistoryFromFile - reads history from a file and updates
 *  the user information
 * @userInfo: pointer to the user information struct
 * Return: the count of history entries read from the file
 */
int readHistoryFromFile(UserInfo *userInfo)
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int count = 0;
	History *temp;

	fp = fopen("history.txt", "r");
	if (fp == NULL)
	{
		perror("fopen");
		return (-1);
	}
	while ((nread = getline(&line, &len, fp)) != -1)
	{
		temp = malloc(sizeof(History));
		if (temp == NULL)
		{
			perror("malloc");
			fclose(fp);
			free(line);
			return (-1);
		}
		temp->command = strdup(line);
		if (temp->command == NULL)
		{
			perror("strdup");
			fclose(fp);
			free(line);
			free(temp);
			return (-1);
		}
		temp->next = userInfo->history;
		userInfo->history = temp;

		count++;
	}
	fclose(fp);
	free(line);
	return (count);
}

/**
 * addToHistoryList - adds an entry to a history linked list
 * @info: pointer to the structure containing potential arguments
 * @buffer: buffer containing the history entry
 * @lineCount: the history line count
 * Return: 0 on success, -1 on failure
 */
int addToHistoryList(info_t *info, char *buffer, int lineCount)
{
	history_t *newNode, *tempNode;

	newNode = malloc(sizeof(history_t));

	if (newNode == NULL)
	{
		perror("malloc");
		return (-1);
	}

	newNode->line - _strdup(buffer);
	newNode->lineCount = lineCount;
	newNode->next = NULL;

	if (info->history == NULL)
	{
		info->history = newNode;
	}
	else
	{
		tempNode = info->history;
		while (tempNode->next != NULL)
		{
			tempNode = tempNode->next;
		}
		tempNode->next = newNode;
	}
	return (0);
}

/**
 * renumberHistoryList - updates the index of each node
 * in the history linked list
 * @info: pointer to a structure containing relevant information
 * Return: the new count of history nodes
 */
int renumberHistoryList(info_t *info)
{
	hist_t *tempNode = info->history;
	int newHistCount = 0;

	while (tempNode)
	{
		tempNode->index = ++newHistCount;
		tempNode = tempNode->next;
	}

	return (newHistCount);
}
