#include "./include/minishell.h"

int main()
{
	char *buf;

	buf = ft_calloc(sizeof(char), 4096);
	write(1, "\n\n\n\n****************", 22);
	write(1, "********************", 21);
	write(1, "\n\n\n\t****MINISHELL****",22);
	write(1, "\n\n\n\n****************", 22);
	write(1, "********************\n\n\n\n", 25);
	char *argv[] = { "/bin/cat", "builtin_test.c", 0};
      char *envp[] =
      {
          0
      };
	while(1)
	{
		write(1, "> ", 3);
		read(0, buf, 4096);
		if(ft_memcmp(buf, "a", 1) == 0 && fork() == 0)
		{
			execve(argv[0], &argv[0], envp);
//			perror("execve");
		}
		else
			wait(NULL);
	}
	free(buf);
 return (1);
}
