/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blacking <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 15:51:08 by blacking          #+#    #+#             */
/*   Updated: 2020/04/19 14:41:21 by blacking         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

typedef struct  env_list
{
	char *name;
	char *value;
	struct env_list *next;
}				t_env_lst;

t_env_lst	*ft_envnew(char *name, char *value);
void		ft_addenv(t_env_lst **alst, t_env_lst *new);
void		ft_delenv(t_env_lst **alst, char *name);

#endif
