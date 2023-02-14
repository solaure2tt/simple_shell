#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * get_env_var_value - find if it exist the vaule of the env
 * variable given in parameter
 * @inst: list of all enviroment variable
 * @env: the enviraoment variable to look for
 * Return: the value of the given environment variable
 * or NULL if not found
 */
char *get_env_var_value(char *env, char *inst[])
{
	char *ptr;
	int i = 0;

	if (env == NULL)
		return (NULL);
	while (inst[i] != NULL)
	{
		ptr = inst[i];
		if (strstr(ptr, env) == ptr)
			return (ptr + 5);
		i = i + 1;
	}
	return (NULL);
}

/**
 * locate_file - look the ocation of a file
 * @filename: the filename to find,
 * @path_value: value of PATH eveironment variable
 * Return: the location of the file or NULL if not found
 */
char *locate_file(char *filename, char *path_value)
{
	struct stat st;
	int i = 0;
	char *dest[200];

	if (stat(filename, &st) == 0)
		return (filename);
	if (filename == NULL || path_value == NULL)
		return (NULL);
	if (split_str(dest, path_value, ":") == 0)
		return (NULL);
	while (dest[i] != NULL)
	{
		strcat(dest[i], "/");
		strcat(dest[i], filename);
		if (stat(dest[i], &st) == 0)
			return (dest[i]);
		i = i + 1;
	}
	return (NULL);
}

