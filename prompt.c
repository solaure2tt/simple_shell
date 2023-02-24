#include "main.h"
/**
 * show_prompt - other case conversion specifier
 * @prompt: no paremeter to convert
 * Return: nothing
 */
void show_prompt(char *prompt)
{
	char *default_prompt = "($) ";

	if (prompt == NULL)
		write(STDOUT_FILENO, default_prompt, strlen(default_prompt));
	else
	{
		write(STDOUT_FILENO, prompt, strlen(prompt));
	}
}

/**
 * read_command - get the entire command line
 * @line: d
 * Return: the command line
 */
char *read_command(char *line)
{
	FILE *f = stdin;
	size_t len = 0;
	ssize_t read;

	read = getline(&line, &len, f);
	if (read != -1)
	{
		/*
		 * delete spaces before the command
		 */
		while (line[0] == ' ')
		{
			line = line + 1;
			read--;
		}
		/*
		 * delete spaces or \n character after the command
		 */
		while (line[read - 1] == ' ' || line[read - 1] == '\n')
		{
			line[read - 1] = '\0';
			read = read - 1;
		}
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';
		return (line);
	}
	else
		return (NULL);
}
