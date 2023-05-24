#include "main.h"

/**
 * main - entry point
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] =  BASE_INFO  ;

	populate_env_list(info);
	shellin(info, av);
	return (EXIT_SUCCESS);
}