#include "minishell.h"

void	redirection_fork(t_cmd *list, char **mem, int *count)
{
	int f;

	*count = 1;

	if(ft_memcmp(list->command, ">>", 2) == 0)
	{
			f = open(list->param, O_CREAT | O_APPEND | O_RDWR, 00600);
			write(f, *mem, ft_strlen(*mem));
			close(f);
			f = open(list->param, O_RDWR);
			*mem = prs_mem(f);
			close(f);
	}
	else
	{
			f = open(list->param,  O_CREAT|O_WRONLY|O_TRUNC, 00600);
			write(f, *mem, ft_strlen(*mem));
			close(f);
	}
}
