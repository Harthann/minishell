#include "../include/minishell.h"


void	ft_exec(char *exec, t_data *data)
{
	char **argv;
	char **env;

	argv = clean_params(exec, data->env_var);
	env = ft_calloc(1, sizeof(char *));
	execve(argv[0], &argv[0], env);
	perror("execve");
}

