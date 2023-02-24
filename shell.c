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
int _pidfork1(char *av0, char **in, char **e)
{
	pid_t pid;
	int n, status, i;

	pid = fork();
	if (pid == -1)
	{
		perror(av0);
		for (i = 0; i < 2; i++)
			free(in[i]);
		free(in);
		return (1);
	}
	else if (pid == 0)
	{
		n = execve(in[0], in, e);
		if (n == -1)
		{
			for (i = 0; i < 2; i++)
				free(in[i]);
			free(in);
			perror(av0);
			return (1);
		}
	}
	else
		wait(&status);
	for (i = 0 ; i < 2; i++)
		free(in[i]);
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
	char **inst = NULL;
	int pi, __attribute((unused)) n;

	while (1)
	{
		inst = malloc(sizeof(char*) * 2);
		n = _prompt(inst);
		if (  n == 0)
		{
			free(inst);
			exit(0);
		}
		if ( n == -1)
		{
			free(inst);
			return (1);
		}
		pi = _pidfork1(av[0], inst, env);
		if (pi == 1)
			exit (1);
	}
	exit (0);
}
