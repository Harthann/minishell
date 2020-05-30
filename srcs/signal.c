/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 08:46:17 by nieyraud          #+#    #+#             */
/*   Updated: 2020/05/26 13:34:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigquit_handler(int signal)
{

	if (fg_process > -1)
		kill(fg_process, signal);
	if (signal == SIGQUIT)
	{
		// write(1, "\b\b  \b\b", 6);
		if (fg_process > -1)
			write(1, "Exit (core dumped)", 18);
	}
	else if (signal == SIGINT)
		write(1, "\nMinishell> ", 12);
}
