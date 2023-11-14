#include "shell.h"

/**
 * exit_shell - Exits the shell.
 * @status: The integer code to exit the shell with
 * Return: void
 */

void exit_shell(int status)
{
	exit(status);
}

/**
 * is_interactive - To run the shell in interactive mode.
 * Return: void
 */

void is_interactive(void)
{
	char *sh = NULL;
	char *cmd_argv[MAX_INPUT_LENGTH];
	int exit_status;
	ssize_t byte_read;
	size_t b;

	while (1)
	{
		_OA_printer("Cisfun $ ");
		byte_read = getline(&sh, &b, stdin);
		if (byte_read == -1)
			free(sh), exit(0);
		if (sh[byte_read - 1] == '\n')
			sh[byte_read - 1] = '\0';
		cmd_parse(sh, cmd_argv);
		if (cmd_argv[0] != NULL)
		{
			if (str_cmp(cmd_argv[0], "exit", _len("exit")) == 0)
			{
				if (cmd_argv[1] != NULL)
				{
					exit_status = _int(cmd_argv[1]);
					free(sh), exit_shell(exit_status);
				}
				else
					free(sh), exit_shell(0);
			}
			else if (str_cmp(cmd_argv[0], "env", _len("env")) == 0)
				_minenv();
			else
			{
				exit_status = cmd_execute(cmd_argv);
				if (exit_status == -1)
					perror("Command exec failed");
			}
		}
	}
	free(sh);
}

/**
 * check_script - Checks script.
 * @file_name: Script Name.
 * Return: The executable script.
 */

int check_script(const char *file_name)
{
	char line[MAX_INPUT_LENGTH];
	char *cmd_argv[MAX_INPUT_LENGTH];
	ssize_t byte_read;
	int script, exit_status = 0;

	script = open(file_name, O_RDONLY);
	if (script == -1)
	{
		perror("Error opening script");
		return (-1);
	}

	while ((byte_read = read(script, line, sizeof(line))) > 0)
	{
		line[byte_read] = '\0';

		cmd_parse(line, cmd_argv);
		if (cmd_argv[0] != NULL)
		{
			exit_status = cmd_execute(cmd_argv);

			if (exit_status == -1)
			{
				perror("Command exec failed");
			}
		}
	}

	close(script);
	return (exit_status);
}

/**
 * main - Source-code.
 * @argc: Argument Count.
 * @argv: The array of argument vector.
 * Return: 0 on success.
 */

int main(int argc, char *argv[])
{
	const char *script;

	if (argc > 1)
	{
		script = argv[1];
		return (check_script(script));
	}
	else
		is_interactive();
	return (0);
}
