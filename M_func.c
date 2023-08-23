#include "hssh.h"

/**
 * main - shell entry point
 * @ac: arg c
 * @av: arg v
 *
 * Return: 0 if success, 1 if error
 */
int main(__attribute__((unused)) int ac, char **av)
{
	esh_t data[] = {{NULL, NULL, 0, NULL, NULL, NULL, 0, 0, 0, NULL, NULL, 0}};
	ssize_t r = 0;
	int builtin_ret = 0;
	var_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	data->env = node;

	while (r != -1 && builtin_ret != -2)
	{
		prompt();
		r = read_line(data);
		if (r != -1)
		{
			init_esh(data, av);
			builtin_ret = check_builtin(data);
			if (builtin_ret == -1)
				execute_command(data);
		}
		free_strings(data->argv);
		data->argv = NULL;
		data->path = NULL;
	}
	reset_esh(data);
	if (!isatty(STDIN_FILENO) && data->status)
		exit(data->status);
	if (builtin_ret == -2)
	{
		if (data->err_num == -1)
			exit(data->status);
		exit(data->err_num);
	}
	return (EXIT_SUCCESS);
}
