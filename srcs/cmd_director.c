#include "minishell.h"
#include "builtin.h"

int     cmd_director(t_cmd *list, t_data *data)
{

    while (list)
	{
        builtins(list->command, list->param, data);
		list = list->next;
	}
    return (data->status);
}