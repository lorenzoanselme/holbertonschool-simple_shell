#include "shell.h"

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
			return (my_strdup(cmd));
		return (NULL);
	}

	path = get_path(envp);
	if (!path)
		return (NULL);

	path_copy = my_strdup(path);
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
