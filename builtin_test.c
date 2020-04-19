#include "include/minishell.h"
#include <stdio.h>
int main ()
{
	t_env_lst *lst;

	lst = 0;
	ft_addenv(&lst, ft_envnew("USER", "stbaleba"));
	ft_addenv(&lst, ft_envnew("ADD", "bobo"));
	ft_addenv(&lst, ft_envnew("NEW", "form"));

	ft_delenv(&lst, "ADD");
	while (lst)
	{
		printf("name : %s\n", lst->name);
		printf("value : %s\n", lst->value);
		lst = lst->next;
	}
}
