#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * splitcmdcoma - split a command
 * Description: split a command by using the separator ;
 * @cmd: list of command to split
 * Return: number of character of the command readed
 */
int splitcmdcoma(char *cmd[])
{
	char *line = NULL;
	size_t len = 0;
	FILE *f = stdin;
	ssize_t read;
	int x;
	char *pt = "($)";

	write(STDIN_FILENO, pt, strlen(pt));
	read = getline(&line, &len, f);
	if (read == -1)
		return (read);
	if (read != -1)
	{
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';
		x =  split_str(cmd, line, ";");
	}
	return (x);
}
/**
 * _pidfork - create a new process
 * Description: create an instance of an executing program
 * @a: name of the program
 * @pa: path
 * @in: command
 * @e: environment
 * Return: 1 or -1
 */
int _pidfork(char *a, char *pa, char *in[], char *e[])
{
	int n = 0;
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror(a);
		return (1);
	}
	else if (pid == 0)
	{
		n = execve(pa, in, e);
		if (n == -1)
		{
			perror(a);
			fflush(stdout);
			return (1);
		}
	}
	return (-1);
}
/**
 * main - entry
 * Description: create a basic shell
 * @ac: number of parameters
 * @av: list of arguments
 * @env: environment of execution
 * Return: 0 on success or 1 if not
 */
int main(int __attribute((unused)) ac, char *av[], char *env[])
{
	char *inst[100], *inst1[200], *path_value, all_path_value_copy[200];
	int  status, __attribute((unused)) n, pi,  checkexit, nbc, i = 0;
	char *all_path_value = get_env_var_value("PATH=", env);

	while (1)
	{

		nbc = splitcmdcoma(inst1);
		i = 0;
		if (nbc == -1)
			exit(0);
		while (i < nbc)
		{
			split_str(inst, inst1[i], " ");
			checkexit = exitshell(inst);
			if (checkexit != -1)
			{
				exit(checkexit);
			}
			path_value = locate_file(inst[0],
				strcpy(all_path_value_copy, all_path_value));
			if (path_value == NULL)
			{
				perror(av[0]);
			}
			else
			{
				pi = _pidfork(av[0], path_value, inst, env);
				if (pi == 1)
					return (pi);
				wait(&status);
			}
			i++;
		}
	}
	return (0);
}
