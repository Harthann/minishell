#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int		check_option(char *command)
{
	while(*command && command)
	{
		if(ft_memcmp(command, "-n", 3) == 0)
			return (0);
		command++;
	}
	return (1);
}

void	display(char *str)
{
/*	char *mem;

	mem = data->res_prev_cmd;
	if (!mem)
		data->res_prev_cmd = ft_strdup(str);
	else
		data->res_prev_cmd = ft_strjoin_free(data->res_prev_cmd, str, 3);*/
	ft_putstr_fd(str, 1);
/*	data->res_prev_cmd = ft_strjoin_free(data->res_prev_cmd, str, 3);
	free(mem);*/
}

void	ft_echo(char **params_cl)
{
	int n;
	int i;

	n = check_option(params_cl[0]);
	i = (n == 0) ? 1 : 0;
	while(params_cl[i])
	{
		display(params_cl[i]);
		if (params_cl[i + 1] != NULL)
			display(" ");
		i++;
	}
	if(n == 1)
		display("\n");
}
