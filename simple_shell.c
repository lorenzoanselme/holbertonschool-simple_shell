#include "shell.h"

/**
 * print_prompt - display prompt if interactive
 * @interactive: interactive mode flag
 */
void print_prompt(int interactive)
{
	if (interactive)
		write(STDOUT_FILENO, "$ ", 2);
}

/**
 * read_input - read a line from stdin
 * @line: buffer
 * @len: buffer size
 * @interactive: interactive mode
 *
 * Return: number of chars read or -1 on EOF
 */
ssize_t read_input(char **line, size_t *len, int interactive)
{
	ssize_t nread;

	nread = getline(line, len, stdin);
	if (nread == -1 && interactive)
		write(STDOUT_FILENO, "\n", 1);

	return (nread);
}

/**
 * prepare_command - trim spaces and split command/arg
 * @line: input line
 * @argv: argument array
 *
 * Return: 1 if valid command, 0 otherwise
 */
int prepare_command(char *line, char **argv)
{
	char *cmd;
	char *arg;

	if (!line)
		return (0);

	if (line[strlen(line) - 1] == '\n')
		line[strlen(line) - 1] = '\0';

	cmd = line;
	while (*cmd == ' ' || *cmd == '\t')
		cmd++;

	if (*cmd == '\0')
		return (0);

	arg = strchr(cmd, ' ');
	if (arg)
	{
		*arg = '\0';
		arg++;
		while (*arg == ' ' || *arg == '\t')
			arg++;
		if (*arg == '\0')
			arg = NULL;
	}

	argv[0] = cmd;
	argv[1] = arg;
	argv[2] = NULL;

	return (1);
}

/**
 * execute_command - fork and execute command
 * @argv: argument array
 * @envp: environment
 */
void execute_command(char **argv, char **envp)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
		return;

	if (pid == 0)
	{
		execve(argv[0], argv, envp);
		write(STDERR_FILENO, argv[0], strlen(argv[0]));
		write(STDERR_FILENO, ": not found\n", 12);
		_exit(127);
	}

	waitpid(pid, &status, 0);
}

/**
 * main - UNIX command line interpreter
 * @ac: argument count (unused)
 * @av: argument vector (unused)
 * @envp: environment
 *
 * Return: Always 0
 */
int main(int ac __attribute__((unused)),
	 char **av __attribute__((unused)),
	 char **envp)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int interactive;
	char *argv[3];

	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		print_prompt(interactive);

		nread = read_input(&line, &len, interactive);
		if (nread == -1)
			break;

		if (!prepare_command(line, argv))
			continue;

		execute_command(argv, envp);
	}

	free(line);
	return (0);
}
