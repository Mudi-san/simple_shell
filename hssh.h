#ifndef _HSSH_H_
#define _HSSH_H_

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

extern char **environ;

char *name;

int hist;

/**
 * struct list_s - New struct type defining a linked list.
 * @dir: Directory path.
 * @next: Pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - New struct type defining builtin commands.
 * @name: Name of the builtin command.
 * @f: Function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - New struct defining aliases.
 * @name: Name of the alias.
 * @value: Value of the alias.
 * @next: Pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

alias_t *aliases;

int shellby_alias(char **args, char __attribute__((__unused__)) **front);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);
char **replace_aliases(char **args);

int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);

int (*get_builtin(char *command))(char **args, char **front);
int shellby_exit(char **args, char **front);
int shellby_cd(char **args, char __attribute__((__unused__)) **front);
int shellby_help(char **args, char __attribute__((__unused__)) **front);

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);

void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

int num_len(int num);
char *_itoa(int num);
int create_error(char **args, int err);

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

void free_args(char **agus, char **frnt);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void variable_replacement(char **bffln, int *exe_rval);

void handle_line(char **bffln, ssize_t rl);
ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);

char *get_args(char *bffln, int *exe_rval);
int call_args(char **agus, char **frnt, int *exe_rval);
int run_args(char **agus, char **frnt, int *exe_rval);
int handle_args(int *exe_rval);
int check_args(char **agus);

alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);

char *error_126(char **args);
char *error_127(char **args);

int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);

char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);

int cant_open(char *file_path);
int proc_file_commands(char *file_path, int *exe_ret);

int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);

char *get_location(char *command);
char *fill_path_dir(char *path);
list_t *get_path_dir(char *path);

void sig_handler(int sig);
int execute(char **args, char **front);
#endif
