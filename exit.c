#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * exitshell - exit of the shell
 * Description: function to exit from the shell
 * @command: shell command
 * Return: status exit
 */
int exitshell(char *command[])
{
	char *search;

	search = strstr(command[0], "exit");
	if (search != NULL)
	{
		if (command[1] != NULL)
			return (atoi(command[1]));
		else
			return (0);
	}
	return (-1);
}
