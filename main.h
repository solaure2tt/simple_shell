#ifndef MAIN
#define MAIN
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
void show_prompt(char *prompt);
char *read_command(char *line);
#endif
