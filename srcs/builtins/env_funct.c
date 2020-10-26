/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 16:38:24 by user42            #+#    #+#             */
/*   Updated: 2020/10/14 15:04:23 by stbaleba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_lst	*ft_envnew(char *name, char *value)
{
	t_env_lst *new;

	new = 0;
	if (!(new = ft_calloc(1, sizeof(t_env_lst))))
		return (NULL);
	new->name = name;
	new->value = value;
	new->next = 0;
	return (new);
}

void		add_env(char **str, t_data *data)
{
	char	*name;
	char	*value;
	int		tab[2];
	char 	*src;

	while (*str)
	{
		tab[0] = 0;
		tab[1] = 0;
		src = *str;
		while (src[tab[0]] && tab[1] == 0)
		{
			tab[0] = tab[0] + 1;
			if (src[tab[0]])
				tab[1] = check_str(src[tab[0]], src[tab[0] + 1]);
		}
		name_value(&name, &value, src, tab);
		if (check_char(name, value) == 1)
			ft_addenv(&(data->env_var), ft_envnew(name, value), tab[1]);
		str++;
	}
}

void		ft_addenv(t_env_lst **alst, t_env_lst *new, int n)
{
	t_env_lst *lst;

	lst = *alst;
	if (!lst)
		*alst = new;
	else
	{
		if (env_exist(lst, new, n) == 1)
			return ;
		else
		{
			while (lst->next)
				lst = lst->next;
			lst->next = new;
		}
	}
}

void		ft_delenv(t_env_lst **alst, char **name)
{
	t_env_lst *lst;
	t_env_lst *mem;
	t_env_lst *prev_elem;
	t_env_lst *next_elem;

	lst = *alst;
	mem = *alst;
	prev_elem = 0;
	if (name == NULL)
		return ;
	while (name && *name)
	{
		lst = mem;
		while (lst)
		{
			next_elem = lst->next;
			if (ft_memplus(*name, lst->name) == 0)
				ft_delst(lst, prev_elem, next_elem, &mem);
			prev_elem = lst;
			lst = next_elem;
		}
		name++;
	}
	*alst = mem;
}

void		env_list(t_data *data, char *params)
{
	t_env_lst *lst;

	lst = data->env_var;
	if (params == NULL)
	{
		while (lst)
		{
			if (check_env(lst) == 1)
			{
				display(lst->name);
				display(lst->value);
				display("\n");
			}
			lst = lst->next;
		}
	}
	else
	{
		errno = 127;
		ft_putstr_fd(strerror(2), 2);
		write(2, "\n", 2);
	}
}
