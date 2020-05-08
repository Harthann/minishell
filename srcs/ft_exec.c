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
	}
	close(fd);
	return (cmd);
}

void	ft_exec(char *exec, t_data *data)
{
	char **argv;
	char **env;
	char *path;

	path = NULL;
	if (*exec != '/')
		path = get_path(exec, data->env_var);
	if (path)
		argv = clean_params(path, data->env_var, data);
	else
		argv = clean_params(exec, data->env_var, data);
	env = ft_calloc(1, sizeof(char *));
	execve(argv[0], &argv[0], env);
	perror(argv[0]);
	free(exec);
}
