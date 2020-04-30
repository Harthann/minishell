#include "../../include/minishell.h"
#include <stdio.h>

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

void	add_env(char *str, t_data *data)
{
	char *name;
	char *value;
	int	 i;

	i = 0;
	name = ft_calloc(ft_strlen(str), sizeof(char));
	value = ft_calloc(ft_strlen(str), sizeof(char));
	while (*str != '=' && *str)
	{
		name[i++] = *str;
		str++;
	}
	str++;
	i = 0;
	while(*str)
	{
		value[i++] = *str;
		str++;
	}
	if(*value != '\0')
		ft_addenv(&(data->env_var), ft_envnew(name, value));
}

void	ft_addenv(t_env_lst **alst, t_env_lst *new)
{
	t_env_lst *lst;

	lst = *alst;
	if (!lst)
		*alst = new;
	else
	{
		while (lst->next)
			lst = lst->next;
		lst->next = new;
	}
}

void	ft_delenv(t_env_lst **alst, char *name)
{
	t_env_lst *lst;
	t_env_lst *mem;
	t_env_lst *prev_elem;
	t_env_lst *next_elem;

	lst = *alst;
	mem = lst;
	prev_elem = 0;
	while (lst)
	{
		next_elem = lst->next;
		if(ft_memcmp(name, lst->name, ft_strlen(name) + 1) == 0)
		{
			free(lst);
			if(prev_elem == 0)
			{
				lst = next_elem;
				mem = next_elem;
			}
			else
				prev_elem->next = next_elem;
		}
		prev_elem = lst;
		lst = lst->next;
	}
	*alst = mem;
}

void	env_list(t_data *data)
{
	t_env_lst *lst;

	lst = data->env_var;
	while(lst)
	{
		display(lst->name, data);
		display("=", data);
		display(lst->value, data);
		display("\n", data);
		lst = lst->next;
	}
}
