#include "shell.h"

/**
 * strtow - Splits a string into words based on a given delimiter
 * @str: The input string
 * @d: The delimiter string
 * Return: A pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char d)
{
	int i;
	int len = strlen(str);
	int wordCount = 0;
	char **words;
	int wordLength;
	int wordIndex;
	int wordStart;

	for (i = 0; i < len; i++)
	{
		if (str[i] != d && (i == 0 || str[i - 1] == d))
		{
			wordCount++;
		}
	}
	words = (char **)malloc(wordCount * sizeof(char *));

	if (!words)
	{
		perror("Memory allocation failed");
		return (NULL);
	}

	wordIndex = 0;
	wordStart = 0;

	for (i = 0; i < len; i++)
	{
		if (str[i] == d)
		{
			wordLength = i - wordStart;

			words[wordIndex] = (char *)malloc((wordLength + 1) * sizeof(char));
			if (!words[wordIndex])
			{
				perror("Memory allocation failed");
				return (NULL);
			}
			strncpy(words[wordIndex], str + wordStart, wordLength);
			words[wordIndex][wordLength] = '\0';
			wordIndex++;
			wordStart = i + 1;
		}
	}
	wordLength = len - wordStart;

	words[wordIndex] = (char *)malloc((wordLength + 1) * sizeof(char));
	if (!words[wordIndex])
	{
		perror("Memory allocation failed");
		return (NULL);
	}
	strncpy(words[wordIndex], str + wordStart, wordLength);
	words[wordIndex][wordLength] = '\0';

	return (words);
}

/**
 * custom_strtow2 - Splits a string into words based on a delimiter
 * @str: The input string
 * @d: The delimiter character
 *
 * Return: A pointer to an array of strings, or NULL on failure
 */
char **custom_strtow2(char *str, const char d)
{
	int word_count = 0;
	char **words = NULL;
	char *token;

	words = (char **)malloc(sizeof(char *));
	if (words == NULL)
	{
		return (NULL);
	}

	token = strtok(str, d);
	while (token != NULL)
	{
		words[word_count] = (char *)malloc(strlen(token) + 1);
		if (words[word_count] == NULL)
		{
			free(words);
			return (NULL);
		}
		strcpy(words[word_count], token);
		word_count++;

		words = (char **)realloc(words, (word_count + 1) * sizeof(char *));
		if (words == NULL)
		{
			return (NULL);
		}

		token = strtok(NULL, d);
	}

	words[word_count] = NULL;

	return (words);
}
