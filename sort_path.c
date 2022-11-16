#include "shell.h"

list_t *_getpathdir(char *path);

/**
 * handle_path - Locates a command in the PATH.
 * @command: The command to locate.
 *
 * Return: If an error occurs or the command cannot be located - NULL.
 *         Otherwise - a pointer to the full pathname of the command.
 */
char *handle_path(char *command)
{
	char *path, *temp;
	list_t *dirs, *head;
	struct stat st;

	path = _getenv("PATH");

	dirs = _getpathdir(path);
	head = dirs;

	while (dirs)
	{
		temp = malloc(_strlen(dirs->str) + _strlen(command) + 2);
		if (!temp)
			return (NULL);

		_strcpy(temp, dirs->str);
		_strcat(temp, "/");
		_strcat(temp, command);

		if (stat(temp, &st) == 0)
		{
			free(head);
			return (temp);
		}

		dirs = dirs->next;
		free(temp);
	}

	return (NULL);
}

/**
 * _getpathdir - Tokenizes a colon-separated list of
 *                directories into a list_t linked list.
 * @path: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */
list_t *_getpathdir(char *path)
{
	list_t *head = NULL;
	char **dirs = NULL, *pathcopy;
	unsigned int idx;

	pathcopy = strdup(path);
	if (!path || !pathcopy)
		return (NULL);

	dirs = _strtok(pathcopy, ":");
	free(pathcopy);
	if (!dirs)
		return (NULL);

	for (idx = 0; dirs[idx]; idx++)
	{
		if (add_node_end(&head, dirs[idx]) == NULL)
		{
			free(head);
			free(dirs);
			return (NULL);
		}
	}
	free(dirs);
	return (head);
}
