/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 11:30:52 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/27 11:32:52 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_synerror(char *str, char sep)
{
	ft_putstr_fd(SYNERROR, 2);
	if (sep != '\n')
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

char	sep_is_valid(char sep, char *str)
{
	str += (*str == '>' && *(str + 1) == '>') ? 2 : 1;
	while (*str && *str == ' ')
		str++;
	if (ft_find_char(sep, "|<>") && !is_separator(str, 0) && *str)
		return (0);
	if (ft_find_char(sep, "|<>") && !*str)
		return ('\n');
	if (ft_find_char(sep, "<>") && is_separator(str, 0))
		return (*str);
	if (ft_find_char(sep, "|;") && ft_find_char(*str, "<>"))
		return (sep_is_valid(*str, str));
	if (ft_find_char(sep, "|;") && ft_find_char(*str, "|;"))
		return (*str);
	return (0);
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
			sep = sep_is_valid(str[i], str + i);
			if (sep)
				return (print_synerror(str, sep));
			while (is_separator(str, i))
				i++;
		}
	}
	return (0);
}
