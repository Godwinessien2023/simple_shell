#ifndef TEST_H
#define TEST_H

#define SPACE 130
#define MAX_INPUT_LENGTH 1024
#define MAX_ENTRY_SIZE 256
#define MAX_ENV_SIZE 100
#define ENV_VAR_VALUE "some_value"
#define ENV_VAR_NAME "MY_ENV_VARIABLE"
#define MY_EOF (-1)

/**
 * struct list_node - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */

typedef struct list_node
{
	char *str;
	int num;
	struct list_node *next;
} list_t;

/**
 * struct pass - contains arguements to pass into a function
 * @env: environment
 * @env_size: size of the environment
 * @env_changed: on if environ was changed
 */

typedef struct pass
{
	list_t *env;
	int env_size;
	int env_changed;
} info_t;
extern char **environ;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

void _puts(char *str);
ssize_t _getline(char **lineptr, size_t *n, int fd);
void initialize_info(info_t *info);
void cleanup_info(info_t *info);
char *_strcat(char *to, const char *from);
const char *str_chr(const char *sequence, char ch);
char *str_cat(char *to, char *from);
char *_sdup(const char *source);
int str_cmp(const char *seq1, const char *seq2, int len);
char *_cpy(char *destination, const char *source);
size_t _len(const char *str);
void _OA_printer(const char *letters);
char *_strtok(char *str, const char *delimiter);
int check_script(const char *file_name);
void is_interactive(void);
int _minenv(void);
void cmd_parse(char *cmd, char **av);
int _setenv(info_t *info, char *var, char *value);
int cmd_execute(char **argv);
int execve_cmd(char *total_path, char **argv);
char *search_cmd(char *input);
char *_getminenv(const char *name);
int _int(char *_string);
void exit_shell(int status);
void handle_execute_error(int flag, char *total_path, int status);
int exec_command(char *total_path, char **argv, int flag);
char *_memset(char *s, char b, unsigned int n);
list_t *add_node_end(list_t **head, const char *str, int num);
char *starts_with(const char *str, const char *prefix);
int _unsetenv(info_t *info, const char *var);
int _putchar(char c);

#endif
