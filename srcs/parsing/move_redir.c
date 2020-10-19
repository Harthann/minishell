/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 13:39:49 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/19 15:23:45 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data *singleton(void)
{
	static t_data *data = NULL;

	if (data)
		return (data);
	if (!(data = ft_calloc(sizeof(t_data), 1)))
		return (NULL);
	return (data);
}

void	append_params(char *str, int *i, t_data *data, t_cmd *cmd)
{
	char	**params;
	int		length;
	int		length_params;

	params = parse_param(str, i, data);
	if (!params)
		return ;
	length = 0;
	length_params = 0;
	while (params[length])
		length++;
	while (cmd->params && cmd->params[length_params])
		length_params++;
	cmd->params = ft_tab_append(cmd->params, length_params, params, length);
}

void	move_redir(t_cmd **cmd)
{
	t_cmd *previous;
	t_cmd *tmp;

	previous = NULL;
	tmp = *cmd;
	while (tmp && tmp->next)
	{
		previous = tmp;
		tmp = tmp->next;
	}
	add_back(&tmp->redirection, tmp);
	if (previous)
		previous->next = NULL;
	else
		*cmd = NULL;
}

int		create_commands(t_cmd **cmd, char *str, t_data *data, int *i)
{
	t_cmd *news;

	news = new_command(str, i, data);
	if (!news)
		return (1);
	if (!ft_strncmp(news->command, "<", 1)
		|| !ft_strncmp(news->command, ">", 1))
	{
		if (*cmd)
			append_params(str, i, data, *cmd);
		else
			create_commands(cmd, str, data, i);
		if (!*cmd)
			*cmd = ft_calloc(sizeof(t_cmd), 1);
		add_back(&(*cmd)->redirection, news);
	}
	else
		add_back(cmd, news);
	return (0);
}
