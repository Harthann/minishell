#include "../../include/minishell.h"

void	free_lst(t_env_lst **alst)
{
	t_env_lst *lst;
	t_env_lst *mem;

	lst = *alst;
	while(lst)
	{
		free(lst->name);
		free(lst->value);
		mem = lst;
		lst = lst->next;
		free(mem);
	}
	free(alst);
}


void	ft_free(t_data *data, char **params_cl)
{
	int i;

	i = 0;

	while(params_cl[i])
	{
		free(params_cl[i]);
		i++;
	}
	free(params_cl);
	free(data->res_prev_cmd);
	free_lst(&(data->env_var));
	free(data);
	exit(0);
}
