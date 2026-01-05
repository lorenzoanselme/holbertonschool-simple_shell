#include "shell.h"

static char *g_progname;
static unsigned long g_cmd_count;

/**
 * get_progname - get program name (argv[0])
 * Return: program name or "hsh" if NULL
 */
char *get_progname(void)
{
	if (!g_progname)
		return ("hsh");
	return (g_progname);
}

/**
 * set_progname - set program name
 * @name: argv[0]
 */
void set_progname(char *name)
{
	g_progname = name;
}

/**
 * get_cmd_count - get command counter
 * Return: current command count
 */
unsigned long get_cmd_count(void)
{
	return (g_cmd_count);
}

/**
 * inc_cmd_count - increment command counter
 */
void inc_cmd_count(void)
{
	g_cmd_count++;
}
