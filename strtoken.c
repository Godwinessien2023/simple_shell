#include "shell.h"

/**
 * _getminenv - Gets the value of an environment variable
 * @name: Name of the variable to get
 * Return: *Ptr to the value
 */

char *_getminenv(const char *name)
{
	char **env = environ;
	char *fe;

	while (*env != NULL)
	{
		fe = *env;
		if (str_cmp(fe, name, _len(name)) == 0)
		{
			return (fe + _len(name) + 1);
		}
		env++;
	}
	return (NULL);
}

/**
 * cmd_parse - To parse the input
 * @cmd: The command to parse
 * @av: The argument
 * Return: void
 */

void cmd_parse(char *cmd, char **av)
{
	char *token;
	int count = 0;

	token = strtok(cmd, " ");
	while (token != NULL)
	{
		av[count++] = token;
		token = strtok(NULL, " ");
	}

	av[count] = NULL;
}

/**
 * _minenv - prints current environment
 * Return: Always 0
 */

int _minenv(void)
{
	char **env = environ;

	if (environ == NULL)
	{
		_OA_printer("Environment not available\n");
		return (-1);
	}
	for (; *env != NULL; env++)
	{
		_puts(*env);
	}
	return (0);
}

/**
 * _strtok - Tokenizes a string.
 * @str: The string to be tokenized.
 * @delimiter: A string containing all possible delimiters.
 * Return: *Ptr to the next token else NULL if no more tokens are found.
 */

char *_strtok(char *str, const char *delimiter)
{
	static char *store_ptr;
	char *token_start;

	if (str != NULL)
		store_ptr = str;
	if (store_ptr == NULL || *store_ptr == '\0')
		return (NULL);

	while (*store_ptr && str_chr(delimiter, *store_ptr))
		store_ptr++;

	if (*store_ptr == '\0')
		return (NULL);
	token_start = store_ptr;

	while (*store_ptr && !str_chr(delimiter, *store_ptr))
		store_ptr++;

	if (*store_ptr == '\0')
	{
		store_ptr = NULL;
		return (token_start);
	}
	*store_ptr++ = '\0';

	return (token_start);
}
