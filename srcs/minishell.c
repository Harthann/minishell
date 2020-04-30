#include "minishell.h"

int	main_loop(t_all *all)
{
	char	*buffer;
	int	ret;

	if (!(buffer = ft_calloc(sizeof(char), 4096)))
		return (-1);
	all->status = 1;
	while(all->status)
	{
		write(1, "Minishell> ", 11);
		ret = read(0, buffer, 4096);
		buffer[ret]= '\0';
		all->status = ft_command_parser(buffer);
	}
	free(buffer);
	return (0);
}


int main(int ac, char **av)
{
	t_all	*all;

	(void)ac;
	(void)av;
	write(1, "\n\n\n\n****************", 22);
	write(1, "********************", 21);
	write(1, "\n\n\n\t****MINISHELL****",22);
	write(1, "\n\n\n\n****************", 22);
	write(1, "********************\n\n\n\n", 25);
	if (!(all = ft_calloc(sizeof(t_all), 1)))
		return (1);
	main_loop(all);
	return (0);
}
