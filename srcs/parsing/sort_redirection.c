/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 11:11:32 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/26 11:38:25 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_front(t_cmd **cmd, t_cmd *new)
{
	new->next = *cmd;
	*cmd = new;
}

void	sort_redirection(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->redirection)
			order_redir(&cmd->redirection);
		cmd = cmd->next;
	}
}

void	order_redir(t_cmd **cmd)
{
	t_cmd *tmp;
	t_cmd *previous;
	t_cmd *next;
	t_cmd *left_redir;

	previous = NULL;
	tmp = *cmd;
	left_redir = NULL;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->command && tmp->command[0] == '<')
		{
			if (previous)
				previous->next = tmp->next;
			else
				*cmd = tmp->next;
			tmp->next = NULL;
			add_back(&left_redir, tmp);
		}
		if (tmp->command[0] != '<')
			previous = tmp;
		tmp = next;
	}
	if (left_redir)
	{
		last_cmd(left_redir)->next = *cmd;
		*cmd = left_redir;
	}
}
