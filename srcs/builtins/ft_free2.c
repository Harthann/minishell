/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 08:28:17 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/20 10:06:13 by nieyraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		free_datas(t_cmd **alst, t_data *data, int *fd)
{
	int		tmp;

	tmp = data->exit_code;
	free(data->line);
	free(data->path);
	free_lst(&(data->env_var));
	free_command(alst);
	if (fd != NULL)
		free(fd);
	free(data);
	return (tmp);
}

void	error_cd(char *params)
{
	errno = 1;
	write(2, "Minishell: cd: ", 16);
	ft_putstr_fd(params, 2);
	write(2, ": ", 2);
	ft_putstr_fd(strerror(2), 2);
	write(2, "\n", 2);
}

void	free_newlst(t_env_lst *new)
{
	free(new->name);
	free(new->value);
	free(new);
}

int		redirect_exit(t_info p, t_cmd *cmd)
{
	int n;
	int fd;

	n = 0;
	if (left_redir(cmd) == 1)
	{
		fd = ft_redirect(cmd, &p);
		if (fd == -1)
			return (0);
	}
	while (n < p.end_pass)
	{
		cmd = cmd->next;
		n++;
	}
	if (right_redir(cmd) == 1)
		ft_redirect2(cmd);
	return (1);
}
