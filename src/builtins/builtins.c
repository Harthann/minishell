#include "../../include/minishell.h"

void builtins(char *params)
{
	int i = 0;
	char **params_cl;
	params_cl = clean_params(params);
	while(params_cl[i] != NULL)
	{
		printf("av[%d] : %s\n", i,  params_cl[i]);
		i++;
	}
}
