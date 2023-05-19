#include "main.h"

int _theexit(info_t *info)
{
	int exit;
	char *s = info->argv[1];

	if (info->argv[1])
	{
		exit = atoi(s);
		if (exit <= 255 && exit >= 0)
		{
			info->err_num = exit;
		}else{
			info -> err_num = 13;
		}
	}else
	{
		info->err_num = -1;
	}
	return (-2);
}