#include "shell.h"

/**
 * duplicateSubstring - Duplicates a portion of character from a string
 * @sourceStr: the source string
 * @startIndex: the starting index of the substring to duplicate
 * @endIndex: the end index of the string to duplicate
 * Return: a dynamically allocated string containing the specified
 * substring, or NULL if the operation fails
 */
char *duplicateSubstring(const char *sourceStr, int startIndex, int endIndex)
{
	char *result;
	int length;

	if (sourceStr == NULL || startIndex < 0 || endIndex < 0 ||
			endIndex < startIndex)
	{
		return (NULL);
	}

	length = endIndex - startIndex + 1;
	result = (char *)malloc((length + 1) * sizeof(char));

	if (result == NULL)
	{
		return (NULL);
	}

	strncpy(result, sourceStr + startIndex, length);
	result[length] = '\0';

	return (result);
}

/**
 * locatePath - Finds the full path of a command in the given PATH string
 * @pathString: The PATH string containing a list of directories
 * @command: the command to locate in the PATH
 * Return: A dynamically allocated string containing the full path of the
 * command if found,or NULL if the command is in the specified PATH
 */
char *locatePath(const char *pathString, const char *command)
{
	char *pathStrCopy;
	char *token, *path, *delimiter = ":";
	struct stat st;
	char *concatenateStrings(const char *s1, const char *s2);

	if (command[0] == '/')
		return (strdup(command));

	if (pathString == NULL || pathString[0] == '\0')
		return (NULL);

	pathStrCopy = strdup(pathString);

	token = strtok(pathStrCopy, delimiter);
	while (token != NULL)
	{
		path = concatenateStrings(token, "/");
		path = concatenateStrings(path, command);

		if (stat(path, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			free(pathStrCopy);
			return (path);
		}

		free(path);
		token = strtok(NULL, delimiter);
	}

	free(pathStrCopy);
	return (NULL);
}

/**
 * isExecutableCommand - determines if a file is an executable command
 * @shellInfo: ponter to the shell information struct.
 * @filePath: path to the file
 * Return: 1 if the file is an executable command, 0 otherwise
 */
int isExecutableCommand(shellinfo *shellInfo, char *filePath)
{
	struct stat fileInfo;

	if (access(filePath, F_OK | R_OK) == 0)
	{
		if (stat(filePath, &fileInfo) == 0 &&
				(S_ISREG(fileInfo.st_mode) || S_ISLNK(fileInfo.st_mode)))
		{
			if (fileInfo.st_mode & S_IXUSR ||
					fileInfo.st_mode & S_IXGRP || fileInfo.st_mode & S_IXOTH)
			{
				shellInfo->command = strdup(filePath);
				shellInfo->path = strdup(filePath);
				return (1);
			}
		}
	}
	return (0);
}
