#include "minishell.h"

int		ft_separate(char *command)
{
	if(command == NULL)
		return (0);
	else if (ft_memcmp(command, ">", 1) == 0)
		return (1);
	else if (ft_memcmp(command, ">>", 2) == 0)
		return (1);
	else if (ft_memcmp(command, "<", 1) == 0)
		return (1);
	else
		return (0);
}

void	advance_list(t_cmd **alist, int *count, int n)
{
	int i;
	t_cmd *lst;

	lst = *alist;

	i = 0;
	while(i < n)
	{
		lst = lst->next;
		*count += 1;
		i++;
	}
	*alist = lst;
}

void	ft_display(t_cmd *list, char *params_mem, int *res)
{
	if (!list || ft_separate(list->command) == 0)
	{
		if(params_mem != NULL)
			ft_putstr_fd(params_mem, 1);
		*res = 0;
	}
}

void pipe_loop(t_cmd **alist, char **mem, t_data *data, int *count)
{
	int n;
	t_cmd *list;

	list = *alist;
	while(check_pipe(list) == 1)
	{
		pipe_fork(list->next, data, mem, &n);
		advance_list(&list, count, n);
	}
	*alist = list;
}

int		fork_parsing(t_cmd *list, t_data *data, int *count)
{
	char	*params_mem;
	int		res;
	int		n;

	res = 1;
	params_mem = NULL;
	while(res == 1 && list)
	{
		errno = 0;
		if(left_redir(list->next) == 1)
			reverse_red_fork(list, data, &params_mem, &n);
		else if(params_mem == NULL)
			normal_fork(list, data, &params_mem, &n);
		advance_list(&list, count, n);
		if(right_redir(list) == 1)
		{
			redirection_fork(list, &params_mem, &n);
			advance_list(&list, count, n);
			if(!list)
			break;
		}
		pipe_loop(&list, &params_mem, data, count);
		ft_display(list, params_mem, &res);
	}
	free(params_mem);
	return (*count);
}
