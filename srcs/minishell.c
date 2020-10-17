/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 08:55:18 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/14 13:37:15 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_loop(t_data *data, char **env)
{
	char	*line;
	int		ret;
	int i;

	add_env(env, data);
	data->env = env;
	signal(SIGINT, sigquit_handler);
	signal(SIGQUIT, sigquit_handler);
	ret = 1;
	while (ret > 0)
	{
		data->status = 0;
		i = 0;
		line = NULL;
		g_fg_process = -1;
		write(1, "Minishell> ", 11);
		ret = get_next_line(0, &line);
		if (ret == 0)
			line = ft_strdup("exit");
		data->line = line;
		while ((i += ft_command_parser(line + i, data)) < (int)ft_strlen(line))
			;
		free(line);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	g_fg_process = -1;
	write(1, "\n\n\n\n****************", 20);
	write(1, "********************", 20);
	write(1, "\n\n\n\t****MINISHELL****", 21);
	write(1, "\n\n\n\n****************", 20);
	write(1, "********************\n\n\n\n", 24);
	if (!(data = ft_calloc(sizeof(t_data), 1)))
		return (1);
	main_loop(data, env);
	return (0);
}
