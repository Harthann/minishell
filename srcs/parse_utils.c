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
	char *to_free;

	tmp = *list;
	to_free = new->command;
	new->command = ft_strtrim(to_free, " ");
	free(to_free);
	to_free = new->param;
	new->param = ft_strtrim(to_free, " ");
	free(to_free);
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (*list)
		tmp->next = new;
	else
		*list = new;
}
