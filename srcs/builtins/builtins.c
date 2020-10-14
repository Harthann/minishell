/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 16:56:11 by user42            #+#    #+#             */
/*   Updated: 2020/10/14 17:13:15 by stbaleba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_display_export(t_env_lst *lst, char **tab)
{
	int			i;
	t_env_lst	*mem;

	mem = lst;
	i = 0;
	while (tab[i])
	{
		if (ft_memcmp(tab[i], lst->name, ft_strlen(tab[i]) + 1) == 0)
		{
			display("declare -x ");
			display(lst->name);
			display(lst->value);
			display("\n");
			lst = mem;
			i++;
		}
		else
			lst = lst->next;
	}
}

void	export_display(t_data *data)
{
	char		**str;
	int			i;
	int			length;
	t_env_lst	*mem;

	mem = data->env_var;
	length = lst_size(data);
	str = ft_calloc(length + 1, sizeof(char *));
	i = 0;
	while (mem)
	{
		str[i++] = mem->name;
		mem = mem->next;
	}
	str[i++] = NULL;
	order_tab(&str, length);
	ft_display_export(data->env_var, str);
	free(str);
}

void	builtins(char *command, char **params, t_data *data)
{
	char *dest;

	dest = (params == NULL) ? NULL : params[0];
	if (ft_memcmp(command, "echo", 5) == 0)
		ft_echo(params);
	else if (ft_memcmp(command, "pwd", 4) == 0)
		pwd(dest);
	else if (ft_memcmp(command, "cd", 3) == 0)
		cd(params, data);
	else if ((ft_memcmp(command, "export", 7) == 0 && params == NULL))
		export_display(data);
	else if (ft_memcmp(command, "env", 4) == 0)
		env_list(data, dest);
	else if (ft_memcmp(command, "export", 7) == 0)
		add_env(params, data);
	else if (ft_memcmp(command, "unset", 6) == 0)
		ft_delenv(&(data->env_var), params);
	else if (ft_memcmp(command, "exit", 5) == 0)
		ft_free(data, params, dest);
	else
		ft_exec(command, params, data);
}
