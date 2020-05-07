#include "minishell.h"

char *normal_fork(t_cmd *lst, t_data *data)
{
	int fd[2];
	int save_fd;
	char *mem;
//	printf("hello\n");
	pid_t p;
//(void)data;
//(void)lst;

//if (!(fd = malloc(sizeof(int) * 2)))
//		return (NULL);
	mem = NULL;
	pipe(fd); 
	p = fork();
	if (p == 0)
	{
		printf("Child process\n");
		wait(NULL);
		close(fd[1]);
		mem = prs_mem(fd[0]);

	}
	else
	{
		save_fd = dup(1);
		printf("Parent Process\n");
		close(fd[0]);
		dup2(fd[1], 1);
		builtins(lst->command, lst->param, data);
		dup2(save_fd, 1);
		close(fd[1]);
		close(save_fd);
//		close(fd[0]);
	}
//	close(fd[0]);
//	close(fd[1]);
//	printf("sucess[1]\n");
	return(mem);
//	return(NULL);

}
