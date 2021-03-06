/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funct2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 16:27:50 by user42            #+#    #+#             */
/*   Updated: 2020/10/14 15:03:36 by stbaleba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		lst_size(t_data *data)
{
	t_env_lst	*lst;
	int			count;

	count = 0;
	lst = data->env_var;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

void	order_tab(char ***tab, int length)
{
	int		i;
	int		j;
	char	**tab1;
	char	*mem;

	i = 0;
	tab1 = *tab;
	while (i < length)
	{
		j = 0;
		while (j + 1 < length)
		{
			if (ft_memcmp(tab1[j], tab1[j + 1], ft_strlen(tab1[j + 1])) > 0)
			{
				mem = tab1[j];
				tab1[j] = tab1[j + 1];
				tab1[j + 1] = mem;
			}
			j++;
		}
		i++;
	}
	*tab = tab1;
}

int		env_exist(t_env_lst *lst, t_env_lst *new, int n)
{
	while (lst)
	{
		if (ft_memplus(lst->name, new->name) == 0)
		{
			if (n != 2 && (ft_memcmp(new->value, "\0", 1)) == 0)
			{
				free_newlst(new);
				return (1);
			}
			if (n != 2)
			{
				free(lst->value);
				lst->value = new->value;
			}
			else
				lst->value = ft_strjoin_free(lst->value, new->value, 3);
			free(lst->name);
			lst->name = new->name;
			free(new);
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

void	ft_delst(t_env_lst *lst, t_env_lst *prev_elem,
				t_env_lst *next_elem, t_env_lst **mem)
{
	free(lst->name);
	free(lst->value);
	free(lst);
	lst = 0;
	if (prev_elem == 0)
	{
		lst = next_elem;
		*mem = next_elem;
	}
	else
		prev_elem->next = next_elem;
}

int		check_env(t_env_lst *lst)
{
	char	*str;
	int		i;

	str = lst->name;
	i = ft_strlen(str);
	if (str[i - 1] == '=')
		return (1);
	return (0);
}
