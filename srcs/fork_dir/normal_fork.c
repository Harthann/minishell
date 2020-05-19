#include "minishell.h"

int		unset_export(t_cmd *list, t_data *data)
{
 	if(ft_memcmp(list->command, "export", 7) == 0 && *(list->param) != '\0')
	{
		builtins(list->command, list->param, data);
		return (1);
	}
	else if(ft_memcmp(list->command, "unset", 5) == 0)
	{
		builtins(list->command, list->param, data);
		return (1);
	}
	else if (ft_memcmp(list->command, "cd", 3) == 0)
	{
		builtins(list->command, list->param, data);
		return (1);
	}
	return (0);
}

void	child_function(int *fd, int *fde, t_cmd *lst, t_data *data)
{
	close(fde[0]);
	close(fd[0]);
	dup2(fd[1], 1);
	dup2(fde[1], 2);
	builtins(lst->command, lst->param, data);
	exit(0);
}

void	normal_fork(t_cmd *lst, t_data *data, char **mem, int *count)
{
	int		*fd;
	int		*fde;

	*count = 1;
	if (!(fd = malloc(sizeof(int) * 2)))
		return ;
	if (!(fde = malloc(sizeof(int) * 2)))
		return ;
	pipe(fd);
	pipe(fde);
	fg_process = fork();
	if (fg_process == 0)
		child_function(fd, fde, lst, data);
	else
	{
		wait(NULL);
		close(fde[1]);
		close(fd[1]);
		free(*mem);
		*mem = NULL;
		if(unset_export(lst, data) == 0)
				*mem = prs_mem(fd[0]);
		else
			close(fd[0]);
		free(fd);
		last_return(data, prs_mem(fde[0]));
		free(fde);
	}
}
