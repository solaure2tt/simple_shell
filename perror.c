#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * _perror - exit of the shell
 * Description: display error
 * @shell: d
 * @command: shell command
 * Return: d
 */
void _perror(char *shell, char *command)
{
	char err_msg[200];

	strcat(err_msg, shell);
	strcat(err_msg, ": 1: ");
	strcat(err_msg, command);
	strcat(err_msg, ": not found\n");
	write(STDERR_FILENO, err_msg, strlen(err_msg));
}
