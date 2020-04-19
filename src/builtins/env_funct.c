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
