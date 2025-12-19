#include "shell.h"

extern char **environ;

/**
 * print_prompt - display prompt if interactive
 * @interactive: 1 if interactive, 0 otherwise
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
 * Return: number of characters read or -1 on EOF
 */
ssize_t read_input(char **line, size_t *len, int interactive)
{
	ssize_t nread;

	nread = getline(line, len, stdin);
	if (nread == -1)
	{
		if (interactive)
			write(STDOUT_FILENO, "\n", 1);
	}
	return (nread);
}

/**
 * prepare_command - trim spaces and split command/arg
 * @line: input line
 * @argv: argument array
 *
 * Return: 1 if command ready, 0 otherwise
 */
int prepare_command(char *line, char **argv)
{
	char *cmd;
	char *arg;

	if (line == NULL)
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
 */
void execute_command(char **argv)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		execve(argv[0], argv, environ);
		write(STDERR_FILENO, argv[0], strlen(argv[0]));
		write(STDERR_FILENO, ": not found\n", 12);
		_exit(127);
	}

	waitpid(pid, &status, 0);
}

/**
 * main - UNIX command line interpreter
 *
 * Return: Always 0
 */
int main(void)
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

		execute_command(argv);
	}

	free(line);
	return (0);
}
