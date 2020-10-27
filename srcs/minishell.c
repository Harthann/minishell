/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 08:55:18 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/20 11:27:36 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_synerror(char *str, char sep)
{
	ft_putstr_fd(SYNERROR, 2);
	if (sep)
		write(2, &sep, 1);
	else
		write(2, "newline", 8);
	ft_putstr_fd(" »\n", 2);
	g_last_return = 2;
	return (ft_strlen(str));
}

void	skip_space(char *str, int *i)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
}

int		check_parser_error(char *str)
{
	int		i;
	char	sep;

	i = 0;
	skip_space(str, &i);
	if (ft_find_char(str[i], "|;"))
		return (print_synerror(str, str[i]));
	while (str[i])
	{
		while (str[i] && !is_separator(str, i))
			i++;
		if (is_separator(str, i))
		{
			sep = str[i];
			if (str[i] == '>' && str[i + 1] == '>')
				i += 2;
			else if (is_separator(str, i))
				i++;
			skip_space(str, &i);
			if (ft_find_char(str[i], "|;")
				|| (!str[i] && ft_find_char(sep, "<>|")))
				return (print_synerror(str, str[i]));
		}
	}
	return (0);
}

int		main_loop(t_data *data, char **env)
{
	int		ret;
	int		i;

	add_env(env, data);
	data->env = env;
	data->path = NULL;
	ret = 1;
	while (ret > 0)
	{
		data->status = 0;
		i = 0;
		data->line = NULL;
		g_fg_process = -1;
		write(1, "Minishell> ", 11);
		ret = get_next_line(0, &data->line);
		if (ret == 0)
			data->line = ft_strdup("exit");
		i += check_parser_error(data->line);
		while ((i += ft_command_parser(data->line + i, data))
				< (int)ft_strlen(data->line))
			;
		free(data->line);
	}
	return (0);
}

int		main(int ac, char **av, char **env)
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
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	data = singleton();
	main_loop(data, env);
	return (0);
}
