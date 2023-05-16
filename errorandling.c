#include "main.h"

void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}


int _eputchar(char c)
{
	static int one;
	static int i;
	static char buf[WB_SIZE];
	char *tmp;
	info_t tmpinf;
	size_t length;

	if (c == B_FLUSH || i >= WB_SIZE) 
	{
		write(2, buf, i);		
		i = 0;
	}
	
	if (c != B_FLUSH)
		buf[i++] = c;
	return (1);
}