/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 08:46:17 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/20 11:28:20 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigquit_handler(int signal)
{
	if (g_fg_process > -1)
		kill(g_fg_process, signal);
	else
		write(1, "\b\b  \b\b", 6);
	if (g_fg_process > -1)
		write(1, "Quit: 3\n", 9);
}

void	sigint_handler(int signal)
{
	if (g_fg_process > -1)
		kill(g_fg_process, signal);
	if (g_fg_process == -1)
	{
		write(1, "\b\b  \b\b\nMinishell> ", 19);
		g_last_return = 130;
	}
	else
		write(1, "\n", 1);
	if (singleton()->line)
	{
		free(singleton()->line);
		singleton()->line = NULL;
	}
}
