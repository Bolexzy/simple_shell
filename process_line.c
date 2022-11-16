#include "shell.h"

int _toklen(char *token, char *delim);
int count_toks(char *str, char *delim);
char **_strtok(char *lineptr, char *delim);

/**
 * _toklen - Calculates the length of a token in a string.
 * @token: The input string.
 * @delim: The delimiter character.
 *
 * Return: The delimiter index marking the end of
 *         the intitial token pointed to be str(length).
 */
int _toklen(char *token, char *delim)
{
	int idx = 0, len = 0;

	while (*(token + idx) && *(token + idx) != *delim)
	{
		len++;
		idx++;
	}

	return (len);
}

/**
 * count_toks - Counts the number of delimited
 *                words contained within a string.
 * @str: The input string.
 * @delim: The delimiter character.
 *
 * Return: The number of tokens contained within str.
 */
int count_toks(char *str, char *delim)
{
	int idx, tokens = 0;

	for (idx = 0; str[idx]; idx++)
	{
		if (*(str + idx) != *delim)
		{
			tokens++;
			idx += _toklen(str + idx, delim);
		}
	}
	return (tokens);
}

/**
 * _strtok - Tokenizes a string.
 * @lineptr: The string.
 * @delim: The delimiter character.
 *
 * Return: A pointer to an array of the tokenized words(string).
 */
char **_strtok(char *lineptr, char *delim)
{
	int tokens, idx = 0, t, l, bytes;
	char **args;

	tokens = count_toks(lineptr, delim);
	if (tokens == 0)
		return (NULL);

	args = malloc(sizeof(char *) * (tokens + 2));
	if (!args)
	{
		fprintf(stderr, "lsh: allocation error\n");
		return (NULL);
	}

	for (t = 0; t < tokens; t++)
	{
		while (lineptr[idx] == *delim)
			idx++;

		bytes = _toklen(lineptr + idx, delim);

		args[t] = malloc(sizeof(char) * (bytes + 1));
		if (!args[t])
		{
			for (idx -= 1; idx >= 0; idx--)
				free(args[idx]);
			free(args);
			return (NULL);
		}

		for (l = 0; l < bytes; l++)
		{
			args[t][l] = lineptr[idx];
			idx++;
		}

		args[t][l] = '\0';
	}
	args[t] = NULL;
	args[t + 1] = NULL;

	return (args);
}
