#include "minishell.h"
#include "libft.h"

void	split_command(char *str, char **command, char **parameter)
{
	int i;

	i = 0;
	while (str[i] != ' ' && str[i])
		i++;
	*command = ft_substr(str, 0, i + 1);
	*parameter = ft_substr(str, i, ft_strlen(str) - i);
}

int	ft_command_parser(char *str)
{
	char *command;
	char *parameter;

	split_command(str, &command, &parameter);
	ft_putstr_fd("Command : ", 1);
	ft_putstr_fd(command, 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("Parameter : ", 1);
	ft_putstr_fd(parameter, 1);
	ft_putchar_fd('\n', 1);
	if (!ft_strncmp("exit", command, 4))
	{
		free(command);
		free(parameter);
		return (0);
	}
	free(command);
	free(parameter);
	return (1);
}
