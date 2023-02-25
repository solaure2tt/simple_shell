#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
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
	char *pt = "($) ";

	write(STDIN_FILENO, pt, strlen(pt));
	read = getline(&line, &len, f);
	if (read == -1)
	{
		return (0);
	}
	if (read != -1)
	{
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';
		inst[0] = strsep(&line, " ");
		free(line);
		inst[1] = NULL;
	}
	return (read);
}
