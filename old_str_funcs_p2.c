#include "hssh.h"

/**
 * _strchr - search a character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 * Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

/**
 * dup_chars - duplicates characters
 * @path_str: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *path_str, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (path_str[i] != ':')
			buf[k++] = path_str[i];
	buf[k] = 0;
	return (buf);
}

/**
 * _strcmp - performs lexicographic comparison of two strange.
 * @first: the first strange
 * @second: the second strange
 * Return: negative if first < second,
 *		positive if first > second, zero if first == second
 */
int _strcmp(char *first, char *second)
{
	while (*first && *second)
	{
		if (*first != *second)
			return (*first - *second);
		first++;
		second++;
	}
	if (*first == *second)
		return (0);
	else
		return (*first < *second ? -1 : 1);
}
