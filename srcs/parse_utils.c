/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 08:48:02 by nieyraud          #+#    #+#             */
/*   Updated: 2020/06/30 09:08:30 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_separator(char c, t_quote *quote)
{
	if ((c == ';' || c == '<' || c == '|' || c == '>')
		&& !quote->quote && !quote->dquote && !quote->escp)
		return (1);
	return (0);
}

void	rmv_escp(char *str, int length, char **res, t_quote quote)
{
	int		i;

	i = 0;
	while (str[length + i])
	{
		if (str[length + i] == '\'' && !quote.dquote && !quote.escp)
		{
			quote.quote++;
			quote.quote -= quote.quote == 2 ? 2 : 0;
		}
		if (str[length + i] == '"' && !quote.quote && !quote.escp)
		{
			quote.dquote++;
			quote.dquote -= quote.dquote == 2 ? 2 : 0;
		}
		if (str[length + i] == '\\' && !quote.quote && !quote.escp)
			length += ++quote.escp;
		else
		{
			(*res)[i] = str[length + i];
			i++;
			quote.escp > 0 ? quote.escp-- : 0;
		}
	}
}

char	*escp_trim(char *str)
{
	char	*res;
	int		i;
	int		escp;
	t_quote	quote;

	quote.dquote = 0;
	quote.quote = 0;
	quote.escp = 0;
	i = 0;
	escp = 0;
	while (str[i])
	{
		if (str[i] == '\\' && !i)
			escp++;
		else if (i && str[i] == '\\' && str[i - 1] != '\\')
			escp++;
		i++;
	}
	if (escp == 0)
		return (str);
	if (!(res = ft_calloc(sizeof(char), i - escp + 1)))
		return (0);
	rmv_escp(str, 0, &res, quote);
	free(str);
	return (res);
}

void	add_back(t_cmd **list, t_cmd *new)
{
	t_cmd	*tmp;
	char	*to_free;

	tmp = *list;
	to_free = new->command;
	new->command = ft_strtrim(to_free, " ");
	new->command = escp_trim(new->command);
	free(to_free);
	to_free = new->param;
	if (new->param && *new->param)
	{
		new->param = ft_strtrim(to_free, " ");
		new->param = escp_trim(new->param);
		free(to_free);
	}
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (*list)
		tmp->next = new;
	else
		*list = new;
}

void	free_command(t_cmd **list)
{
	t_cmd *tmp;
	t_cmd *to_free;

	tmp = *list;
	while (tmp)
	{
		free(tmp->command);
		free(tmp->param);
		to_free = tmp;
		tmp = to_free->next;
		free(to_free);
	}
}
