#include "main.h"
#include <unistd.h>

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if 0
		r = getline(buf, &len_p, stdin);
#else
		r = __getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			//remove_comments(*buf);sayed
			//build_history_list(info, *buf, info->histcount++);sayed
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

int __getline(info_t *info, char **lineptr, size_t *n)
{
    int count = 0, fd, size_realloc = RB_SIZE;
	ssize_t r = 0;
	int loop = 0;
    char *buf = NULL;
	char text[RB_SIZE];
	char x ;


	do {
		if(loop == 0){
			buf = malloc(size_realloc * sizeof(char));
		}
		else
        {
			if (buf [(RB_SIZE * loop) - 1] == '\n')
			{
				buf[count + r ] = '\0';
				break;
			}
			else if(r == RB_SIZE)
			{
				size_realloc += RB_SIZE;
				buf = realloc(buf, size_realloc * sizeof(char));
				count += RB_SIZE;
			}
        }

		if (!buf) /* ALLOC FAILURE! */
			return (buf ? free(buf), -1 : -1);
		r = read(info->readfd, &buf[count], RB_SIZE);

		buf[count + r] = '\0';
		if (r == -1 || r == 0)
		{
			free(buf);
			return (-1);
		}
		loop++;
	} while (r == RB_SIZE);
	*lineptr = buf;
	*n = count + RB_SIZE;
	return (count + r);
}

ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(B_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		//sayedcheck_chain(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			/*if (is_chain(info, buf, &j))
				break;sayed*/
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = 0; //CMD_NORM; sayed
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

void sigintHandler(__attribute__((unused))int sig_num)
{
	puts("\n");
	puts("$ ");
	_putchar(B_FLUSH);
}

void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((/*interactive(info) ||sayed*/ _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			//print_error(info, "not found\n");
		}
	}
}


void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			//sayedfree_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			/*if (info->status == 126)
				*///print_error(info, "Permission denied\n");
		}
	}
}
