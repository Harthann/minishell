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
	free(exec);
	return (cmd);
}

void	ft_exec(char *exec, char *params, t_data *data)
{
	char **argv;
	char **env;
	char *mem;

//	if (*exec != '/')
//		exec = get_path(exec, data->env_var);
	mem = ft_strjoin(exec, " ");
	exec = ft_strjoin(mem, params);
	free(mem);
	argv = clean_params(exec, data->env_var, data);
	env = ft_calloc(1, sizeof(char *));
	execve(argv[0], &argv[0], env);
	perror("execve");
}
