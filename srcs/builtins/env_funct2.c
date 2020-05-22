#include "minishell.h"


int		lst_size(t_data *data)
{
	t_env_lst	*lst;
	int			count;

	count = 0;
	lst  = data->env_var;
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

int		env_exist(t_env_lst *lst, t_env_lst *new)
{
	char *name;

	name = new->name;
	while (lst)
	{
		if (ft_memcmp(name, lst->name, ft_strlen(name) + 1) == 0)
		{
			free(lst->value);
			lst->value = new->value;
			free(new->name);
			free(new);
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

