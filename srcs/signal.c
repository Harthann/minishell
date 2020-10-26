/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 08:46:17 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/26 15:13:29 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	id_info(void) __attribute__((constructor));

void id_info(void)
{
	printf("This is process with id : [%d]\n", g_fg_process);
}

void	sigquit_handler(int signal)
{
	int status;
	int tmp;

	tmp = waitpid(-1, &status, WUNTRACED);
	if (tmp == -1)
	{
		write(1, "\b\b  \b\b", 6);
		return ;
	}
	if (g_fg_process > 0)
		kill(g_fg_process, signal);
	singleton()->statuspid = status;
	if (tmp > -1 && WIFSIGNALED(status))
		write(1, "Quit: (core dumped)\n", 21);
}

void	sigint_handler(int signal)
{
	int status;
	int	tmp;

	tmp = waitpid(-1, &status, WUNTRACED);
	if (tmp == -1 && g_fg_process == -1)
	{
		write(1, "\b\b  \b\b\nMinishell> ", 19);
		g_last_return = 130;
		return ;
	}
	if (g_fg_process > 0)
		kill(g_fg_process, signal);
	singleton()->statuspid = status;
	if (tmp > -1 && WIFSIGNALED(status))
		write(1, "\n", 1);
	if (singleton()->line)
	{
		free(singleton()->line);
		singleton()->line = NULL;
	}
}
