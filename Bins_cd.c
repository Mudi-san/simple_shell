#include "hssh.h"

/**
 * esh_cd - changes the current directory
 * @data: Structure containing potential arguments.
 *  Return: 0
 */

int esh_cd(esh_t *data)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("getcwd fail\n");
	if (!data->argv[1])
	{
		dir = _getenv(data, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _getenv(data, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(data->argv[1], "-") == 0)
	{
		if (!_getenv(data, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(data, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = _getenv(data, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(data->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(data, "can't cd to ");
		_puts(data->argv[1]), _putchar('\n');
	}

	return (0);
}
/**
 * esh_exit - shell exits
 * @data: Struct containing potential arguments.
 * Return: exits with a given exit status
 */
int esh_exit(esh_t *data)
{
	if (data->argv[1])
	{
		data->err_num = _atoi(data->argv[1]);
		if (data->err_num == -1)
		{
			data->status = 2;
			print_error(data, "Illegal number: ");
			_puts(data->argv[1]);
			_putchar('\n');
			return (1);
		}
		return (-3);
	}
	data->err_num = -1;
	return (-2);
}
