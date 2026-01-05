#include "shell.h"

static char *g_progname;
static unsigned long g_cmd_count = 0;

/**
 * print_not_found - print formatted "not found" error
 * format: <progname>: <count>: <cmd>: not found
 * @cmd: command name
 */
void print_not_found(char *cmd)
{
	char buf[32];
	char tmp[32];
	int n = 0, t = 0;
	unsigned long x = g_cmd_count;

	if (!g_progname)
		g_progname = "hsh";

	write(STDERR_FILENO, g_progname, strlen(g_progname));
	write(STDERR_FILENO, ": ", 2);

	if (x == 0)
	{
		buf[n++] = '0';
	}
	else
	{
		while (x > 0)
		{
			tmp[t++] = '0' + (x % 10);
			x /= 10;
		}
		while (t > 0)
			buf[n++] = tmp[--t];
	}
	write(STDERR_FILENO, buf, n);

	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmd, strlen(cmd));
	write(STDERR_FILENO, ": not found\n", 12);
}

/**
 * get_path - retrieve PATH from environment
 * @envp: environment variables
 * Return: PATH string or NULL if not found
 */
char *get_path(char **envp)
{
	int i = 0;

	if (!envp)
		return (NULL);

	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

/**
 * find_command - find command in PATH
 * @cmd: command name
 * @envp: environment
 *
 * Return: full path or NULL
 */
char *find_command(char *cmd, char **envp)
{
	char *path, *path_copy, *dir, *full_path;
	struct stat st;

	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (stat(cmd, &st) == 0)
			return (strdup(cmd));
		return (NULL);
	}

	path = get_path(envp);
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(cmd) + 2);
		if (!full_path)
			break;

		sprintf(full_path, "%s/%s", dir, cmd);

		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

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
 * prepare_command - split line into arguments
 * @line: input line
 * @argv: argument array
 *
 * Return: 1 if valid command, 0 otherwise
 */
int prepare_command(char *line, char **argv)
{
	int argc = 0;
	char *token;

	if (!line)
		return (0);

	if (line[0] == '\n')
		return (0);

	if (line[strlen(line) - 1] == '\n')
		line[strlen(line) - 1] = '\0';

	token = strtok(line, " \t");
	while (token && argc < (MAX_ARGS - 1))
	{
		argv[argc++] = token;
		token = strtok(NULL, " \t");
	}
	argv[argc] = NULL;

	return (argc > 0);
}

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

/**
 * main - UNIX command line interpreter
 * @ac: argument count (unused)
 * @av: argument vector (unused)
 * @envp: environment
 *
 * Return: exit status of the last executed command
 */
int main(int ac __attribute__((unused)),
		 char **av __attribute__((unused)),
		 char **envp)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int interactive;
	char *argv[MAX_ARGS];
	int last_status = 0;

	g_progname = (av && av[0]) ? av[0] : "hsh";
	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		print_prompt(interactive);

		nread = read_input(&line, &len, interactive);
		if (nread == -1)
			break;

		if (!prepare_command(line, argv))
			continue;

		g_cmd_count++;

		last_status = execute_command(argv, envp);
	}

	free(line);
	return (last_status);
}
