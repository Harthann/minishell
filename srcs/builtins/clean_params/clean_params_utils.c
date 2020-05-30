/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_params_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 16:20:08 by user42            #+#    #+#             */
/*   Updated: 2020/05/30 16:20:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollar_check(t_data *data, char *s, t_env_lst *lst, int index)
{
	if (s[index + 1] == '?')
		return (ft_itoa(data->last_return));
	else
		return (env_value(s, index, lst));
}

int		count_quotechar(char *str, int index)
{
	int c;
	int count;

	c = str[index];
	index++;
	count = 0;
	while (str[index] != c && str[index])
	{
		index++;
		count++;
	}
	return (count + 1);
}

char	*quote_check(char *s, t_env_lst *lst, int index)
{
	int n;

	n = count_quotechar(s, index);
	return (ft_quote(s + index, n, lst));
}
