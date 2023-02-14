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
	char *all_path_value = get_env_var_value("PATH=", env);
	char all_path_value_copy[200];
	char *path_value = NULL;

	while (1)
	{
		n = _prompt(inst);
		if (n == -1)
			break;
		path_value = locate_file(inst[0],
				strcpy(all_path_value_copy, all_path_value));
		if (path_value == NULL)
		{
			perror(av[0]);
			continue;
		} 
		pid = fork();
		if (pid == -1)
		{
			perror(av[0]);
			return (1);
		}
		else if (pid == 0)
		{
			n = execve(path_value, inst, env);
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
