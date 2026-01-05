#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_ARGS 64

char *my_strdup(char *s);

char *get_progname(void);
void set_progname(char *name);
unsigned long get_cmd_count(void);
void inc_cmd_count(void);

void print_prompt(int interactive);
ssize_t read_input(char **line, size_t *len, int interactive);
int prepare_command(char *line, char **argv);
char *get_path(char **envp);
char *find_command(char *cmd, char **envp);
int execute_command(char **argv, char **envp);

int handle_builtins(char **argv, char **envp, int *last_status, char *line);
void print_env(char **envp);

void print_not_found(char *cmd);

#endif /* SHELL_H */
