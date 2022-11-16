#include "shell.h"

int process_args(int *pp_ret);

/**
 * exec_args - Calls the execution of a command.
 *
 * @args: An array of arguments.
 * @pp_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int exec_args(char **args, int *pp_ret)
{
	int ret = 0, i;
	int (*builtin)(char **args);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1);
		if (ret != EXIT)
			*pp_ret = ret;
	}
	else
	{
		*pp_ret = execute(args);
		ret = *pp_ret;
	}

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (ret);
}

/**
 * process_args - Processes (Gets & calls) and runs the execution of a command.
 *
 * @pp_ret: The return value of the parent process' last executed command.
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized, -1.
 *         O/w - The exit value of the last executed command.
 */
int process_args(int *pp_ret)
{
	int ret = 0;
	char *linebuf = NULL;
	char **args;

	linebuf = read_line();
	if (*linebuf == '\0')
		return (EOF);

	args = _strtok(linebuf, " ");

	if (!args)
	{
		free(args);
		return (ret);
	}
	if (args)
		ret = exec_args(args,  pp_ret);

	return (ret);
}
