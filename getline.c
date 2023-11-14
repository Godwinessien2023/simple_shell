#include "shell.h"

/**
 * _getline - Read lines from file descriptor.
 * @lineptr: *Ptr to *ptr to line-buffer.
 * @n: *Ptr to size of the line-buffer
 * @fd: File descriptor.
 * Return: 0 on success.
 */

ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	char *temp;
	char ch;
	size_t a = 0, b, initial_buffer_size = 128;

	while (*lineptr == NULL || *n == 0)
	{
		*n = initial_buffer_size;
		*lineptr = (char *)malloc(*n);
		if (*lineptr == NULL)
		{
			perror("malloc failed");
			return (-1);
		}
	}
	while (read(fd, &ch, 1) == 1 && ch != '\n')
	{
		(*lineptr)[a++] = ch;
		if (a == *n)
		{
			*n *= 2;
			temp = (char *)malloc(*n);
			if (temp == NULL)
			{
				perror("malloc failed");
				return (-1);
			}
			for (b = 0; b < a; b++)
			{
				temp[b] = (*lineptr)[b];
			}
			free(*lineptr);
			*lineptr = temp;
		}
	}
	while (ch == MY_EOF && a == 0)
	{
		return (-1);
	}
	(*lineptr)[a] = '\0';
	return (a);
}
