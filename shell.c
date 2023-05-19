#include "main.h"

int shellin(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;
	builtin_ret = 0;//sayed

	while (r != -1 && builtin_ret != -2)
	{
		//clear_info(info);
	if (1)//interactive(info))
		{
			if (info->cmd_buf_type == 0)
				_puts("$ ");
		}
		_eputchar(B_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		/*else if (interactive(info))
			_putchar('\n');*/
		//free_info(info, 0);
	}
	//write_history(info);
	//free_info(info, 1);
	/*if (!interactive(info) && info->status)
		exit(info->status);*/
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
    return (1);
}