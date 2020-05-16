#include "minishell.h"

void	unset_export(t_cmd *list, t_data *data)
{
 	if(ft_memcmp(list->command, "export", 6) == 0 && list->param != NULL)
		builtins(list->command, list->param, data);
	else if(ft_memcmp(list->command, "unset", 5) == 0)
		builtins(list->command, list->param, data);

}


void	normal_fork(t_cmd *lst, t_data *data, char **mem, int *count)
{
	int		*fd;
	int		save_fd;

	*count = 1;
	if(!(fd = malloc(sizeof(int) * 2)))
		fd = 0;
	pipe(fd);
	fg_process = fork();
	if (fg_process == 0)
	{
		save_fd = dup(1);
		close(fd[0]);
		dup2(fd[1], 1);
		builtins(lst->command, lst->param, data);
		dup2(save_fd, 1);
		close(save_fd);
		_exit(0);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		*mem = prs_mem(fd[0]);
		unset_export(lst, data);
	}
}
