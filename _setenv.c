#include "shell.h"

/**
 * * _len - Calculate String lenght.
 * @str: The string to be calculated.
 * Return: Length of string.
 */

size_t _len(const char *str)
{
	size_t len = 0;

	while (str && str[len])
		len++;
	return (len);
}

/**
 * _int - Converts strings to integer.
 * @_string: String to be converted.
 * Return: Integer.
 */

int _int(char *_string)
{
	int j = 0;
	unsigned int ui = 0;
	int min = 1;
	int isi = 0;

	while (_string[j])
	{
		if (_string[j] == '-')
		{
			min *= -1;
		}
		while (_string[j] >= '0' && _string[j] <= '9')
		{
			isi = 1;
			ui = (ui * 10) + (_string[j] - '0');
			j++;
		}
		if (isi == 1)
		{
			break;
		}
		j++;
	}
	ui *= min;
	return (ui);
}

/**
 * _setenv - Set environment variable or modify an existing one.
 * @info: Struct containing arguments. Used to maintain.
 *        const func prototype.
 * @var: String env variable.
 * @value: String env var value.
 * Return: Always 0
 */

int _setenv(info_t *info, char *var, char *value)
{
	char buff[MAX_ENTRY_SIZE];
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);
	if (_len(var) + _len(value) + 2 > MAX_ENTRY_SIZE)
	{
		return (1);
	}
	_cpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			_cpy(node->str, buff);
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	if (info->env_size + 1 >= MAX_ENV_SIZE)
	{
		return (1);
	}
	add_node_end(&(info->env), buff, 0);
	info->env_size++;
	info->env_changed = 1;
	return (0);
}

/**
 * starts_with - Check if string starts with prefix
 * @str: The string to check
 * @prefix: The prefix to check against
 * Return: Pointer to the start of prefix in str, or NULL if not found
 */
char *starts_with(const char *str, const char *prefix)
{
	while (*prefix)
	{
		if (*prefix != *str)
			return (NULL);
		prefix++;
		str++;
	}
	return ((char *)str);
}

/**
 * add_node_end - Add node to end of list.
 * @head: *Ptr to *Ptr to head node
 * @str: str field of node
 * @num: node index used by history
 * Return: size of list
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = (list_t *)malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _sdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}
