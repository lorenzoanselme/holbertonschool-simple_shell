#include "shell.h"

/**
 * handle_builtins - handle built-in commands
 * @argv: argument array
 * @envp: environment
 * @last_status: pointer to last exit status
 * @line: getline buffer (to free on exit)
 *
 * Return: 1 if a builtin was handled, 0 otherwise
 */
int handle_builtins(char **argv, char **envp, int *last_status, char *line)
{
	if (strcmp(argv[0], "exit") == 0)
	{
		free(line);
		exit(*last_status);
	}

	if (strcmp(argv[0], "env") == 0)
	{
		print_env(envp);
		*last_status = 0;
		return (1);
	}

	return (0);
}
