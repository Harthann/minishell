#include "minishell.h"

void	pipe_fork2(t_cmd *lst, t_data *data, char **mem, int fd)
{
	int *fds;

	if(!(fds = malloc(sizeof(int) * 2)))
		fds = 0;
	pipe(fds);
	fg_process = fork();
	if(fg_process == 0)
	{
		close(fds[0]);
		dup2(fd, 0);
		dup2(fds[1], 1);
		builtins(lst->command, lst->param, data);
		fg_process = -1;
		_exit(0);
	}
	else
	{
		wait(NULL);
		close(fds[1]);
		*mem = prs_mem(fds[0]);
	}
	fg_process = -1;
}

void	pipe_fork(t_cmd *lst, t_data *data, char **mem, int *count)
{
	int *fd;

	if(!(fd = malloc(sizeof(int) * 2)))
		fd = 0;
	pipe(fd);
	fg_process = fork();
	*count = 2;
	if(fg_process == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		ft_putstr_fd(*mem, 1);
		fg_process = -1;
		_exit(0);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		pipe_fork2(lst, data, mem, fd[0]);
	}
	fg_process = -1;
}
