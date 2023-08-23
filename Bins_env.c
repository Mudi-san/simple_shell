#include "hssh.h"

/**
 * esh_env - prints current environment
 * @data: Structure containing potential arguments.
 * Return: 0
 */
int esh_env(esh_t *data)
{
	var_t *h = data->env;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
	}

	return (0);
}

/**
 * _getenv - gets value of environ variable
 * @data: Structure containing arguments.
 * @name: env name
 *
 * Return: value
 */
char *_getenv(esh_t *data, const char *name)
{
	var_t *node = data->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}

	return (NULL);
}

/**
 * get_environ - returns string array copy of environ
 * @data: Structure containing potential arguments.
 * Return: 0
 */
char **get_environ(esh_t *data)
{
	if (!data->environ)
		data->environ = list_to_strings(data->env);

	return (data->environ);
}
