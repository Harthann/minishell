#include "minishell.h"

void	normal_fork(t_cmd *lst, t_data *data, char **mem, int *count)
{
	int fd[2];
	int save_fd;

	*count = 1;
//	char *mem;
//	printf("hello\n");
	pid_t p;
//(void)data;
//(void)lst;

//if (!(fd = malloc(sizeof(int) * 2)))
//		return (NULL);
//	mem = NULL;
	pipe(fd);
	p = fork();
	if (p == 0)
	{
		save_fd = dup(1);
		close(fd[0]);
		dup2(fd[1], 1);
		builtins(lst->command, lst->param, data);
		dup2(save_fd, 1);
//		close(fd[1]);
		close(save_fd);
		_exit(0);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		*mem = prs_mem(fd[0]);
//		close(fd[0]);
	}
//	close(fd[0]);
//	close(fd[1]);
//	printf("sucess[1]\n");
//	return(mem);
//	return(NULL);

}
