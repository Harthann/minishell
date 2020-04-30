#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	print_cmd(t_cmd *list)
{
	while (list)
	{
		printf("command : %s\n", list->command);
		printf("param : %s\n", list->param);
		list = list->next;
	}
}
