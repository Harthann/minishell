/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 16:20:28 by user42            #+#    #+#             */
/*   Updated: 2020/05/30 16:22:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_env(char *params, int index, int c_env, t_env_lst *lst)
{
	params = params + index;
	while (lst)
	{
		if (ft_memcmp(params, lst->name, c_env) == 0)
			return (ft_strlen(lst->value));
		lst = lst->next;
	}
	return (2);
}

int		count_qchar(char *params, t_env_lst *lst, int quote_type, int index)
{
	int count;
	int c_env;
	int i;

	count = 0;
	i = 0;
	while (i < index)
	{
		if (params[i] == '$' && quote_type == 34)
		{
			c_env = 0;
			i++;
			while (params[i] != 34 && params[i + 1] != ' ' &&
				params[i + 1] != '\0')
			{
				c_env++;
				i++;
			}
			count += count_env(params, i - c_env, c_env, lst);
		}
		count++;
		i++;
	}
	return (count);
}

void	dollar_quote(char *params, char **res, int *i, t_env_lst *lst)
{
	char	*mem;
	int		j;

	j = 0;
	mem = env_value2(params + 1, lst);
	while (mem[j])
		(*res)[(*i)++] = mem[j++];
	free(mem);
}

char	*ft_quote(char *params, int index, t_env_lst *lst)
{
	int		n;
	char	*res;
	int		j;
	int		i;

	n = count_qchar(params, lst, params[index], index);
	if (!(res = ft_calloc(n + 1, sizeof(char *))))
		return (NULL);
	i = 0;
	j = 0;
	while (j <= index)
	{
		if (params[j] == '$' && params[index] == 34)
		{
			dollar_quote(params + j, &res, &i, lst);
			while (params[j + 1] != 34 && params[j + 1] != '$')
				j++;
		}
		else if (params[j] != params[index])
			res[i++] = params[j];
		j++;
	}
	res[i] = '\0';
	return (res);
}
