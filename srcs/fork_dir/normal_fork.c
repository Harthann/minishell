#include "minishell.h"

void	unset_export(t_cmd *list, t_data *data)
{
 	if(ft_memcmp(list->command, "export", 7) == 0 && *(list->param) != '\0')
		builtins(list->command, list->param, data);
	else if(ft_memcmp(list->command, "unset", 5) == 0)
		builtins(list->command, list->param, data);
	else if (ft_memcmp(list->command, "cd", 3) == 0)
		builtins(list->command, list->param, data);
}


void	normal_fork(t_cmd *lst, t_data *data, char **mem, int *count)
{
	int		*fd;
	int 	fds[2];
	int		save_fd;

	*count = 1;
	pipe(fds);
	if(!(fd = malloc(sizeof(int) * 2)))
		fd = 0;
	pipe(fd);
	child_process = fork();
	if (child_process == 0)
	{
		close(fds[0]);
		save_fd = dup(1);
		close(fd[0]);
		dup2(fd[1], 1);
		builtins(lst->command, lst->param, data);
		dup2(save_fd, 1);
		close(save_fd);
		write(fds[1], ft_itoa(errno), ft_strlen(ft_itoa(errno)));
		_exit(0);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		close(fds[1]);
		*mem = prs_mem(fd[0]);
		error_child(fds[0]);
		free(fd);
//		free(fds);
		unset_export(lst, data);
		last_return(data);

	}
}
