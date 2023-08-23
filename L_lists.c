#include "hssh.h"

/**
 * add_node_end - adds a node to end of list
 * @head: address head node
 * @str: str of  node
 * @num: node index for  history
 *
 * Return: list size
 */
var_t *add_node_end(var_t **head, const char *str, int num)
{
	unsigned int i;
	char *s;
	var_t *new_node, *node;
	unsigned int n = sizeof(var_t);

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(var_t));
	if (!new_node)
		return (NULL);

	s = (void *)new_node;
	for (i = 0; i < n; i++)
		s[i] = 0;

	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{

		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * list_len - find length of linked list
 * @h: first node pointer
 *
 * Return: size of list
 */
size_t list_len(const var_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - returns array of strings of the list->str
 * @head: first node pointer
 *
 * Return: array of strings
 */
char **list_to_strings(var_t *head)
{
	var_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * node_starts_with - returns node starts with prefix
 * @node: list head pointer
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
var_t *node_starts_with(var_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
