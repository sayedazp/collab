#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <math.h>  
#include <sys/stat.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define RB_SIZE 1024
#define WB_SIZE 1024
#define B_FLUSH -1

extern char **environ;

#define BASE_INFO \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_node;


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
	list_node *env;
	list_node *history;
	list_node *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;


typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;



int __getline(info_t *info, char **lineptr, size_t *n);
void sigintHandler(__attribute__((unused))int sig_num);
int _putchar(char c);
int _eputchar(char c);
char *itoa(long int num, int base, int flags);
char *starts_with(const char *haystack, const char *needle);
void _puts(char *str);

list_node *add_node(list_node **, const char *, int);
list_node *add_node_end(list_node **, const char *, int);
size_t print_list_str(const list_node *);
int delete_node_at_index(list_node **, unsigned int);
void free_list(list_node **);


/*envs*/
int populate_env_list(info_t *info);

/**shell.c**/
int shellin(info_t *info, char **av);
ssize_t get_input(info_t *info);


void set_info(info_t *info, char **av);

int is_delim(char c, char *delim);

char **strtow(char *str, char *d);

void find_cmd(info_t *info);

char *find_path(info_t *info, char *pathstr, char *cmd);

char *_getenv(info_t *info, const char *name);

int is_cmd(info_t *info, char *path);
void fork_cmd(info_t *info);
char *dup_chars(char *pathstr, int start, int stop);

char **list_to_strings(list_node *head);
char **get_environ(info_t *info);

void print_error(info_t *info, char *estr);
void _eputs(char *str);
int _eputchar(char c);

int _theexit(info_t *info);
int find_builtin(info_t *info);

#endif
