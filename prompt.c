#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * _prompt - prompt of the shell
 * Description: create a prompt, wait for the user to enter a command
 * @inst: parameters of the command entered
 * Return: number of charcters read on stream
 */
int _prompt(char *inst[])
{
	char *line = NULL;
	size_t len = 0;
	FILE *f = stdin;
	ssize_t read;
	char *pt = "#cisfun$ ";

	write(STDIN_FILENO, pt, strlen(pt));
	read = getline(&line, &len, f);
	if (read != -1)
	{
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';
		split_str(inst, line);
	}
	return (read);
}
