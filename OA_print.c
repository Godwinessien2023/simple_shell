#include "shell.h"

/**
 * _OA_printer - Print to standard-output
 * @letters: Output to be printed to standard-output
 * Return: void
 */

void _OA_printer(const char *letters)
{
	while (isatty(STDOUT_FILENO))
	{
		write(STDOUT_FILENO, letters, _len(letters));
	}
}
