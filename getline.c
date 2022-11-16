#include "shell.h"

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_getline(void);

/**
 * read_line - Points to input buffer from getline.
 * Return: pointer to buffer string.
 */
char *read_line()
{
	char *buf = NULL;

	buf = _getline();

	if (buf == NULL)
	{
		exit(0);
	}

	return (buf);
}

/**
 * _realloc - reallocates a memory block.
 *
 * @ptr: pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	if (ptr == NULL)
		ptr = malloc(new_size);

	if (new_size == old_size)
		return (ptr);

	free(ptr);
	ptr = malloc(new_size);

	return (ptr);
}

/**
 * _getline - Reads command input from a stream(STDIN).
 * Return: input buffer.
 */
char *_getline(void)
{
	int buffsize = LSH_BUFSIZE, position = 0;
	unsigned int old_size;
	ssize_t r;
	char *buffer = malloc(sizeof(char) * buffsize);
	char c;

	if (!buffer)
	{
		ERR("lsh: allocation error\n");
		return (NULL);
	}

	while (1)
	{
		/* Read a character */
		r = read(0, &c, 1);
		if (c == '0' || c == '\n' || r < 0)
		{
			buffer[position] = '\0';
			return (buffer);
		}
		else if (c == '\0')
			return (NULL);

		buffer[position] = c;
		position++;
		if (position >= buffsize)
		{
			old_size = buffsize;
			buffsize += LSH_BUFSIZE;
			buffer = _realloc(buffer, old_size, buffsize);

			if (!buffer)
				return (NULL);
		}
	}
}
