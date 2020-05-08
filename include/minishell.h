/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blacking <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 15:51:08 by blacking          #+#    #+#             */
/*   Updated: 2020/05/08 16:31:00 by blacking         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "builtin.h"
# include "get_next_line.h"
# include <sys/wait.h>
typedef struct	s_all
{
	int status;
}		t_all;

typedef struct s_quote
{
	int dquote;
	int quote;
}		t_quote;

typedef struct s_cmd
{
	char	*command;
	char	*param;
	void	*next;
}		t_cmd;


int		ft_command_parser(char *str, t_data *data);
void	print_cmd(t_cmd *list);
int		cmd_director(t_cmd *list, t_data *data);
int		is_separator(char c, t_quote quote);
void	add_back(t_cmd **list, t_cmd *new);

t_env_lst	*ft_envnew(char *name, char *value);
void		ft_addenv(t_env_lst **alst, t_env_lst *new);
void		ft_delenv(t_env_lst **alst, char *name);
void		builtins(char *command, char *params, t_data *data);
char		**clean_params(char *params, t_env_lst *lst, t_data *data);
char		*env_value(char *str, int index, t_env_lst *lst);
char		*env_value2(char *str, t_env_lst *lst);
char		*ft_quote(char *params, int index, t_env_lst *lst);
void		ft_echo(char *command, char **params_cl, t_data *data);
void		ft_putstr(char *str);
void		pwd(t_data *data);
void		cd(char **params_cl);
void		env_list(t_data *data);
void		display(char *str, t_data *data);
void		add_env(char *str, t_data *data);
void		ft_free(t_data *data, char **params_cl);
void		ft_exec(char *exec, t_data *data);
void		init_env(t_data *data, char **env);
int			fork_parsing(t_cmd *list, t_data *data, int *count);
char		*prs_mem(int fd);
int			left_redir(t_cmd *list);
int			right_redir(t_cmd *list);
void		normal_fork(t_cmd *lst, t_data *data, char **mem);
void		reverse_red_fork(t_cmd *list, t_data *data, char **mem);
void		redirection_fork(t_cmd *list, char **mem);

#endif
