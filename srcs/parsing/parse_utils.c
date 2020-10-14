/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 08:48:02 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/14 16:41:34 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_separator(char *str, int start)
{
	if (ft_find_char(str[start], "<>|;") && !is_escape(str, start))
		return (1);
	return (0);
}

char	*extract_quote(char *str, int *start)
{
	char	*ret;
	int		i;

	i = *start + 1;
	while (str[i] && str[i] != '\'')
		i++;
	ret = ft_substr(str, *start + 1, i - 1 - *start);
	*start = i;
	return (ret);
}

char	*extract_dquote(char *str, int *start, t_data *data)
{
	char	*ret;
	int		i;

	i = *start + 1;
	ret = NULL;
	while (str[i] && str[i] != '"')
	{
		if (str[i] == '\\' && (str[i + 1] == '"' || str[i + 1] == '$'))
		{
			ret = ft_strapp_free(ret, str[i + 1]);
			i++;
		}
		else if (str[i] == '$' && !is_escape(str, i))
			ret = ft_strjoin_free(ret, extract_dollar(str, &i, data), 3);
		else
			ret = ft_strapp_free(ret, str[i]);
		i += str[i] == '"' && !is_escape(str, i) ? 0 : 1;
	}
	(*start) = i;
	return (ret);
}

void	add_back(t_cmd **list, t_cmd *new)
{
	t_cmd	*tmp;

	if (list)
		tmp = *list;
	else
		tmp = NULL;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new;
	else
		*list = new;
}

void	free_command(t_cmd **list)
{
	t_cmd	*tmp;
	t_cmd	*to_free;
	int		j;

	tmp = *list;
	while (tmp)
	{
		free(tmp->command);
		j = 0;
		while (tmp->params && tmp->params[j])
		{
			free(tmp->params[j]);
			j++;
		}
		free(tmp->params);
		to_free = tmp;
		tmp = to_free->next;
		free(to_free);
	}
}
