/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 08:46:17 by nieyraud          #+#    #+#             */
/*   Updated: 2020/06/25 08:55:20 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigquit_handler(int signal)
{
	if (g_fg_process > -1)
		kill(g_fg_process, signal);
	if (signal == SIGQUIT)
	{
		if (g_fg_process > -1)
			write(1, "Quit: 3\n", 9);
	}
	else if (signal == SIGINT)
	{
		if (g_fg_process >= 0)
			write(1, "\n", 1);
		else
			write(1, "\nMinishell> ", 12);
	}
}
