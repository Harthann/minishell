#include "../../include/minishell.h"

void builtins(char *command, char *params, t_data *data)
{
	char **params_cl;
	char *mem;

	mem = ft_strjoin(command, " ");
	if (params != NULL)
		params_cl = clean_params(params, data->env_var, data);
//	 while(*command)
//	 {
//		 printf("%s\n", command);
		if(ft_memcmp(command, "echo", 4) == 0)
			ft_echo(command, params_cl, data);
		else if(ft_memcmp(command, "pwd", 3) == 0)
			pwd(data);
		else if(ft_memcmp(command, "cd", 2) == 0)
			cd(params_cl);
		else if(ft_memcmp(command, "env", 3) == 0)
			env_list(data);
		else if(ft_memcmp(command, "export", 6) == 0)
			add_env(params_cl[0], data);
		else if(ft_memcmp(command, "unset", 5) == 0)
			ft_delenv(&(data->env_var), params_cl[0]);
		else if(ft_memcmp(command, "exit", 4) == 0)
			ft_free(data, params_cl);
		else
			ft_exec(ft_strjoin(mem, params), data);
//		 command++;
//	}
}
