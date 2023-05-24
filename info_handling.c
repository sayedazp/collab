#include "main.h"

void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

	}
}


void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

void free_info(info_t *info)
{
	ssfree(info->argv);
	info->argv = NULL;
	info->path = NULL;
}

void ffree_info(info_t *info)
{
    free_info(info);
    if (!info->cmd_buf)
        free(info->arg);
    if (info->env)
        free_list(&(info->env));
    if (info->history)
        free_list(&(info->history));
    if (info->alias)
        free_list(&(info->alias));
    ssfree(info->environ);
        info->environ = NULL;
    bfree(info->cmd_buf);
    /*if (info->readfd > 2)
        close(info->readfd);*/
//	_putchar(B_FLUSH);
}

int bfree(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
