#include "minishell.h"
#include "builtin.h"

int     cmd_director(t_cmd *list, t_data *data)
{
	int count;

	count = 0;
    while (list)
	{
		if(ft_memcmp(list->command, "exit", 5) == 0)
		{
	        builtins(list->command, list->param, data);
			count = 1;
		}
		else
        	fork_parsing(list, data, &count);
		while(count > 0 && list)
		{
			list = list->next;
			count--;
		}
    }
    return (data->status);
}
