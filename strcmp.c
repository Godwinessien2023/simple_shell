#include "shell.h"

/**
 * _sdup - String Duplicator.
 * @source: String obtained.
 * Return: Duplicated string.
 */

char *_sdup(const char *source)
{
	int cp1, cp2;
	char *dp;

	if (source == NULL)
		return (NULL);

	cp1 = 0;
	while (source[cp1] != '\0')
	{
		cp1++;
	}

	dp = (char *)malloc((cp1 + 1) * sizeof(char));
	if (dp == NULL)
	{
		return (NULL);
	}

	cp2 = 0;
	while (cp2 < cp1)
	{
		dp[cp2] = source[cp2];
		cp2++;
	}

	dp[cp2] = '\0';
	return (dp);
}

/**
 * str_chr - Find string Character.
 * @sequence: The string.
 * @ch: The character to find.
 * Return: *Ptr to character in the string.
 */

const char *str_chr(const char *sequence, char ch)
{
	int i = 0;

	while (sequence[i] != '\0')
	{
		if (sequence[i] == ch)
			return (&sequence[i]);
		i++;
	}

	return (NULL);
}

/**
 * str_cat - Concatenates two strings.
 * @to: string1
 * @from: string2
 * Return: *Ptr to resulting string destination.
 */

char *str_cat(char *to, char *from)
{
	int dlen = 0;
	int srclen = 0;
	int j;

	for (j = 0; to[j] != '\0'; j++)
		dlen++;
	for (j = 0; from[j] != '\0'; j++)
		srclen++;
	for (j = 0; j <= srclen; j++)
		to[dlen + j] = from[j];
	return (to);
}
