#include "shell.h"

/**
 * str_cmp - Comparing two strings to determine a string length.
 * @seq1: Sequence one.
 * @seq2: Sequence two.
 * @len: The maximum number of characters to compare
 * Return: If the sequences are the equal 0, else a non zero value.
 */

int str_cmp(const char *seq1, const char *seq2, int len)
{
	int j;

	for (j = 0; j < len; j++)
	{
		if (seq1[j] != seq2[j])
			return (seq1[j] - seq2[j]);
		if (seq1[j] == '\0')
			return (0);
	}
	if (j == len)
		return (0);

	return (seq1[j] ? 1 : -1);
}
