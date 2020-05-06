#include "minishell.h"

int	is_separator(char c, t_quote quote)
{
	if ((c == ';' || c == '<' || c == '|' || c == '>')
		&& !quote.quote && !quote.dquote)
		return (1);
	return (0);
}

void	add_back(t_cmd **list, t_cmd *new)
{
	t_cmd *tmp;

	tmp = *list;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (*list)
		tmp->next = new;
	else
		*list = new;
}
