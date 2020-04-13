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
	while(1)
	{
		write(1, "> ", 3);
		read(0, buf, 4096);
	}
	free(buf);
 return (1);
}
