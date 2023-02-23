#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * split_str - splits a string
 * Description: function that splits a string
 * @str: string to split
 * @words: words of str
 * @sep: the separator string
 * Return: number of words
 */

int split_str(char **words, char *str, char *sep)
{
	int i = 0;
	char *first;

	if (str != NULL)
	{
		first = strtok(str, sep);
		while (first != NULL)
		{
			if (words[i] != NULL)
				words[i] = NULL;
			words[i] = malloc(sizeof(char) * strlen(first));
			strcpy(words[i], first);
			first = strtok(NULL, sep);
			i++;
		}
		words[i] = first;
	}
	return (i);

}
