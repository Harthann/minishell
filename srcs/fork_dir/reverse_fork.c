#include "minishell.h"

void	reverse_red_fork2(char *command, t_data *data, char **mem, int fd)
{
	int fds[2];
	pid_t p;

	pipe(fds);
	p = fork();
	if (p == 0)
	{
		close(fds[0]);
		dup2(fds[1], 1);
		dup2(fd, 0);
		builtins(command, NULL, data);
		_exit(0);
	}
	else
	{
		wait(NULL);
		close(fds[1]);
		free(*mem);
		*mem = prs_mem(fds[0]);
	}
}

void copy_file(char **mem, char *param)
{
	int f;

	f = open(param, O_RDWR);
	*mem = prs_mem(f);
}

void	reverse_red_fork(t_cmd *list, t_data *data, char **mem, int *count)
{
	char *command;
	pid_t p;
	int *fd;

	if(!(fd = malloc(sizeof(int) * 2)))
		fd = 0;
	pipe(fd);
	*count = 2;
	command = list->command;
	list = list->next;
	p = fork();
	if(p == 0)
	{
		close(fd[0]);
		copy_file(mem, list->param);
		dup2(fd[1], 1);
		ft_putstr_fd(*mem, 1);
		_exit(0);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		reverse_red_fork2(command, data, mem, fd[0]);
	}
}
