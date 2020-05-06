#include "minishell.h"
#include "libft.h"

char *extract_param(char *str, t_quote quote, int *i)
{
	int length;
	char *param;

	length = 0;
	while (str[length])
	{
		if (is_separator(str[length], quote))
			break ;
		if (str[length] == 27 && quote.dquote == 0)
		{
			quote.quote++;
			quote.quote -= quote.quote == 2 ? 2 : 0; 
		}
		if (str[length] == 22 && quote.quote == 0)
		{
			quote.dquote++;
			quote.dquote -= quote.dquote == 2 ? 2 : 0; 
		}
		length++;
	}
	param = ft_substr(str, 0, length);
	*i += length;
	return (param);
}

t_cmd	*new_command(char *str, int *start)
{
	t_cmd	*cmd;
	t_quote quote;
	int	i;
	
	if (!(cmd = ft_calloc(sizeof(t_cmd), 1)))
		return (NULL);
	quote.dquote = 0;
	quote.quote = 0;
	i = 0;
	while (str[i] != ' ' && str[i] && !is_separator(str[i], quote))
		i++;
	printf("[%d]\n", i);
	if (*str == '|' || *str == '<' || *str == '>')
		i += (*str == '>' && *(str + 1) == '>') ? 2 : 1;
	cmd->command = ft_substr(str , 0, i);
	while (str[i] == ' ' && str[i])
		i++;
	if (str[i] == '|' || str[i] == '<' || str[i] == '>' || *str == '|')
		cmd->param = ft_strdup("");
	else
		cmd->param = extract_param(str + i, quote, &i);
	*start += i;
	return (cmd);
}

int	ft_command_parser(char *str, t_data *data)
{
	t_cmd	*commands;
	int	i;

	i = 0;
	commands = NULL;
	while (str[i])
	{
		add_back(&commands, new_command(str + i, &i));
		while ((str[i] == ';' || str[i] == ' ') && str[i])
			i++;
	}
	cmd_director(commands, data);
	return (1);
}
