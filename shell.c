#include "shell.h"

int execute(char **args);

/**
 * execute - Executes a command referred to by args in a child process.
 *
 * @args: An array of arguments.
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last executed command.
 */
int execute(char **args)
{
	pid_t child;
	int status, ret = 0, flag = 0;
	char *cmd = args[0];


	if (cmd[0] != '/' && cmd[0] != '.')
	{
		flag = 1;
		cmd = handle_path(cmd);
	}
	child = fork();

	if (child == 0)
	{
	/* child process*/
		if (execve(cmd, args, environ) == -1)
		{
			perror("./shell: command not found");
			exit(0);
		}
	}
	else if (child > 0)
	{
		wait(&status);
		ret = WEXITSTATUS(status);
	}
	else
		ERR("child");

	if (flag)
		free(cmd);

	return (ret);
}

/**
 * main - Entry point.
 *	-  Runs a simple UNIX command interpreter.
 *
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: The return value of executed command / process.
 */
int main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
	int  mode = 1;
	int ret = 0;
	int *pp_ret = &ret;

	while (mode)
	{
		mode = isatty(STDIN_FILENO);
		write(STDOUT_FILENO, "$ ", 2);

		ret = process_args(pp_ret);
		if (ret == EOF)
			continue;
	}

	putchar('\n');
	return (*pp_ret);
}
