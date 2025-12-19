#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

/**
 * print_prompt - display the prompt if interactive
 * @interactive: 1 if stdin is a terminal, 0 otherwise
 */
static void print_prompt(int interactive)
{
	if (interactive)
		(void)write(STDOUT_FILENO, "$ ", 2);
}

/**
 * strip_newline - replace trailing '\n' by '\0'
 * @s: input string
 */
static void strip_newline(char *s)
{
	size_t len;

	if (s == NULL)
		return;

	len = strlen(s);
	if (len > 0 && s[len - 1] == '\n')
		s[len - 1] = '\0';
}

/**
 * trim_spaces - remove leading and trailing spaces/tabs
 * @line: input string
 *
 * Return: pointer to trimmed string, or NULL if empty
 */
static char *trim_spaces(char *line)
{
	char *start;
	char *end;

	if (line == NULL)
		return (NULL);

	start = line;
	while (*start == ' ' || *start == '\t')
		start++;

	if (*start == '\0')
		return (NULL);

	end = start + strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t'))
	{
		*end = '\0';
		end--;
	}

	return (start);
}

/**
 * print_not_found - print error message
 * @shell_name: name of shell
 * @cmd: command
 */
static void print_not_found(const char *shell_name, const char *cmd)
{
	if (shell_name && *shell_name)
	{
		(void)write(STDERR_FILENO, shell_name, strlen(shell_name));
		(void)write(STDERR_FILENO, ": ", 2);
	}
	(void)write(STDERR_FILENO, cmd, strlen(cmd));
	(void)write(STDERR_FILENO, ": not found\n", 12);
}

/**
 * main - simple shell 0.1
 * @ac: argument count (unused)
 * @av: argument vector
 * @envp: environment
 *
 * Return: 0
 */
int main(int ac __attribute__((unused)), char **av, char **envp)
{
	char *line = NULL;
	size_t cap = 0;
	ssize_t nread;
	int interactive;
	pid_t pid;
	int status;
	char *argv_exec[2];
	char *cmd;

	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		print_prompt(interactive);

		nread = getline(&line, &cap, stdin);
		if (nread == -1)
		{
			if (interactive)
				(void)write(STDOUT_FILENO, "\n", 1);
			break;
		}

		strip_newline(line);
		cmd = trim_spaces(line);
		if (cmd == NULL)
			continue;

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}

		if (pid == 0)
		{
			argv_exec[0] = cmd;
			argv_exec[1] = NULL;

			execve(cmd, argv_exec, envp);

			if (errno == ENOENT || errno == EACCES)
				print_not_found(av[0], line);
			else
				perror("execve");

			_exit(127);
		}

		(void)waitpid(pid, &status, 0);
	}

	free(line);
	return (0);
}
