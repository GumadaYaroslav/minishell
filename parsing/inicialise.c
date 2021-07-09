#include "minishell.h"

void	inicialise_struct(t_msh *msh, int argc, char **argv, char **envp)
{
	size_t	i;
	
	(void)argc;
	(void)argv;
	msh->lst_env = NULL;
	i = 0;
	while (envp[i])
		ft_lstadd_front(&msh->lst_env, ft_lstnew(ft_strdup(envp[i++])));
	msh->env = ft_lst_get_array(msh->lst_env);
	msh->builtin = ft_split(BUILTINS, ':');
	msh->cmnd = NULL;

}

int	is_builtin(t_msh *msh, char *name)
{
	size_t	i;

	if (!name)
		return (false);
	i = 0;
	while (msh->builtin[i])
		if (!ft_strncmp(msh->builtin[i], name, ft_strlen(name)))
			return (true);
	return (false);
}