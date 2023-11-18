#include "shell.h"

/**
 * bufferChainedCommands - Reads and buffers chained commands from stdin.
 * @shellInfo: Pointer to the shell information structure.
 * @buffer: Address of the buffer to store the command.
 * @bufferLength: Address of the variable to store the buffer length.
 * Return: Bytes read or -1 on EOF or error.
 */
ssize_t bufferChainedCommands(shellinfo *shellInfo, char **buffer, size_t *bufferLength)
{
	ssize_t bytesRead;
	char *line = NULL;
	size_t lineLength = 0;

	bytesRead = getline(&line, &lineLength, stdin);
	if (bytesRead == -1)
	{
		free(line);
		return (-1);
	}
	if (line[bytesRead - 1] == '\n')
	{
		line[bytesRead - 1] = '\0';
		bytesRead--;
	}

	if (strchr(line, ';'))
	{
		shellInfo->inputBuffer = line;
		shellInfo->inputBufferLength = (char *)bytesRead;
		bytesRead = getNextCommand(shellInfo, buffer, bufferLength);
	}
	else
	{
		*buffer = line;
		*bufferLength = bytesRead;
	}
	return (bytesRead);
}

/**
 * getNextCommand - Retrieves the next command from the input buffer
 * @shellInfo: Pointer to the ShellInfo struct containing input information.
 * @command: Pointer to a char pointer where the command will be stored
 * @commandLen: Pointer to a size_t where the length of the command will be stored.
 * Return: The number of bytes read for the command
 * or 0 if no more commands are available.
 */
ssize_t getNextCommand(shellinfo *shellInfo, char **command, size_t *commandLen)
{	
	size_t start;
	size_t end;

	if ((size_t)shellInfo->currentPosition >= (unsigned char)*(shellInfo->inputBufferSize))
	{
		*command = NULL;
		*commandLen = 0;
		return (0);
	}
	start = (size_t)shellInfo->currentPosition;

	while ((size_t)shellInfo->currentPosition < *(shellInfo->inputBufferSize) &&
			(unsigned char)shellInfo->inputBuffer[*(shellInfo->currentPosition)](unsigned char) != ';' && (unsigned char)shellInfo->inputBuffer[*(shellInfo->currentPosition)](unsigned int) != '\0')
	{
		shellInfo->currentPosition++;
	}

	end = (size_t)shellInfo->currentPosition;

	*commandLen = end - start;
	*command = malloc((*commandLen + 1) * sizeof(char));
	if (*command == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	memcpy(*command, shellInfo->inputBuffer + start, *commandLen);
	(*command)[*commandLen] = '\0';

	if ((size_t)*(shellInfo->currentPosition) < *(shellInfo->inputBufferSize) && (unsigned char)'\0' !=
			shellInfo->inputBuffer[*((size_t *)shellInfo->currentPosition)])
	{
		shellInfo->currentPosition++;
	}
	else
	{
		shellInfo->inputBuffer[shellInfo->currentPosition] == '\0';
	}
	

	return (*commandLen);
}

/**
 * readBuffer - Reads data into a buffer.
 * @shellInfo: Pointer to the ShellInfo struct containing
 * file descriptor and buffer information.
 * @buffer: Pointer to the buffer where data will be stored.
 * @size: Pointer to the size variable indicating the size of the buffer.
 * Return: The number of bytes read, or -1 on error.
 */
ssize_t readBuffer(shellinfo *shellInfo, char *buffer, size_t *size)
{
	ssize_t bytesRead;

	if (shellInfo == NULL || buffer == NULL || size == NULL)
	{
		return (-1);
	}
	bytesRead = read(*(shellInfo->fileDescriptor), buffer, *size);
	if (bytesRead < 0)
	{
		perror("read");
		return (-1);
	}
	*size = bytesRead;
	return (bytesRead);
}
/**
 * getLine - Reads the next line of input from STDIN.
 * @shellInfo: Pointer to the shell information struct.
 * @buffer: Address of pointer to buffer, preallocated or NULL.
 * @size: Size of preallocated buffer if not NULL.
 *
 * Return: The number of bytes read, or -1 on error or EOF.
 */
int getLine(shellinfo *shellInfo, char **buffer, size_t *size)
{
	char *tempBuffer;
	size_t bufferSize;
	size_t index = 0;
	ssize_t bytesRead;
	char currentChar;

	if (shellInfo == NULL || buffer == NULL || size == NULL)
	{
		return (-1);
	}

	tempBuffer = *buffer;
	bufferSize = *size;

	if (tempBuffer == NULL || bufferSize < 2)
	{
		bufferSize = BUFSIZ;
		tempBuffer = realloc(tempBuffer, bufferSize);
		if (tempBuffer == NULL)
		{
			return (-1);
		}
	}
	while (1)
	{
		bytesRead = read(STDIN_FILENO, &currentChar, 1);

		if (bytesRead <= 0)
		{
			break;
		}

		tempBuffer[index++] = currentChar;

		if (index >= bufferSize - 1)
		{
			bufferSize += BUFSIZ;
			tempBuffer = realloc(tempBuffer, bufferSize);
			if (tempBuffer == NULL)
			{
				return (-1);
			}
		}
		if (currentChar == '\0')
		{
			break;
		}
	}
	tempBuffer[index] = '\0';
	*buffer = tempBuffer;
	*size = bufferSize;
	return (bytesRead > 0 ? index : (size_t)bytesRead);
}

/**
 * customSigintHandler - Custom handling for Ctrl-C signal.
 * @signalNumber: The signal number.
 *
 * Return: void
 */
void customSigintHandler(__attribute__((unused)) int signalNumber)
{
	puts("\n$ ");
	
}
