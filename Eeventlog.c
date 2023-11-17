#include "shell.h"
/**
 * generateHistoryFilePath - generates the path to the history file
 * @shellInfo: user information struct
 * Return: allocated string containing the history file path
 */
char *generateHistoryFilePath(shellinfo *shellInfo)
{
	char *homeDirectory, *historyFileName, *historyFilePath;

	homeDirectory = getenv("HOME");
	if (homeDirectory == NULL)
		return (NULL);

	historyFileName = shellInfo->historyFileName;
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

/**
 * write_history - create,modify, append the files
 * @info: pointer to struct info_t containing arguments
 * Return: 1 when successiful, -1 on failure
 *
 *
 */
int write_history(info_t *info)
{
	ssize_t fp;
	char *filename = generateHistoryFilePath(info);
	list_t *node = NULL;

	fp = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);

	if (fp == -1)
	{
		return (-1);
	}

	for (node = info->history; node; node = node->next)
	{
		_fputs(fp, node->str, strlen(node->str));
		_fputs(fp, "\n", 1);
	}
	close(fp);
	return (1);

}
/**
 * readHistoryFromFile - reads history from a file and updates
 *  the user information
 * @shellInfo: pointer to the user information struct
 * Return: the count of history entries read from the file
 */
int readHistoryFromFile(shellinfo *shellInfo)
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
		temp->next = shellInfo->history;
		shellInfo->history = temp;

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
