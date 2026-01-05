#include "shell.h"

/**
 * print_env - print current environment variables
 * @envp: environment variables
 */
void print_env(char **envp)
{
	int i = 0;

	while (envp && envp[i])
	{
		write(STDOUT_FILENO, envp[i], strlen(envp[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
