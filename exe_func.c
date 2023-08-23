#include "hssh.h"

int is_executable(char *path);
/**
 * find_path - finds this command in the PATH
 * @path_str: string PATH
 * @command: the command
 * Return: path of command or NULL
 */
char *find_path(char *path_str, char *command)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!path_str)
		return (NULL);
	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (is_executable(command))
			return (command);
	}
	while (1)
	{
		if (!path_str[i] || path_str[i] == ':')
		{
			path = dup_chars(path_str, curr_pos, i);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (is_executable(path))
				return (path);
			if (!path_str[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * execute_command - search for a command in PATH
 * @data: parameter and return struct
 * Return: void
 */
void execute_command(esh_t *data)
{
	char *path = NULL;
	int i, k;
	pid_t child_pid;

	data->path = data->argv[0];
	if (data->flag == 1)
	{
		data->line_count++;
		data->flag = 0;
	}

	for (i = 0, k = 0; data->arg[i]; i++)
		if (!is_delimiter(data->arg[i], " \t\n"))
		k++;
	if (!k)
		return;
	path = find_path(_getenv(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(data->path, data->argv, get_environ(data)) == -1)
		{
			reset_esh(data);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				print_error(data, "Permission denied\n");
		}
	}
}

/**
 * is_executable - find if file is an executable command
 * @path: the path to a file
 * Return: 1 if true, 0 otherwise
 */
int is_executable(char *path)
{
	struct stat st;

	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}

	return (0);
}
