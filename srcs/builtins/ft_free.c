/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 08:49:10 by nieyraud          #+#    #+#             */
/*   Updated: 2020/08/31 09:15:09 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	free_lst(t_env_lst **alst)
{
	t_env_lst *lst;
	t_env_lst *mem;

	lst = *alst;
	while (lst)
	{
		free(lst->name);
		free(lst->value);
		mem = lst;
		lst = lst->next;
		free(mem);
	}
	free(alst);
}

void	free_builtin(char **params_cl, char **mem)
{
	int i;

	i = 0;
	while (params_cl && params_cl[i] != NULL)
	{
		free(params_cl[i]);
		i++;
	}
	free(params_cl);
	free(mem[0]);
	free(mem);
}

void	free_exec(char *exec, char *path, char **env, char **argv)
{
	int i;

	i = 0;
	free(exec);
	free(path);
	free(env);
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	error_exit(t_data *data)
{
	ft_putstr_fd("Too many arguments\n", 2);
	errno = 7;
	data->last_return = 127;
}

void	ft_free(t_data *data, char **params)
{
	int		i;
	char	*str;

	i = 0;
	errno = 0;
	while (params[i])
		i++;
	if (i > 1)
		error_exit(data);
	else
	{
		str = params[0];
		while (str && *str)
		{
			if (ft_isdigit(*str) == 0)
				errno = 1;
			str++;
		}
		if (params[0])
			data->exit_code = (unsigned char)ft_atoi(params[0]);
		ft_putstr_fd("exit\n", 1);
		if (errno != 0)
			ft_putstr_fd("numeric argument required\n", 2);
		exit(data->exit_code);
	}
}
