#ifndef MAIN_H
#define MAIN_H
int split_str(char **words, char *str, char *sep);
char *get_env_var_value(char *env, char *inst[]);
int _prompt(char *inst[]);
char *locate_file(char *filename, char *path_value);
int exitshell(char *command[]);
int _pidfork(char *a, char *pa, char *in[], char *e[]);
int splitcmdcoma(char *cmd[]);
void _perror(char *shell, char *command);
#endif
