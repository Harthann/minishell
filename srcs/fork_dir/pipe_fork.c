#include "minishell.h"

void	pipe_fork(t_cmd *lst, t_data *data, char **mem, int *count)
{
	pid_t p;
	int fd[2];
	int fds[2];

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
		pipe(fds);
		p = fork();
		if(p == 0)
		{
			close(fds[0]);
			dup2(fd[0], 0);
			dup2(fds[1], 1);
			builtins(lst->command, lst->param, data);
			_exit(0);
		}
		else
		{
			wait(NULL);
			close(fds[1]);
			*mem = prs_mem(fds[0]);
//			printf("[%s]\n", *mem);
		}
	}
}
