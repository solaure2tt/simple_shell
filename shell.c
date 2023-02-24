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
	char **inst;
	int i, status, __attribute((unused)) n;
	char *line = NULL;
	size_t len = 0;
	FILE *f = stdin;
	ssize_t read;
	char *pt = "($) ";
	pid_t pid;

	while (1)
	{
		write(STDIN_FILENO, pt, strlen(pt));
		read = getline(&line, &len, f);
		if ( read == -1)
			exit(0);
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';
		inst = malloc(sizeof(char *) * 2);
		inst[0] = strsep(&line, " ");
		inst[1] = NULL;
		pid = fork();
		if (pid == -1)
		{
			perror(av[0]);
			for (i = 0; i < 2; i++)
				free(inst[i]);
			free(inst);
			exit(1);
		}
		else if (pid == 0)
		{
			n = execve(inst[0], inst, env);
			if (n == -1)
			{
				for (i = 0; i < 2; i++)
					free(inst[i]);
				free(inst);
				perror(av[0]);
				exit(1);
			}
		}
		else
			wait(&status);
		for (i = 0 ; i < 2; i++)
			free(inst[i]);
		free(inst);
	}
	exit (0);
}
