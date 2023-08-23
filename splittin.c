#include "hssh.h"

/**
 * **_split_str - splits a string into words.
 * @ss: input string
 * @meter: the delimeter
 * Return: pointer to an array of strings, or NULL
 */

char **_split_str(char *ss, char *meter)
{
	int e, f, g, q, nowrz = 0;
	char **str;

	if (ss == NULL || ss[0] == 0)
		return (NULL);
	if (meter == NULL)
		meter = " ";
	for (e = 0; ss[e] != '\0'; e++)
		if (!is_delimiter(ss[e], meter) &&
				(is_delimiter(ss[e + 1], meter) || !ss[e + 1]))
			nowrz++;

	if (nowrz == 0)
		return (NULL);
	str = malloc((1 + nowrz) * sizeof(char *));
	if (str == NULL)
		return (NULL);
	for (e = 0, f = 0; f < nowrz; f++)
	{
		while (is_delimiter(ss[e], meter))
			e++;
		g = 0;
		while (!is_delimiter(ss[e + g], meter) && ss[e + g])
			g++;
		str[f] = malloc((g + 1) * sizeof(char));
		if (!str[f])
		{
			for (g = 0; g < f; g++)
				free(str[g]);
			free(str);
			return (NULL);
		}
		for (q = 0; q < g; q++)
			str[f][q] = ss[e++];
		str[f][q] = 0;
	}
	str[f] = NULL;
	return (str);
}

/**
 * is_delimiter - checks if character is a delimeter
 * @ch: the char to check
 * @dlm: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delimiter(char ch, char *dlm)
{
	while (*dlm)
		if (*dlm++ == ch)
			return (1);
	return (0);
}
