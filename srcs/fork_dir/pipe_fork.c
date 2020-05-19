#include "minishell.h"

void	parent_function(int *fds, int *fdb, char **mem, t_data *data)
{
	wait(NULL);
	close(fdb[1]);
	close(fds[1]);
	free(*mem);
	*mem = prs_mem(fds[0]);
	last_return(data, prs_mem(fdb[0]));
	free(fds);
	free(fdb);
}

void	pipe_fork2(t_cmd *lst, t_data *data, char **mem, int fd)
{
	int *fds;
	int *fdb;

	if (!(fds = malloc(sizeof(int) * 2)))
		fds = 0;
	if (!(fdb = malloc(sizeof(int) * 2)))
		fdb = 0;
	pipe(fds);
	pipe(fdb);
	fg_process = fork();
	if(fg_process == 0)
	{
		close(fdb[0]);
		close(fds[0]);
		dup2(fd, 0);
		dup2(fds[1], 1);
		dup2(fdb[1], 2);
		builtins(lst->command, lst->param, data);
		fg_process = -1;
		exit(0);
	}
	else
		parent_function(fds, fdb, mem, data);
	fg_process = -1;
}

void	pipe_fork(t_cmd *lst, t_data *data, char **mem, int *count)
{
	int *fd;

	if (!(fd = malloc(sizeof(int) * 2)))
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
		exit(0);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		pipe_fork2(lst, data, mem, fd[0]);
		free(fd);
	}
	fg_process = -1;
}
