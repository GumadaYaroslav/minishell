#include "minishell.h"

void	run_command(t_msh *msh, t_cmnd *cmnd)
{
	char	**paths;
	char	*name;

	if (!cmnd->lst_arg)
		exit (0);
	paths = get_splited_path(msh);
	name = cmnd->arg[0];
	while (gen_next_path(cmnd->arg, paths, name))
	{
		execve(cmnd->arg[0], cmnd->arg, msh->env);
		if (errno != 2)
			ft_critical_error(0, name);
	}
	ft_critical_error(ft_strjoin("msh: ", ft_strjoin("Command not found: ", name)), 0);
}

void	run_builtin(t_msh *msh, t_cmnd *cmnd, char *name)
{
	if (!ft_strncmp(name, "echo", ft_strlen(name)))
		; // add your funcs
	else if (!ft_strncmp(name, "cd", ft_strlen(name)))
		;
	else if (!ft_strncmp(name, "pwd", ft_strlen(name)))
		;
	else if (!ft_strncmp(name, "export", ft_strlen(name)))
		;
	else if (!ft_strncmp(name, "unset", ft_strlen(name)))
		;
	else if (!ft_strncmp(name, "env", ft_strlen(name)))
		;
	else if (!ft_strncmp(name, "exit", ft_strlen(name)))
		;
	else
		ft_putendl_fd("Impossible!", 2);
}


/*
**	@brief	Checks the name program is the builtin
*/
int	is_builtin(t_msh *msh, char *name)
{
	size_t	i;

	if (!name)
		return (false);
	i = 0;
	while (msh->builtin[i])
		if (!ft_strncmp(msh->builtin[i++], name, ft_strlen(name)))
			return (true);
	return (false);
}
