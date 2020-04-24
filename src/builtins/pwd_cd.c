#include "../../include/minishell.h"

void	pwd(t_data *data)
{
	char *res;

	res = ft_calloc(1000, sizeof(char));
	res = getcwd(res, 1000);
	ft_putstr(res);
	data->res_prev_cmd = res;
}
