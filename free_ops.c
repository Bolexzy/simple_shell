#include "shell.h"

void free_list(list_t *head);

/**
 * free_args - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 */
void free_args(char **args)
{
	size_t i;

	for (i = 0; args[i]; i++)
		free(args[i]);
	free(args);
}

/**
 * free_list - Frees a list_t linked list.
 * @head: The head of the list_t list.
 */
void free_list(list_t *head)
{
	list_t *next;

	while (head)
	{
		next = head->next;
		free(head->str);
		free(head);
		head = next;
	}
}
