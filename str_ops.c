#include "shell.h"

char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strdup(char *s);
int _strcmp(char *s1, char *s2);
int _strlen(const char *s);

/**
 * _strcpy - Copies the string pointed to by src, including the
 *           terminating null byte, to the buffer pointed by dest.
 *
 * @dest: Pointer to the destination of copied string.
 * @src: Pointer to the src of the source string.
 * Return: Pointer to dest.
 */
char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - Concantenates two strings.
 *
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 * Return: Pointer to destination string.
 */
char *_strcat(char *dest, const char *src)
{
	char *destTmp;
	const char *srcTmp;

	destTmp = dest;
	srcTmp =  src;

	while (*destTmp != '\0')
		destTmp++;

	while (*srcTmp != '\0')
		*destTmp++ = *srcTmp++;
	*destTmp = '\0';
	return (dest);
}


/**
 * _strdup - duplicates a str in the heap memory.
 *
 * @s: Type char pointer str
 * Return: duplicated str
 */
char *_strdup(char *s)
{
	char *new;
	size_t len;
	unsigned int i;

	len = _strlen(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);

	for (i = 0; i < len + 1; i++)
		new[i] = s[i];
	return (new);
}

/**
 * _strcmp - Compares two strings.
 * @s1: The first string to be compared.
 * @s2: The second string to be compared.
 *
 * Return: Positive byte difference if s1 > s2
 *         0 if s1 = s2
 *         Negative byte difference if s1 < s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}

/**
 * _strlen - Returns the length of a string.
 *
 * @s: A pointer to the characters string.
 * Return: The length of the character string.
 */
int _strlen(const char *s)
{
	int length = 0;

	if (!s)
		return (length);
	for (length = 0; s[length]; length++)
		;
	return (length);
}
