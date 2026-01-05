#include "shell.h"

/**
 * execute_command - fork and execute command
 * @argv: argument array
 * @envp: environment
 *
 * Return: exit status of the executed command
 */
int execute_command(char **argv, char **envp)
{
	pid_t pid;
	int status;
	char *cmd_path;

	cmd_path = find_command(argv[0], envp);
	if (!cmd_path)
	{
		print_not_found(argv[0]);
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		free(cmd_path);
		return (1);
	}

	if (pid == 0)
	{
		execve(cmd_path, argv, envp);
		_exit(127);
	}

	waitpid(pid, &status, 0);
	free(cmd_path);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (1);
}
