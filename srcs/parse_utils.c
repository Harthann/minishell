/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 08:48:02 by nieyraud          #+#    #+#             */
/*   Updated: 2020/05/20 08:48:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_separator(char c, t_quote quote)
{
	if ((c == ';' || c == '<' || c == '|' || c == '>')
		&& !quote.quote && !quote.dquote)
		return (1);
	return (0);
}

void	add_back(t_cmd **list, t_cmd *new)
{
	t_cmd	*tmp;
	char	*to_free;

	tmp = *list;
	to_free = new->command;
	new->command = ft_strtrim(to_free, " ");
	free(to_free);
	to_free = new->param;
	if (new->param && *new->param)
	{
		new->param = ft_strtrim(to_free, " ");
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
