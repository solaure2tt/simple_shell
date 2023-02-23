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
	char **inst, *path_value, all_path_value_copy[200];
	pid_t pid;
	int status, __attribute((unused)) n, checkexit;
	char *all_path_value = get_env_var_value("PATH=", env);

	while (1)
	{
		inst = malloc(sizeof(char*) * 4);
		if ((_prompt(inst)) == -1)
		{
			free(inst);
			exit(0);
		}
		checkexit = exitshell(inst);
		if (checkexit != -1)
		{
			free(inst);
			exit(checkexit);
		}
		path_value = locate_file(inst[0],
				_strcpy(all_path_value_copy, all_path_value));
		if (path_value == NULL)
		{
			perror(av[0]);
			free(inst);
			continue;
		}
		pid = fork();
		if (pid == -1)
		{
			perror(av[0]);
			free(inst);
			exit (1);
		}
		else if (pid == 0)
		{
			n = execve(path_value, inst, env);
			if (n == -1)
			{
				free(inst);
				perror(av[0]);
				exit (1);
			}
		}
		else
			wait(&status);
		free(inst);
	}
	exit (0);
}
