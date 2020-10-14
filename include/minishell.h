/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nieyraud <nieyraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 15:51:08 by blacking          #+#    #+#             */
/*   Updated: 2020/10/14 15:23:48 by stbaleba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# define INT_MAX 2147483647

pid_t			g_fg_process;
int				g_fd;

typedef struct	s_cmd
{
	char	*command;
	char	**params;
	void	*next;
}				t_cmd;

typedef	struct	s_env_list
{
	char				*name;
	char				*value;
	struct s_env_list	*next;
}				t_env_lst;

typedef struct	s_data
{
	t_env_lst		*env_var;
	int				last_return;
	int				status;
	char			**env;
	int				red;
	unsigned char	exit_code;
}				t_data;

typedef struct	s_info
{
	int end_pass;
	int	pcount;
	int pnum;
}				t_info;
int				ft_command_parser(char *str, t_data *data);
void			print_cmd(t_cmd *list);
int				cmd_director(t_cmd *list, t_data *data);
int				is_separator(char *str, int start);
void			add_back(t_cmd **list, t_cmd *new);
void			sigquit_handler(int signal);
void			free_command(t_cmd **list);
char			*extract_quote(char *str, int *start);
char			*extract_dquote(char *str, int *start, t_data *data);
int				is_escape(char *str, int i);
char			*extract_param(char *str, int *start, t_data *data);
char			*extract_command(char *str, int *start, t_data *data);
char			*extract_dollar(char *str, int *start, t_data *data);

t_env_lst		*ft_envnew(char *name, char *value);
void			ft_addenv(t_env_lst **alst, t_env_lst *new);
void			ft_delenv(t_env_lst **alst, char **name);
void			builtins(char *command, char **params, t_data *data);
char			**clean_params(char *params, t_env_lst *lst, t_data *data);
char			*env_value(char *str, int index, t_env_lst *lst);
char			*env_value2(char *str, t_env_lst *lst);
char			*ft_quote(char *params, int index, t_env_lst *lst);
void			ft_echo(char **params_cl);
void			ft_putstr(char *str);
void			pwd(char *params);
void			cd(char **params_cl);
void			env_list(t_data *data, char *params);
void			display(char *str);
void			add_env(char **str, t_data *data);
void			ft_free(t_data *data, char **params, char *dest);
void			ft_exec(char *exec, char **params, t_data *data);
void			fork_parsing(t_cmd *list, t_data *data, int *count);
char			*prs_mem(int fd);
int				left_redir(t_cmd *list);
int				right_redir(t_cmd *list);
int				check_pipe(t_cmd *list);
void			normal_fork(t_cmd *lst, t_data *data, char **mem, int *count);
void			reverse_red_fork(t_cmd *list, t_data *data,
								char **mem, int *count);
void			redirection_fork(t_cmd *list, char **mem,
								int *count, t_data *data);
void			pipe_fork(t_cmd *list, t_data *data, char **mem, int *count);
void			error_child(int fd);
void			last_return(t_data *data, char *m);
int				length(char **params);
int				lst_size(t_data *data);
void			order_tab(char ***tab, int length);
char			*dollar_check(t_data *data, char *s, t_env_lst *lst, int index);
int				count_char(char *str);
char			*quote_check(char *s, t_env_lst *lst, int index);
int				count_quotechar(char *str, int index);
int				ft_error_fd(t_data *data, int fd);
void			free_exec(char *exec, char **env, char **argv);
void			free_builtin(char **params_cl);
int				env_exist(t_env_lst *lst, t_env_lst *new);
void			ft_delst(t_env_lst *lst, t_env_lst *prev_elem,
					t_env_lst *next_elem, t_env_lst *mem);
void			unset_export(t_cmd **list, t_data *data);
void			display_parse(t_cmd *list, t_data *data, int *count);
int				check_env(t_env_lst *lst);
int				check_char(char *str);
int				ft_memplus(char *name, char *cname);
int				double_tab_length(char **str);
void			main_fork(t_cmd **list, t_data *data);
void			do_builtin(t_info p, int *fdpipe, t_cmd *lst, t_data *data);
int				ft_redirect(t_cmd *lst, t_info *p);
int				ft_redirect2(t_cmd *lst);
int				check_unset_export(t_cmd *lst);
int				ft_free2(char **sr, int i);
#endif
