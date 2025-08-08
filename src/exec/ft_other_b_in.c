#include "../../include/minishell.h"

void	other_b_in(char *cmd, t_env *env)
{
	if (cmd[0] && ft_execve(cmd, env) == 0)
		ft_execve(cmd, env);
	ft_free_copy_envp(env);
	ft_del_all();
}
