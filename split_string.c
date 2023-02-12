#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * split_str - splits a string
 * Description: function that splits a string
 * @str: string to split
 * @words: words of str
 * Return: number of words
 */

int split_str(char **words, char *str)
{
	int i = 0;
	char *first;

	if (str != NULL)
	{
		first = strtok(str, " ");
		while (first != NULL)
		{
			words[i] = malloc(sizeof(char) * strlen(first));
			strcpy(words[i], first);
			first = strtok(NULL, " ");
			i++;
		}
		words[i] = first;
	}
	return (i);

}
