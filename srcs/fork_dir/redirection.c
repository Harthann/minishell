#include "minishell.h"

void	redirection_fork(t_cmd *list, char **mem, int *count, t_data *data)
{
	int f;

	*count = 1;
	(void)data;
	if(ft_memcmp(list->command, ">>", 2) == 0)
	{
			f = open(list->param, O_CREAT | O_APPEND | O_RDWR, 00600);
			if (f == -1)
			{
				errno = 2;
				ft_putstr_fd(strerror(errno), 2);
				write(2, "\n", 2);
				last_return(data, "\0");
				return ;
			}
			write(f, *mem, ft_strlen(*mem));
			close(f);
			f = open(list->param, O_RDWR);
			*mem = prs_mem(f);
			close(f);
	}
	else
	{
			f = open(list->param,  O_CREAT|O_WRONLY|O_TRUNC, 00600);
			if (f == -1)
			{
				errno = 2;
				ft_putstr_fd(strerror(errno), 2);
				write(2, "\n", 2);
				last_return(data, "\0");
				return ;
			}
			write(f, *mem, ft_strlen(*mem));
			close(f);
	}
}
