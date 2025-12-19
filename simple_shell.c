#include "shell.h"

extern char **environ;

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	int resultFils;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "$ ", 2);
		}

		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (strcmp(&line, "\n") != 0)
		{
			pid = fork();

			if (pid == -1)
			{
				perror("fork");
				free(line);
				exit(EXIT_FAILURE);
			}

			if (pid == 0)
			{
				char *argv[] = {line, NULL};

				if (execv(line, argv) == -1)
				{
					write(STDERR_FILENO, "Error executing command\n", 24);
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				waitpid(pid, &resultFils, 0);
			}
		}
	}

	free(line);
	return (0);
}