#include "minishell.h"

void	pwd(t_data *data, char *params)
{
	char *res;

	if(*params == '\0')
	{
		res = ft_calloc(1000, sizeof(char));
		res = getcwd(res, 1000);
		ft_putstr_fd(res, 1);
		data->res_prev_cmd = res;
		write(1, "\n", 2);
	}
	else
	{
		errno = 7;
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 2);
	}
}

void	cd(char **params_cl)
{
	int n;

	n = length(params_cl);
	if(n == 1)
		chdir(params_cl[0]);
	else
	{
		errno = 7;
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 2);
	}
}
