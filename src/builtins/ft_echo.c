#include "../../include/minishell.h"

void	ft_putstr(char *str)
{
	while(*str)
	{
		write(1, str, 1);
		str++;
	}
}

int		check_option(char *command)
{
	while(*command)
	{
		if(ft_memcmp(command, "-n", 2) == 0)
			return (0);
		command++;
	}
	return (1);
}

void	ft_echo(char *command, char **params_cl, t_data *data)
{
	int n;
	char *mem;
	int i;

	n = check_option(command);
	i = 0;
	while(params_cl[i])
	{
//		ft_putstr(params_cl[i]);
		mem = data->res_prev_cmd;
		data->res_prev_cmd = ft_strjoin(data->res_prev_cmd, params_cl[i]);
		free(mem);
		if (params_cl[i + 1] != NULL)
		{
//			ft_putstr(" ");
			mem = data->res_prev_cmd;
			data->res_prev_cmd = ft_strjoin(data->res_prev_cmd, " ");
			free(mem);
		}
		i++;
	}
	if(n == 1)
	{
//			ft_putstr("\n");
			mem = data->res_prev_cmd;
			data->res_prev_cmd = ft_strjoin(data->res_prev_cmd, "\n");
			free(mem);
	}
}
