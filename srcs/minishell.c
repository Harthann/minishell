#include "minishell.h"


int	main_loop(t_data *data)
{
	char	*line;
	int		ret;

	data->status = 1;
	while(data->status)
	{
		write(1, "Minishell> ", 11);
		ret = get_next_line(0, &line);
		data->status = ft_command_parser(line, data);
	}
	free(line);
	return (0);
}

int main(int ac, char **av)
{
	t_data	*data;

	(void)ac;
	(void)av;
	write(1, "\n\n\n\n****************", 22);
	write(1, "********************", 21);
	write(1, "\n\n\n\t****MINISHELL****",22);
	write(1, "\n\n\n\n****************", 22);
	write(1, "********************\n\n\n\n", 25);
	if (!(data = ft_calloc(sizeof(t_data), 1)))
		return (1);
	main_loop(data);
	return (0);
}
