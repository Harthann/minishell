#include "../../include/minishell.h"

void builtins(char *command, char *params, t_data *data)
{
//	int i = 0;
//	int j = 0;
	char **params_cl;
	params_cl = clean_params(params, data->env_var);
/*	while(params_cl[i] != NULL)
	{
		printf("av[%d] : %s\n", i,  params_cl[i]);
		i++;
	}*/
	if(ft_memcmp(command, "echo", 4) == 0)
			ft_echo(command, params_cl, data);
//	printf("data_res : %s\n", data->res_prev_cmd);
//	data->res_prev_cmd = NULL;
}
