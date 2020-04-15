#include "minishell.h"

int	main_loop(void)
{
	char *buffer;
	int status;
	int ret;

	if (!(buffer = ft_calloc(sizeof(char), 4096)))
		return (-1);
	status = 1;
	while(status)
	{
		write(1, "Minishell> ", 11);
		ret = read(0, buffer, 4096);
		buffer[ret]= '\0';
		status = ft_command_parser(buffer);
	}
	free(buffer);
	return (0);
}


int main()
{
	write(1, "\n\n\n\n****************", 22);
	write(1, "********************", 21);
	write(1, "\n\n\n\t****MINISHELL****",22);
	write(1, "\n\n\n\n****************", 22);
	write(1, "********************\n\n\n\n", 25);
	main_loop();
	return (0);
}
