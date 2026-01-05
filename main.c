#include "shell.h"

/**
 * main - UNIX command line interpreter
 * @ac: argument count (unused)
 * @av: argument vector
 * @envp: environment
 *
 * Return: exit status of the last executed command
 */
int main(int ac __attribute__((unused)), char **av, char **envp)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int interactive, last_status = 0;
	char *argv[MAX_ARGS];

	set_progname((av && av[0]) ? av[0] : "hsh");
	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		print_prompt(interactive);
		nread = read_input(&line, &len, interactive);
		if (nread == -1)
			break;

		if (!prepare_command(line, argv))
			continue;

		if (handle_builtins(argv, envp, &last_status, line))
			continue;

		inc_cmd_count();
		last_status = execute_command(argv, envp);
	}

	free(line);
	return (last_status);
}
