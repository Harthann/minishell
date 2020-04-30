#include "minishell.h"
#include "libft.h"

int	is_separator(char c, t_quote quote)
{
	if (c == ';' && !quote.quote && !quote.dquote)
		return (1);
	return (0);
}


t_cmd	*new_command(char *str, int *start)
{
	t_cmd	*cmd;
	t_quote quote;
	int	i;
	int	length;
	
	if (!(cmd = ft_calloc(sizeof(t_cmd), 1)))
		return (NULL);
	quote.dquote = 0;
	quote.quote = 0;
	i = 0;
	while (str[i] != ' ' && str[i])
		i++;
	cmd->command = ft_substr(str , 0, i + 1);
	while (str[i] == ' ' && str[i])
		i++;
	length = 0;
	while (str[i + length])
	{
		if (is_separator(str[i + length], quote))
			break ;
		if (str[i + length] == 27 && quote.dquote == 0)
		{
			quote.quote++;
			quote.quote -= quote.quote == 2 ? 2 : 0; 
		}
		if (str[i + length] == 22 && quote.quote == 0)
		{
			quote.dquote++;
			quote.dquote -= quote.dquote == 2 ? 2 : 0; 
		}
		length++;
	}
	cmd->param = ft_substr(str, i, length);
	*start += i + length;
	return (cmd);
}

void	add_back(t_cmd **list, t_cmd *new)
{
	t_cmd *tmp;

	tmp = *list;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (*list)
		tmp->next = new;
	else
		*list = new;
}

int	ft_command_parser(char *str)
{
	t_cmd	*commands;
	int	i;

	i = 0;
	commands = NULL;
	//if (!(commands = ft_calloc(sizeof(t_cmd), 1)))
	//	return (1);
	while (str[i])
	{
		add_back(&commands, new_command(str + i, &i));
		while ((str[i] == ';' || str[i] == ' ') && str[i])
			i++;
	}
	print_cmd(commands);
	if (!ft_strncmp("exit", commands->command, 4))
		return (0);
	return (1);
}
