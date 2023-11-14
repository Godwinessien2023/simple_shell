#include "shell.h"

/**
 * _cpy - Copies a string.
 * @destination: Destination to copy to.
 * @source: Source to copy from
 * Return: *Ptr to destination string.
 */

char *_cpy(char *destination, const char *source)
{
	char *destination_start;

	if (source != NULL && destination != NULL)
	{
		destination_start = destination;
		while (*source != '\0')
		{
			*destination = *source;
			destination++;
			source++;
		}
		*destination = '\0';
		return (destination_start);
	}
	return (NULL);
}
