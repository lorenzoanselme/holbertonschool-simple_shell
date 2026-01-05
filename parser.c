#include "shell.h"

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

	if (!line || line[0] == '\n')
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
