#include "minishell.h"

void	reverse_red_fork2(t_cmd *list, t_data *data, char **mem, int fd)
{
	int *fds;
	int fdb[2];
	char *m;
	pid_t p;

	if(!(fds = malloc(sizeof(int) * 2)))
		fds = 0;
	pipe(fds);
	pipe(fdb);
	p = fork();
	if (p == 0)
	{
		close(fdb[0]);
		close(fds[0]);
		dup2(fds[1], 1);
		dup2(fd, 0);
		dup2(fdb[1], 2);
		builtins(list->command, list->param, data);
//		write(fdb[1], ft_itoa(errno), ft_strlen(ft_itoa(errno)));
		_exit(0);
	}
	else
	{
		wait(NULL);
		close(fdb[1]);
//		error_child(fdb[0]);
		close(fds[1]);
		m = prs_mem(fdb[0]);
		free(*mem);
		*mem = prs_mem(fds[0]);
		last_return(data, m);
	}
}

void copy_file(char **mem, int f)
{
	*mem = prs_mem(f);
}

void	reverse_red_fork(t_cmd *list, t_data *data, char **mem, int *count)
{
	t_cmd *m;
	pid_t p;
	int *fd;
	int f; 

	if(!(fd = malloc(sizeof(int) * 2)))
		fd = 0;
	pipe(fd);
	*count = 2;
//	next_params = list->next->param;
	m = list->next;
	if((f = open(m->param, O_RDWR)) == -1)
	{
		errno = 2;
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 2);
		last_return(data, "\0");
		return ;
	}
	p = fork();
	if(p == 0)
	{
		close(fd[0]);
		copy_file(mem, f);
		dup2(fd[1], 1);
		ft_putstr_fd(*mem, 1);
		_exit(0);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		reverse_red_fork2(list, data, mem, fd[0]);
//		last_return(data);
	}
}
