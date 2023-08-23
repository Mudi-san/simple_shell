#include "hssh.h"

/**
 * check_builtin - search for builtin command
 * @data: the return info struct
 * Return: status number for custom builtin
 */
int check_builtin(esh_t *data)
{
	int i, return_status = -1;
	builtin_t builtins[] = {
		{"env", esh_env},
		{"cd", esh_cd},
		{"exit", esh_exit},
		{NULL, NULL}};

	for (i = 0; builtins[i].type; i++)
		if (_strcmp(data->argv[0], builtins[i].type) == 0)
		{
			data->line_count++;
			(return_status) = builtins[i].func(data);
			break;
		}
	return (return_status);
}
