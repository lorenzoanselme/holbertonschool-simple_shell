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
