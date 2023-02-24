#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
/**
 * _pidfork1 - new process
 * Description: create a new process
 * @av0: name of program
 * @p: path
 * @in: instructions
 * @e: environment
 * Return: number
 */
int _pidfork1(char *av0, char *p, char **in, char **e)
{
	pid_t pid;
	int n, status;

	pid = fork();
	if (pid == -1)
	{
		perror(av0);
		free(in);
		return (1);
	}
	else if (pid == 0)
	{
		n = execve(p, in, e);
		if (n == -1)
		{
			free(in);
			perror(av0);
			return (1);
		}
	}
	else
		wait(&status);
	free(in);
	return (0);
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
	char **inst, *path_value, all_path_value_copy[200];
	int pi, __attribute((unused)) n;
	char *all_path_value = get_env_var_value("PATH=", env);

	while (1)
	{
		inst = malloc(sizeof(char *) * 4);
		if ((_prompt(inst)) == -1)
		{
			free(inst);
			exit(0);
		}
		path_value = locate_file(inst[0],
				_strcpy(all_path_value_copy, all_path_value));
		if (path_value == NULL)
		{
			perror(av[0]);
			free(inst);
			continue;
		}
		pi = _pidfork1(av[0], path_value, inst, env);
		if (pi == 1)
			exit(1);
	}
	exit(0);
}
