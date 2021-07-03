#include "minishell.h"

void	inicialise_struct(t_msh *msh, int argc, char **argv, char **envp)
{
	size_t	i;
	
	msh->lst_env = NULL;
	i = 0;
	while (envp[i])
		ft_lstadd_front(&msh->lst_env, ft_lstnew(ft_strdup(envp[i++])));
	msh->env = ft_lst_get_array(msh->lst_env);
	msh->cmnd = NULL;
}

char	*get_value_from_envp(t_msh *msh, char *key)
{
	t_list	*res;

	res = ft_lstfind(msh->lst_env, key);
	free(key);
	if (res)
		return (ft_strdup(res->val));
	else
		return (ft_strdup(""));
}