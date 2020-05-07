#include "minishell.h"

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
		res = 0;
	}
	printf("[%s]\n", params_mem);
	return (*count);
}
