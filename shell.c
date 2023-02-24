#include "main.h"


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
	char *inst[2];
	pid_t pid;
	int status, __attribute((unused)) n;
	char *command;

	while (1)
	{
		show_prompt("($) ");
		command = read_command();
		if (command == NULL)
			break;
		if(command[0] == '\0')
			continue;

		pid = fork();
		if (pid == -1)
		{
			perror(av[0]);
			free(command_space);
			return (1);
		}
		else if (pid == 0)
		{
			inst[0] = command;
			inst[1] = NULL;
			n = execve(inst[0], inst, env);
			if (n == -1)
			{
				perror(av[0]);
				free(command_space);
				return (1);
			}
			free(command_space);
			return (0);
		}
		else
			wait(&status);
	}
	return (0);
}
