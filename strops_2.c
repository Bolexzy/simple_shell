#include "shell.h"

int _isdigit(char *s);

/**
 * _atoi -  convert a string to an integer
 * @s: the sting to convert to integer
 * Description:  convert a string of numbers to an integer
 * Return: integer gotten from string
 */
int _atoi(char *s)
{
	int sign = 1;
	unsigned int num = 0;

	do {
		if (*s == '-')
			sign *= -1;

		else if (*s >= '0' && *s <= '9')
			num = (num * 10) + (*s - '0');

		else if (num > 0)
			break;

	} while (*s++);

	return (num * sign);
}

/**
 * _isdigit - checks if a string contains only digits
 * @s: string to be checked
 * Description: checks if a string contains only digit
 * Return: 1 if string contains only didgit
 *         0 if string has at lest one non-digit character
 */
int _isdigit(char *s)
{
	while (*s != '\0')
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}
