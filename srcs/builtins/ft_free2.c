#include "minishell.h"

void	free_datas(t_cmd **alst, t_data *data, int *fd)
{
	free(data->line);
        free_lst(&(data->env_var));
        free_cmd(alst);
        free(fd);
	free(data);
}
