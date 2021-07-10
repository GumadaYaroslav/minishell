#include "minishell.h"

void	run_command(t_msh *msh, t_cmnd *cmnd)
{
	char	**paths;
	char	*name;

	if (!cmnd->lst_arg)
		return ;
	paths = get_splited_path(msh);
	name = cmnd->arg[0];
	while (gen_next_path(cmnd->arg, paths, name))
	{
		if (!access(cmnd->arg[0], F_OK)) // TODO! forbidden func!
		{
			if (!access(cmnd->arg[0], X_OK))
			{
				printos("Execve", cmnd->arg[0]);
				execve(cmnd->arg[0], cmnd->arg, msh->env);

			}
			break ;
		}
	}
	ft_critical_error(ft_strjoin("Command not found: ", name), 0);
}

void	run_builtin(t_msh *msh, t_cmnd *cmnd, char *name)
{
	if (!ft_strncmp(name, "echo", ft_strlen(name)))
		ft_echo(msh, cmnd->arg, msh->env); // add your funcs
	else if (!ft_strncmp(name, "cd", ft_strlen(name)))
		;
	else if (!ft_strncmp(name, "pwd", ft_strlen(name)))
		ft_pwd();
	else if (!ft_strncmp(name, "export", ft_strlen(name)))
		ft_export(cmnd->arg, msh);
	else if (!ft_strncmp(name, "unset", ft_strlen(name)))
		ft_unset(cmnd->arg, msh);
	else if (!ft_strncmp(name, "env", ft_strlen(name)))
		ft_env(cmnd->arg, msh->env, msh);
	else if (!ft_strncmp(name, "exit", ft_strlen(name)))
		ft_exit(cmnd->arg, msh);
	else
		ft_putendl_fd("Impossible!", 2);
}