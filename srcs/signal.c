/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 08:46:17 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/14 11:50:26 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigquit_handler(int signal)
{
	if (g_fg_process > -1)
		kill(g_fg_process, signal);
	else
		write(1, "\b\b  \b\b", 6);
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
