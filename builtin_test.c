#include "include/minishell.h"
#include <stdio.h>
int main ()
{
	t_env_lst	*lst;
//	t_data		*data;
	lst = 0;
//	data = ft_calloc(1, sizeof(t_data));
//	data->res_prev_cmd = NULL;
	ft_addenv(&lst, ft_envnew("USER", "stbaleba"));
	ft_addenv(&lst, ft_envnew("ADD", "bobo"));
	ft_addenv(&lst, ft_envnew("NEW", "form"));

	ft_delenv(&lst, "ADD");
//	data->env_var = lst;
	builtins("Hello_World");
	builtins("Hello World ");
	builtins("Hello\"World\" ");
	builtins("'Hello'World");
	builtins("Hello 'World' \"dddsd\"");
	builtins("Hello$USER");
	builtins("Hello$USER |");
	builtins("Hello$USER|");

}
