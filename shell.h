#ifndef _SHELL_H_
#define _SHELL_H_

#define ERR(s) {\
	perror((s));\
	exit(EXIT_FAILURE); }

#define STR_DELIM " \t\n\a"
#define EXIT -3
#define EOF -2
#define LSH_BUFSIZE 1024
extern char **environ;

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

/**
 * struct node - A new struct type defining a linked list.
 * @str: A directory path.
 * @next: A pointer to another struct list_t.
 */
typedef struct node
{
	char *str;
	struct node *next;
} list_t;

/**
 * struct builtins - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtins
{
	char *name;
	int (*f)(char **args);
} builtin_t;

/* commands */
int execute(char **args);
ssize_t readline(char **buf);
int _toklen(char *token, char *delim);
char **_strtok(char *lineptr, char *delim);
int count_toks(char *str, char *delim);

/* str_ops.c */
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strdup(char *s);
int _strcmp(char *s1, char *s2);
int _strlen(const char *s);
int _atoi(char *s);
int _isdigit(char *s);

/* environ.c */
char *_getenv(const char *name);

/* getline.c */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_getline(void);
char *read_line();

/* sort.c*/
list_t *_getpathdir(char *path);
char *handle_path(char *command);

/* inputs.c */
int process_args(int *pp_ret);
int exec_args(char **args, int *pp_ret);

/* builtins.c */
int (*get_builtin(char *cmd))(char **args);
int printenv(char **args);
int exit_lsh(char **args);

/* free_ops.c */
void free_list(list_t *head);
void free_args(char **args);

/* linked_list.c */
list_t *add_node_end(list_t **head, char *dir);

#endif /* shell_h */
