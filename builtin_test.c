#include "include/minishell.h"
#include <stdio.h>
int main ()
{
	t_env_lst	*lst;
	t_data		*data;
	lst = 0;
	data = ft_calloc(1, sizeof(t_data));
	data->res_prev_cmd = NULL;
//	ft_addenv(&lst, ft_envnew("USER", "stbaleba"));
//	ft_addenv(&lst, ft_envnew("ADD", "bobo"));
//	ft_addenv(&lst, ft_envnew("NEW", "form"));

//	ft_delenv(&lst, "ADD");
	data->env_var = lst;
//	builtins("echo -n", "Hello_World", data);
//printf("data_res : %s\n", data->res_prev_cmd);
//	builtins("pwd", NULL, data);
//printf("data_res : %s\n", data->res_prev_cmd);
/*	builtins("cd", "/home", data);
	builtins("env",  NULL, data);
	builtins("export",  "USER=stbaleba", data);

	builtins("export",  "BB=5", data);
	builtins("env",  NULL, data);
	builtins("unset",  "BB", data);
	builtins("env",  NULL, data);
	builtins("exit",  NULL, data); */
 char *argv[] = { "/bin/cat", "builtin_test.c", 0};
    char *envp[] =
    {
        0
    };
    execve(argv[0], &argv[0], envp);
	perror("execve");
/*	builtins("echo", "Hello World ", data);
	builtins("echo", "Hello\"World\" ", data);
	builtins("echo", "'Hello'World", data);
	builtins("echo", "Hello 'World' \"dddsd\"", data);
	builtins("echo", "Hello \"$USER\"", data);
	builtins("echo", "Hello\"$USER\" |", data);
	builtins("echo", "Hello '$USER'", data);
	builtins("echo", "Hello'$USER' |", data);

	builtins("echo", "Hello$USER|", data);
	builtins("echo", "$USER", data);
	builtins("echo -n", "Hello \"$USER\"", data);
	builtins("echo -n", "Hello\"$USER\" |", data);
	builtins("echo -n", "Hello '$USER'", data);
	builtins("echo -n", "Hello'$USER' |", data); */

}
