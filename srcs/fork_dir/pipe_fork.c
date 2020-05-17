#include "minishell.h"

void	pipe_fork2(t_cmd *lst, t_data *data, char **mem, int fd)
{
	int *fds;
	int fdb[2];
	char *m;
	pid_t p;

	pipe(fdb);
	if(!(fds = malloc(sizeof(int) * 2)))
		fds = 0;
	pipe(fds);
	p = fork();
	if(p == 0)
	{
		close(fdb[0]);
		close(fds[0]);
		dup2(fd, 0);
		dup2(fds[1], 1);
		dup2(fdb[1], 2);
		builtins(lst->command, lst->param, data);
//		write(fdb[1], ft_itoa(errno), ft_strlen(ft_itoa(errno)));
		_exit(0);
	}
	else
	{
		wait(NULL);
		close(fdb[1]);
		close(fds[1]);
		m = prs_mem(fdb[0]);
//		error_child(fdb[0]);
		*mem = prs_mem(fds[0]);
		last_return(data, m);
	}

}

void	pipe_fork(t_cmd *lst, t_data *data, char **mem, int *count)
{
	pid_t p;
	int *fd;

	if(!(fd = malloc(sizeof(int) * 2)))
		fd = 0;
	pipe(fd);
	p = fork();
	*count = 2;
	if(p == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		ft_putstr_fd(*mem, 1);
		_exit(0);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		pipe_fork2(lst, data, mem, fd[0]);
//		last_return(data);
	}
}
