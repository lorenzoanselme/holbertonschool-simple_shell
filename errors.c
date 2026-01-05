#include "shell.h"

/**
 * print_not_found - print formatted "not found" error
 * format: <progname>: <count>: <cmd>: not found
 * @cmd: command name
 */
void print_not_found(char *cmd)
{
	char buf[32], tmp[32];
	int n = 0, t = 0;
	unsigned long x = get_cmd_count();
	char *prog = get_progname();

	write(STDERR_FILENO, prog, strlen(prog));
	write(STDERR_FILENO, ": ", 2);

	if (x == 0)
		buf[n++] = '0';
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
