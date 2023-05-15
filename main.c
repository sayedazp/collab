#include "main.h"


int main(int ac, char **av)
{
	info_t info[] =  BASE_INFO  ;


	populate_env_list(info);
	//read_history(info);
	shellin(info, av);
	return (EXIT_SUCCESS);
}