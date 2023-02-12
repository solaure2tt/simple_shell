#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>

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
	char *inst[50];
	pid_t pid;
	int status, __attribute((unused)) n;

	while (1)
	{
		n = _prompt(inst);
		if (n  == -1)
			break;
		pid = fork();
		if (pid == -1)
		{
			perror(av[0]);
			return (1);
		}
		else if (pid == 0)
		{
			n = execve(inst[0], inst, env);
			if (n == -1)
			{
				perror(av[0]);
				return (1);
			}
		}
		else
			wait(&status);
	}
	return (0);
}
