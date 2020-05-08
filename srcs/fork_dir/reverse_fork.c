#include "minishell.h"

void	reverse_red_fork(t_cmd *list, t_data *data, char **mem)
{
	char *command;
	pid_t p;
	int fd[2];
	int f;
	int fds[2];
//printf("hello\n");
	(void)data;
	pipe(fd);
	
	command = list->command;
	list = list->next;
	p = fork();
	if(p == 0)
	{
		close(fd[0]);
		f = open(list->param, O_RDWR);
		*mem = prs_mem(f);
		dup2(fd[1], 1);
		ft_putstr_fd(*mem, 1);
		close(f);
		_exit(0);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
//		*mem = prs_mem(fd[0]);
		pipe(fds);
		p = fork();
		if (p == 0)
		{
			close(fds[0]);
			dup2(fds[1], 1);
			close(fd[1]);
			dup2(fd[0], 0);
			builtins(command, NULL, data);
			_exit(0);
		}
		else
		{
			wait(NULL);
//			printf("eee\n");
			close(fds[1]);
			free(*mem);
			*mem = prs_mem(fds[0]);
//			printf("[%s]\n", *mem);
		}
	}
//	printf("Good\n");
}
