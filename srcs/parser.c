/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 08:41:08 by nieyraud          #+#    #+#             */
/*   Updated: 2020/06/26 10:40:07 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_param(char *str, t_quote quote, int *i)
{
	int		length;
	char	*param;

	length = 0;
	quote.escp = 0;
	while (str[length])
	{
		if (is_separator(str[length], &quote))
			break ;
		if (str[length] == '\\' && !quote.quote)
			!quote.escp ? quote.escp++ : quote.escp--;
		if (str[length] == '\'' && !quote.dquote && !quote.escp)
		{
			quote.quote++;
			quote.quote -= quote.quote == 2 ? 2 : 0;
		}
		if (str[length] == '"' && !quote.quote && !quote.escp)
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
	t_quote	quote;
	int		i;

	if (!(cmd = ft_calloc(sizeof(t_cmd), 1)))
		return (NULL);
	quote.dquote = 0;
	quote.quote = 0;
	quote.escp = 0;
	i = -1;
	while (str[++i] != ' ' && str[i] && !is_separator(str[i], &quote))
		str[i] == '\\' && !quote.escp ? quote.escp++ : 0;
	if (*str == '|' || *str == '<' || *str == '>')
		i += (*str == '>' && *(str + 1) == '>') ? 2 : 1;
	cmd->command = ft_substr(str, 0, i);
	while (str[i] == ' ' && str[i])
		i++;
	if (str[i] == '|' || str[i] == '<' || str[i] == '>' || *str == '|')
		cmd->param = ft_strdup("");
	else
		cmd->param = extract_param(str + i, quote, &i);
	*start += i;
	return (cmd);
}

int		ft_command_parser(char *str, t_data *data)
{
	t_cmd	*commands;
	int		i;

	i = 0;
	commands = NULL;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i])
	{
		add_back(&commands, new_command(str + i, &i));
		while ((str[i] == ';' || str[i] == ' ') && str[i])
			i++;
	}
	cmd_director(commands, data);
	free_command(&commands);
	return (1);
}
