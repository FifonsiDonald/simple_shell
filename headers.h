#ifndef HEADERS_H 
#define HEADERS_H 

#define WRITE_BUFF_SIZE 1024
#define BUFF_FLUSH '\n'

#include <stdint.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/wait.h> 

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
int _strlen(const char *);
int _strcmp(const char *,const char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

void env();
void run_env(char **av);

char *_strtok(char *str,const char *delim);
ssize_t _getline(char **lineptr, size_t *n, int fd);
size_t _strcspn(const char *str, const char *chars);

void parse_cmds(char **av);
/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	char *env;
	char *history;
	char *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

char *find_path(char *pathstr, char *cmd);
void cmdexec(char **av);
char *get_path(char *cmd);
#endif
