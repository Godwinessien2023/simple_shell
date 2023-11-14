#include "shell.h"

/**
 * search_cmd - Check if command is executable in PATH.
 * @input: Array of parsed input.
 * Return: 0 on success.
 */

char *search_cmd(char *input)
{
	char *get_path, *total_path, *copy_path;
	char *token;
	size_t total_path_len;

	get_path = _getminenv("PATH");
	copy_path = _sdup(get_path);
	token = _strtok(copy_path, ":");

	while (token != NULL)
	{
		total_path_len = _len(token) + 1 + _len(input) + 1;

		total_path = (char *)malloc(total_path_len);
		if (total_path == NULL)
		{
			perror("Failed to allocate memory");
			exit(EXIT_FAILURE);
		}

		_cpy(total_path, token);
		str_cat(total_path, "/");
		str_cat(total_path, input);
		if (access(total_path, X_OK) == 0)
		{
			free(copy_path);
			return (total_path);
		}

		free(total_path);
		token = _strtok(NULL, ":");
	}
	free(copy_path);
	return (NULL);
}

/**
 * execve_cmd - Execute commands.
 * @total_path: Total path.
 * @argv: Array of total_path
 * Return: -1 on failure.
 */

int execve_cmd(char *total_path, char **argv)
{
	if (execve(total_path, argv, environ) == -1)
	{
		perror("Execve failed");
		exit(EXIT_FAILURE);
	}
	return (-1);
}

/**
 * exec_command - Execute given commands.
 * @total_path: Path to command.
 * @argv: Argument vector of command.
 * @flag: Determine if total_path needs to be freed.
 * Return: Exit status of command or -1 on failure.
 */

int exec_command(char *total_path, char **argv, int flag)
{
	int exec_result, status;
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Fork failed");
		if (flag)
			free(total_path);
		return (-1);
	}
	if (child_pid == 0)
	{
		exec_result = execve_cmd(total_path, argv);
		if (flag)
			free(total_path);
		exit(exec_result);
	}
	else
	{
		if (wait(&status) == -1)
		{
			perror("Wait failed");
			if (flag)
				free(total_path);
			return (-1);
		}
		return (status);
	}
}

/**
 * handle_execute_error - Error Handler
 * @flag: Determine if total_path needs to be freed.
 * @total_path: The full path to the command.
 * @status: The status of the executed command
 */

void handle_execute_error(int flag, char *total_path, int status)
{
	if (flag)
		free(total_path);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		exit(2);
	}
	else if (!WIFEXITED(status))
	{
		perror("Command did not exit correctly");
		exit(2);
	}
}

/**
 * cmd_execute - Executes commands
 * @argv: The array containing the arguments
 * Return: -1 on failure or exit status of the executed command on success
 */

int cmd_execute(char **argv)
{
	char *total_path, *searched_path;
	int status, flag = 0;

	total_path = argv[0];

	if (access(total_path, X_OK) != 0)
	{
		searched_path = search_cmd(argv[0]);
		if (searched_path != NULL)
		{
			total_path = searched_path;
			flag = 1;
		}
		else
		{
			perror("Command not found");
			return (-1);
		}
	}
	status = exec_command(total_path, argv, flag);
	handle_execute_error(flag, total_path, status);

	return (WEXITSTATUS(status));
}
