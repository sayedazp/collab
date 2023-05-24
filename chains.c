#include "main.h"

int is_chain(info_t *info, char *buf, size_t j)
{


	
	if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);

	return (1);
}