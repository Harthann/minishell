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

void	display(char *str, t_data *data)
{
	char *mem;

	mem = data->res_prev_cmd;
	ft_putstr(str);
	data->res_prev_cmd = ft_strjoin(data->res_prev_cmd, str);
	free(mem);
}

void	ft_echo(char *command, char **params_cl, t_data *data)
{
	int n;
	int i;

	n = check_option(command);
	i = 0;
	while(params_cl[i])
	{
		display(params_cl[i], data);
		if (params_cl[i + 1] != NULL)
			display(" ", data);
		i++;
	}
	if(n == 1)
			display("\n", data);
}
