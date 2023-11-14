#include "shell.h"

/**
 * _puts - function that prints a string, followed by a new line
 * @str: String to print
 */

void _puts(char *str)
{
	while (*str != '\0')
	{
		_putchar(*str++);
	}
		_putchar('\n');
}

/**
 * _putchar - writes the character c to stamdard-output.
 * @c: The character to be printed on the standard-output.
 * Return: 1 on success.
 * On error, -1 is returned and errno is set appropriately.
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}
