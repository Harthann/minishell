#include "minishell.h"

void	p_init(int pnum, p_info *p)
{
	p->end_pass = 0;
	p->pcount = 0;
	p->pnum = pnum;
}

int		pnum_l(t_cmd *list)
{
	int count;

	count = 0;
	while (list)
	{
		if(ft_memcmp(list->command, "|", 2) == 0)
			count++;
		list = list->next;
	}
	return (count * 2);
}

void	main_fork(t_cmd **list, t_data *data)
{
	int fdpipe[pnum_l(*list)];
	p_info p;
	int status;
	t_cmd *lst;
	int i;

	p_init(pnum_l(*list), &p);
	lst = *list;
	i = 0;
	while(i < p.pnum)
	{
		pipe(fdpipe + i);
		i = i + 2;
	}
	while(lst)
	{
		if(p.pcount == 0 || ft_memcmp(lst->command, "|", 2) == 0)
		{
			if(fork() == 0)
				do_builtin(p, fdpipe, lst, data);
			p.pcount += 1;
		}
		lst = lst->next;
	}
	i = 0;
	while(i < p.pnum)
		close(fdpipe[i++]);
	while((wait(&status)) > 0);
	if(status != 0)
		data->last_return = 127;
	else
		data->last_return = 0;
	*list = lst;
}
