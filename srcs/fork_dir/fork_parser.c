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
		printf("error\n");
		normal_fork(list, data, &params_mem);
		printf("success\n");
		list = list->next;
		*count += 1;
		if (!list || ft_separate(list->command) == 0)
		{
			ft_putstr_fd(params_mem, 1);
			res = 0;
		}
	//	res = 0;
	}
//	printf("[%s]\n", params_mem);
	return (*count);
}
