#include "include/minishell.h"
#include <stdio.h>
int main ()
{
	t_env_lst	*lst;
	t_data		*data;
	lst = 0;
	data = ft_calloc(1, sizeof(t_data));
	data->res_prev_cmd = NULL;
	ft_addenv(&lst, ft_envnew("USER", "stbaleba"));
	ft_addenv(&lst, ft_envnew("ADD", "bobo"));
	ft_addenv(&lst, ft_envnew("NEW", "form"));

	ft_delenv(&lst, "ADD");
	data->env_var = lst;
	while (data->env_var)
	{
		printf("name : %s\n", data->env_var->name);
		printf("value : %s\n", data->env_var->value);
		data->env_var = data->env_var->next;
	}
}
