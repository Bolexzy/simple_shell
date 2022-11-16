#include "shell.h"

/**
 * get_builtin - Matches a command with a corresponding
 *               lsh builtin function.
 * @cmd: The command to match.
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*get_builtin(char *cmd))(char **args)
{
	builtin_t funcs[] = {
		{ "exit", exit_lsh},
		{"env", printenv},
		{ NULL, NULL}
	};
	unsigned int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (_strcmp(funcs[i].name, cmd) == 0)
			break;
	}

	return (funcs[i].f);
}


/**
 * exit_lsh - Causes normal process termination
 *            for the lsh shell.
 * @args: An array of arguments containing the exit value.
 *
 * Return: If there are no arguments, -3.
 *         If the given exit value is invalid, 2.
 *         O/w - exits with the given status value.
 *
 * Description: Upon returning -3, the program exits back in the main function.
 */
int exit_lsh(char **args)
{
	int status = 0;

	if (args[1])
	{
		if (!_isdigit(args[1]) || (status > INT_MAX))
		{
		dprintf(2, "Illegal number: %s\n", args[1]);
		return (1);
		}
		else
		{
			status  = _atoi(args[1]);
			exit(status);
		}

	}
	exit(status);
}

/**
 * printenv - Prints the current environment.
 * @args: An array of arguments passed to the shell.
 *
 * Return: If an error occurs, -1.
 *	   Otherwise- 0.
 *
 * Description: Prints one variable per line in the
 *              format "variable=value".
 */
int printenv(char **args)
{
	unsigned int idx;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (idx = 0; environ[idx]; idx++)
	{
		write(STDOUT_FILENO, environ[idx], _strlen(environ[idx]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void) args;
	return (0);
}
