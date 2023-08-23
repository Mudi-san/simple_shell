#include "hssh.h"

/**
 * init_esh - initializes esh_t struct
 * @data: struct address
 * @av: argument av
 */
void init_esh(esh_t *data, char **av)
{
	int i = 0;

	data->esh_name = av[0];
	if (data->arg)
	{
		data->argv = _split_str(data->arg, " \t");
		if (!data->argv)
		{
			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = _strdup(data->arg);
				data->argv[1] = NULL;
			}
		}
		for (i = 0; data->argv && data->argv[i]; i++)
			;

		replace_vars(data);
	}
}
/**
 * reset_esh - frees esh_t struct fields
 * @data: struct address
 */
void reset_esh(esh_t *data)
{
	free_strings(data->argv);
	data->argv = NULL;
	data->path = NULL;
	if (!data->buffer)
		free(data->arg);
	if (data->env)
		free_var_list(&(data->env));
	free_strings(data->environ);
	data->environ = NULL;
	safely_free_pointer((void **)data->buffer);
	_putchar(FLUSH_BUFFER);
}
/**
 * prompt - write prompt
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
		_puts("$ ");
	_putchar(FLUSH_BUFFER);
}
