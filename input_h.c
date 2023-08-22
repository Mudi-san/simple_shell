#include "hssh.h"

/**
 * get_args - Gets a command from the standard input.
 * @bffln: Buffer to store the command.
 * @exe_rval: The return value of the last exe command.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - Pointer to the stored command.
 */
char *get_args(char *bffln, int *exe_rval)
{
	size_t ignored = 0;
	ssize_t gtl;
	char *prompt = "$ ";

	if (bffln)
		free(bffln);

	gtl = _getline(&bffln, &ignored, STDIN_FILENO);
	if (gtl == -1)
		return (NULL);
	if (gtl == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(bffln, exe_rval));
	}

	bffln[gtl - 1] = '\0';
	variable_replacement(&bffln, exe_rval);
	handle_line(&bffln, gtl);

	return (bffln);
}

/**
 * call_args - Partitions operators from the commands and calls them.
 * @agus: Array of arguments.
 * @frnt: Double pointer to the beginning of args.
 * @exe_rval: The return value of the parent process' last exe command.
 *
 * Return: The return value of the last exe command.
 */
int call_args(char **agus, char **frnt, int *exe_rval)
{
	int rt, index;

	if (!agus[0])
		return (*exe_rval);
	for (index = 0; agus[index]; index++)
	{
		if (_strncmp(agus[index], "||", 2) == 0)
		{
			free(agus[index]);
			agus[index] = NULL;
			agus = replace_aliases(agus);
			rt = run_args(agus, frnt, exe_rval);
			if (*exe_rval != 0)
			{
				agus = &agus[++index];
				index = 0;
			}
			else
			{
				for (index++; agus[index]; index++)
					free(agus[index]);
				return (rt);
			}
		}
		else if (_strncmp(agus[index], "&&", 2) == 0)
		{
			free(agus[index]);
			agus[index] = NULL;
			agus = replace_aliases(agus);
			rt = run_args(agus, frnt, exe_rval);
			if (*exe_rval == 0)
			{
				agus = &agus[++index];
				index = 0;
			}
			else
			{
				for (index++; agus[index]; index++)
					free(agus[index]);
				return (rt);
			}
		}
	}
	agus = replace_aliases(agus);
	rt = run_args(agus, frnt, exe_rval);
	return (rt);
}

/**
 * run_args - Calls the execution of a command.
 * @agus: Array of arguments.
 * @frnt: Double pointer to the beginning of args.
 * @exe_rval: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int run_args(char **agus, char **frnt, int *exe_rval)
{
	int rt, i;
	int (*builtin)(char **agus, char **frnt);

	builtin = get_builtin(agus[0]);

	if (builtin)
	{
		rt = builtin(agus + 1, frnt);
		if (rt != EXIT)
			*exe_rval = rt;
	}
	else
	{
		*exe_rval = execute(agus, frnt);
		rt = *exe_rval;
	}

	hist++;

	for (i = 0; agus[i]; i++)
		free(agus[i]);

	return (rt);
}

/**
 * handle_args - Handle the gets, calls, and runs of the commands.
 * @exe_rval: The return value of the parent process' last exe command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int handle_args(int *exe_rval)
{
	int rt = 0, index;
	char **agus, *bffln = NULL, **frnt;

	bffln = get_args(bffln, exe_rval);
	if (!bffln)
		return (END_OF_FILE);

	agus = _strtok(bffln, " ");
	free(bffln);
	if (!agus)
		return (rt);
	if (check_args(agus) != 0)
	{
		*exe_rval = 2;
		free_args(agus, agus);
		return (*exe_rval);
	}
	frnt = agus;

	for (index = 0; agus[index]; index++)
	{
		if (_strncmp(agus[index], ";", 1) == 0)
		{
			free(agus[index]);
			agus[index] = NULL;
			rt = call_args(agus, frnt, exe_rval);
			agus = &agus[++index];
			index = 0;
		}
	}
	if (agus)
		rt = call_args(agus, frnt, exe_rval);

	free(frnt);
	return (rt);
}

/**
 * check_args - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @agus: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *	   Otherwise - 0.
 */
int check_args(char **agus)
{
	size_t i;
	char *curr, *nxt;

	for (i = 0; agus[i]; i++)
	{
		curr = agus[i];
		if (curr[0] == ';' || curr[0] == '&' || curr[0] == '|')
		{
			if (i == 0 || curr[1] == ';')
				return (create_error(&agus[i], 2));
			nxt = agus[i + 1];
			if (nxt && (nxt[0] == ';' || nxt[0] == '&' || nxt[0] == '|'))
				return (create_error(&agus[i + 1], 2));
		}
	}
	return (0);
}
