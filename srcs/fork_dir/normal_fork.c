#include "minishell.h"

char *normal_fork(t_cmd *lst, t_data *data)
{
	int fd[2];
	char *mem;
//	printf("hello\n");
//	pid_t p;
//(void)data;
//(void)lst;

//if (!(fd = malloc(sizeof(int) * 2)))
//		return (NULL);
	mem = NULL;
	pipe(fd);
//	p = fork();
	if (fork() > 0)
	{
//		printf("Child process\n");
		close(fd[0]);
		dup2(fd[1], 1);
		builtins(lst->command, lst->param, data);
	}
	else
	{
//		printf("Parent Process\n");
		wait(NULL);
		close(fd[1]);
		mem = prs_mem(fd[0]);
		close(fd[0]);
	}
//	printf("sucess[1]\n");
	return(mem);
//	return(NULL);

}
