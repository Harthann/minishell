#include "minishell.h"

int		fork_parsing(t_cmd *list, t_data *data, int *count)
{
	char	*params_mem;
	int		res;
//(void)data;
	res = 1;
	while(res == 1 && list)
	{
		printf("error\n");
		params_mem = normal_fork(list, data);
		printf("success\n");
		list = list->next;
		*count += 1;
		res = 0;
	}
	printf("[%s]\n", params_mem);
	return (*count);
}
