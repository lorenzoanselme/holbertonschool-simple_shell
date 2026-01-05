#include "shell.h"

/**
 * my_strdup - duplicate a string using malloc
 * @s: string to duplicate
 *
 * Return: pointer to duplicated string, or NULL on failure
 */
char *my_strdup(char *s)
{
	char *dup;
	size_t len;

	if (!s)
		return (NULL);

	len = strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);

	memcpy(dup, s, len + 1);
	return (dup);
}
