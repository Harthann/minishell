#include "minishell.h"

void	pwd(t_data *data)
{
	char *res;

	res = ft_calloc(1000, sizeof(char));
	res = getcwd(res, 1000);
	ft_putstr_fd(res, 1);
	data->res_prev_cmd = res;
}

void	cd(char **params_cl)
{
	chdir(params_cl[0]);
}
