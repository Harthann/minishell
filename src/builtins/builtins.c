#include "../../include/minishell.h"

void builtins(char *command, char *params, t_data *data)
{
//	int i = 0;
//	int j = 0;
	char **params_cl;
	if (params != NULL)
		params_cl = clean_params(params, data->env_var);
/*	while(params_cl[i] != NULL)
	{
		printf("av[%d] : %s\n", i,  params_cl[i]);
		i++;
	}*/
	while(*command)
	{
		if(ft_memcmp(command, "echo", 4) == 0)
				ft_echo(command, params_cl, data);
		else if(ft_memcmp(command, "pwd", 3) == 0)
				pwd(data);
		else if(ft_memcmp(command, "cd", 2) == 0)
				cd(params_cl);

		command++;
	}
//	printf("data_res : %s\n", data->res_prev_cmd);
//	data->res_prev_cmd = NULL;
}
