#include "hssh.h"

/**
 * read_input_buffer - buffers of commands
 * @data: parameter
 * @buf: address of buffer
 * @len: address of len
 * Return: readden bytes
 */
ssize_t read_input_buffer(esh_t *data, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);

		r = getline(buf, &len_p, stdin);

		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			data->flag = 1;
			remove_comments(*buf);
			*len = r;
			data->buffer = buf;
		}
	}
	return (r);
}

/**
 * read_line - gets a line
 * @data: parameter
 *
 * Return: read bytes
 */
ssize_t read_line(esh_t *data)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p, *p;

	data->arg = NULL;
	buf_p = &(data->arg);

	_putchar(FLUSH_BUFFER);
	r = read_input_buffer(data, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		handle_chain(data, buf, &j, i, len);
		while (j < len)
		{
			if (detect_chain_delimiter(data, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			data->buffer_type = 0;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * sigintHandler - blocks the  ctrl-C command
 * @sig_num: a signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(FLUSH_BUFFER);
}
