#include "hssh.h"

int replace_string(char **old, char *new);
/**
 * detect_chain_delimiter - test if current char in buffer is a chain delimeter
 * @data: parameter struct
 * @buf: char buffer
 * @p: address of current position in buf
 * Return: 1 if chain delimeter or 0
 */
int detect_chain_delimiter(esh_t *data, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		data->buffer_type = 1;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		data->buffer_type = 2;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		data->buffer_type = 3;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * handle_chain - checks if continue chaining based on last status
 * @data: parameter struct
 * @buf: char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 * Return: Void
 */
void handle_chain(esh_t *data, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (data->buffer_type == 2)
	{
		if (data->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (data->buffer_type == 1)
	{
		if (!data->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_vars - replacing vars in tokenized string
 * @data: struct parameter
 * Return: 1 if replaced or 0
 */
int replace_vars(esh_t *data)
{
	int i = 0;
	var_t *node;

	for (i = 0; data->argv[i]; i++)
	{
		if (data->argv[i][0] != '$' || !data->argv[i][1])
			continue;

		if (!_strcmp(data->argv[i], "$?"))
		{
			replace_string(&(data->argv[i]),
					_strdup(convert_number(data->status, 10)));
			continue;
		}
		if (!_strcmp(data->argv[i], "$$"))
		{
			replace_string(&(data->argv[i]), _strdup(convert_number(getpid(), 10)));
			continue;
		}
		node = node_starts_with(data->env, &data->argv[i][1], '=');
		if (node)
		{
			replace_string(&(data->argv[i]), _strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&data->argv[i], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - function for replacing string
 * @old: old string address
 * @new: new string
 * Return: 1 if replaced or 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
