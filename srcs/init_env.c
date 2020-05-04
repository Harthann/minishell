#include "minishell.h"

void	init_env(t_data *data, char **env)
{
	while (*env)
	{
		add_env(*env, data);
		env++;
	}
}