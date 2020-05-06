#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


int main(int ac, char **av)
{
	char **env;
	char buf[12];
	int fd[2];
//	int f;

	pipe(fd);
	pid_t p;
	p = fork();
	av++;
	env = calloc(1, sizeof(char *));
	if (p > 0)
	{
		close(fd[0]);
		printf("child process\n");
		dup2(fd[1], 1);
		printf("Hello World\n");
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		int fds[2];
		pipe(fds);
		if(fork())
		{
			close(fds[0]);
			dup2(fds[1], 1);
			close(fd[1]);
			dup2(fd[0], 0);
			execve(av[0], av, env);
		}
		else 
		{
			close(fds[1]);
			read(fds[0], buf, 12);
			printf("Parent process : %s", buf);
		}
//		exit(0);
	}
//	close(0);
//	close(fd[0]);
//f = open("main.c", O_RDONLY);
//	dup2(fd[0], 0);
//	write(fd[1], "hello world\0", 12);
//	printf("Hello world");
//	dup2(fd[1], 1);
//	close(1);
//	dup(fd[1]);
//	printf("Hello world\n");
//	close(0);
//	open(fd[0], O_APPEND);
//close(fd[1]);
//	dup2(fd[0], 0);
//	close(fd[0]);
//	open(fd[0], "rw");
//	read(fd[0], buf, 12);
//	printf("%s\n", buf);
//	env = calloc(1, sizeof(char *));
//	av++;
//	(void)ac;
//	(void)av;
//	(void)env;
//	execve(av[0], av, env);
//	perror("execve");
//	exit(0);
}
