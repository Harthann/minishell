#include "minishell.h"

void builtins(char *command, char *params, t_data *data)
{
	char **params_cl;
	int	length;

	length = ft_strlen(command);
	if (params != NULL)
		params_cl = clean_params(params, data->env_var, data);
	if(ft_memcmp(command, "echo", length) == 0)
		ft_echo(command, params_cl, data);
	else if(ft_memcmp(command, "pwd", length) == 0)
		pwd(data);
	else if(ft_memcmp(command, "cd", length) == 0)
		cd(params_cl);
	else if(ft_memcmp(command, "env", length) == 0 ||
	(ft_memcmp(command, "export", length) == 0 && *params == '\0'))
			env_list(data);
	else if(ft_memcmp(command, "export", length) == 0)
		add_env(params_cl[0], data);
	else if(ft_memcmp(command, "unset", length) == 0)
		ft_delenv(&(data->env_var), params_cl[0]);
	else if(ft_memcmp(command, "exit", length) == 0)
		ft_free(data, params_cl);
	else
		ft_exec(command, params, data);
}
