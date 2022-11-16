#include "shell.h"

/**
 * _getenv - Searches for an environmental variable.
 * @name: The name of the environmental variable requested.
 *
 * Return: If the environmental variable does not exist - 0.
 *         Otherwise - a pointer to the environmental variable value.
 */
char *_getenv(const char *name)
{
	int i, j;
	int equal;

	for (i = 0; environ[i] != NULL; i++)
	{
		equal = 1;
		for (j = 0; environ[i][j] != '='; j++)
		{
			if (name[j] != environ[i][j])
			{
				equal = 0;
				break;
			}
		}
		if (equal)
		{
			return (&environ[i][j + 1]);
		}
	}
	return (NULL);
}
