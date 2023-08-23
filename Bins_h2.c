#include "hssh.h"

/**
 * help_env - Displays information on the shellby builtin command 'env'.
 */
void help_env(void)
{
	char *msg = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_setenv - Displays information on the shellby builtin command 'setenv'.
 */
void help_setenv(void)
{
	char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_unsetenv - Displays information on the shellby builtin command
 * 'unsetenv'.
 */
void help_unsetenv(void)
{
	char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "message to stderr.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_history - Displays information on the shellby builtin command 'history'.
 */
void help_history(void)
{
	char *msg = "history: history\n\tDisplay or manipulate the history list.";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "\n\n\n\tDisplay the history list with line numbers, prefixing each modified";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "\n\tentery with a `*'.  An argument of N lists only the last N entries.";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "\n\n\n\tExit Status:";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "\n\tReturns success unless an invalid option is given or an error occurs.";
	write(STDOUT_FILENO, msg, _strlen(msg));
}
