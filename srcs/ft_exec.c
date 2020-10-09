/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 09:01:47 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/09 14:35:53 by stbaleba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_path(char **path)
{
	int		i;
	char	*cmd;

	i = 0;
	while ((*path)[i] != ':' && (*path)[i])
		i++;
	if (i == 0)
		cmd = NULL;
	else
		cmd = ft_substr(*path, 0, i);
	if ((*path)[i])
		(*path)++;
	*path += i;
	return (cmd);
}

char	*get_path(char *exec, t_env_lst *env)
{
	char	*path;
	char	*cmd;
	int		fd;

	while (env && ft_strncmp("PATH", env->name, 4))
		env = env->next;
	fd = -1;
	path = env->value;
	cmd = path;
	while (fd < 0 && cmd)
	{
		cmd = extract_path(&path);
		if (cmd)
		{
			cmd = ft_strjoin_free(cmd, "/", 1);
			cmd = ft_strjoin_free(cmd, exec, 1);
		}
		fd = open(cmd, O_RDONLY);
		if (fd < 0)
			free(cmd);
	}
	close(fd);
	return (cmd);
}

/*void	exec_params(char **exec, char *temp, char *params)
{
	char *mem;

	if (params == NULL)
		*exec = temp;
	else
	{
		mem = ft_strjoin(temp, " ");
		*exec = ft_strjoin(mem, params);
		free(mem);
	}
}*/

char **create_extab(char **params, char *exec)
{
	int count;
	int i;
	int j;
	char **str;

	count = double_tab_length(params);
	i = 0;
	j = 0;
	if(!(str = ft_calloc(count + 2, sizeof(char *))))
		return (NULL);
	if(i == 0)
		str[i++] = exec;
	while (params && params[j])
		str[i++] = params[j++];
	str[i++] = NULL;
	return (str);
}

void	ft_exec(char *exec, char **params, t_data *data)
{
	char	**argv;
	char	*path;

	path = NULL;
	errno = 0;
	if (*exec != '/' && *exec != '.')
		path = get_path(exec, data->env_var);
	argv = create_extab(params, path);
	execve(argv[0], argv, data->env);
	if (errno != 0)
	{
		ft_putstr_fd("Minishell: ", 1);
		write(1, exec, ft_strlen(exec));
		ft_putstr_fd(": command not found\n", 1);
	}
	free_exec(exec, path, 0, argv);
	exit(1);
}
