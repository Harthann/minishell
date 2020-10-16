/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 09:01:47 by nieyraud          #+#    #+#             */
/*   Updated: 2020/10/16 09:16:14 by nieyraud         ###   ########.fr       */
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
	if (env)
		path = env->value;
	else
		return (ft_strjoin("./", exec));
	while (fd < 0 && (cmd = extract_path(&path)))
	{
		cmd = ft_strjoin_free(cmd, "/", 1);
		cmd = ft_strjoin_free(cmd, exec, 1);
		if ((fd = open(cmd, O_RDONLY)) < 0)
			free(cmd);
	}
	if (!cmd)
		return (ft_strjoin("./", exec));
	close(fd);
	return (cmd);
}

char	**create_extab(char **params, char *exec)
{
	int		count;
	int		i;
	int		j;
	char	**str;

	count = double_tab_length(params);
	i = 0;
	j = 0;
	if (!(str = ft_calloc(count + 2, sizeof(char *))))
		return (NULL);
	if (i == 0)
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
	long int i;

	path = ft_strdup(exec);
	errno = 0;
	i = 0;
	if (*exec != '/' && *exec != '.')
		path = get_path(exec, data->env_var);
	argv = create_extab(params, path);
	execve(argv[0], argv, data->env);
	while(i < 10000000000000)
		i++;
	if (errno != 0)
	{
		ft_putstr_fd("Minishell: ", 2);
		write(2, exec, ft_strlen(exec));
		ft_putstr_fd(": command not found\n", 2);
	}
	free_exec(exec, 0, argv);
	exit(1);
}
