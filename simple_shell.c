#include "shell.h"

/**
 * main - UNIX command line interpreter
 *
 * Return: Always 0
 */

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	int resultFils;
	char *argv[2];
	char *envp[1];

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free(line);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			argv[0] = line;
			argv[1] = NULL;
			envp[0] = NULL;

			if (execve(line, argv, envp) == -1)
			{
				write(STDERR_FILENO, "No such file or directory\n", 28);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			waitpid(pid, &resultFils, 0);
		}
	}
	free(line);
	return (0);
}
