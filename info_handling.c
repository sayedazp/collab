#include "main.h"

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
    ffree(info->environ);
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
