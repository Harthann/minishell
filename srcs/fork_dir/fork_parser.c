#include "minishell.h"

int		ft_separate(char *command)
{
	if(command == NULL)
		return (0);
	else if (ft_memcmp(command, ">", 1) == 0)
		return (1);
	else if (ft_memcmp(command, ">>", 2) == 0)
		return (1);
	else if (ft_memcmp(command, "<", 1) == 0)
		return (1);
	else
		return (0);
}




int		fork_parsing(t_cmd *list, t_data *data, int *count)
{
	char	*params_mem;
	int		res;
//(void)data;
	res = 1;
	params_mem = NULL;
	while(res == 1 && list)
	{
		if(left_redir(list->next) == 1)
		{
			reverse_red_fork(list, data, &params_mem);
			res = 0;
			*count += 2;
//			break;
			list = list->next;
			list = list->next;
		}
		else
		{
			normal_fork(list, data, &params_mem);
			list = list->next;
			*count += 1;
		}
//		printf("[%s]\n", params_mem);
		if(right_redir(list) == 1)
		{
				redirection_fork(list, &params_mem);
				list = list->next;
				*count += 1;
				printf("[%s]\n", params_mem);
				if(!list)
					break;
		}
		if (!list || ft_separate(list->command) == 0)
		{
			ft_putstr_fd(params_mem, 1);
			res = 0;
		}
	//	res = 0;
	}
	free(params_mem);
//	printf("[%s]\n", params_mem);
	return (*count);
}
