/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 11:11:32 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/25 11:25:44 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	previous = NULL;
	tmp = *cmd;
	while (tmp)
	{
		if (tmp->command && tmp->command[0] == '<' && *cmd != tmp)
		{
			if (previous)
				previous->next = tmp->next;
			tmp->next = *cmd;
			*cmd = tmp;
		}
		previous = tmp;
		tmp = tmp->next;
	}
}
