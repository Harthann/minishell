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

void	free_builtin(char **params_cl, char **mem)
{
	int i;

	i = 0;
	while(params_cl && params_cl[i] != NULL)
	{
		free(params_cl[i]);
		i++;
	}
	free(params_cl);
	free(mem[0]);
	free(mem);
}

void	free_exec(char *exec, char *path, char **env, char **argv)
{
	int i;

	i = 0;
	free(exec);
	free(path);
	free(env);
	while(argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	ft_free(t_data *data)
{
	data->status = 0;
	exit(0);
}
