#include "minishell.h"
#include "builtin.h"

int     cmd_director(t_cmd *list, t_data *data)
{

    while (list)
	{
//		printf("Command : [%s]\n", list->command);
//		printf("Parameter : [%s]\n", list->param);
        builtins(list->command, list->param, data);
		list = list->next;
    }
    return (data->status);
}
