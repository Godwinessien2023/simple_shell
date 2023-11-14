#include "shell.h"

/**
 * _strcat - Cooncatenates two strings.
 * @to: Destination..
 * @from: Source.
 * Return: *Ptr to destination.
 */

char *_strcat(char *to, const char *from)
{
	int dlen = _len(to);
	int j;

	for (j = 0; from[j] != '\0'; j++)
		to[dlen + j] = from[j];

	to[dlen + j] = '\0';
	return (to);
}

/**
 * _memset - Fills memory with a constant byte.
 * @s: *Ptr to memory.
 * @b: Byte to fill *s
 * @n: Amout of byte
 * Return: (s) - *Ptr to the memory area of S
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
		s[j] = b;
	return (s);
}

/**
 * initialize_info - Initializes info structure.
 * @info: *Ptr to info structure
 */

void initialize_info(info_t *info)
{
	info->env = NULL;
	info->env_size = 0;
	info->env_changed = 0;
	info->env = NULL;
}

/**
 * cleanup_info - Cleans up and deallocates mem asociated with info structure
 * @info: *Ptr to info structure to be cleaned up
 */

void cleanup_info(info_t *info)
{
	while (info->env != NULL)
	{
		list_t *temp = info->env;

		info->env = info->env->next;
		free(temp->str);
		free(temp);
	}
	info->env_size = 0;
	info->env_changed = 0;
}

/**
 * _unsetenv - Remove environment variable
 * @info: Structure containing posible  arguments.
 * @var: the string enviroment variable property to unset.
 * Return: 0 if successful, -1 if the variable doesn't exist
 */

int _unsetenv(info_t *info, const char *var)
{
	size_t var_len = _len(var);
	list_t *prev = NULL;
	list_t *current = info->env;

	if (!var)
		return (-1);
	while (current != NULL)
	{
		char *p = starts_with(current->str, var);

		if (p && *p == '=' && strncmp(current->str, var, var_len) == 0)
		{
			if (prev == NULL)
			{
				info->env = current->next;
			}
			else
			{
				prev->next = current->next;
			}

			free(current->str);
			free(current);
			info->env_size--;
			info->env_changed = 1;
			return (0);
		}

		prev = current;
		current = current->next;
	}

	return (-1);
}
