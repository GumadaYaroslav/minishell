#include "minishell.h"

/*
**	@brief	Inicialises main structure. Saves envp to new list.
**			Splits the builtins string
*/
void	inicialise_struct(t_msh *msh, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	msh->lst_env = NULL;
	while (*envp)
		ft_lstadd_front(&msh->lst_env, ft_lstnew(ft_strdup(*envp++)));
	msh->env = ft_lst_get_array(msh->lst_env);
	msh->builtin = ft_split(BUILTINS, ':');
	msh->cmnd = NULL;
	msh->status = 0;
}

/*
**	@brief	Frees memory after last commands string.
**			Update last error status
**	
**	@param	main structure
**	@param	last writen string
*/
void	cleaning(t_msh *msh, char *str)
{
	free(str);
	ft_lstclear_cmnds(&msh->lst_cmnd);
	msh->old_status = msh->status;
	msh->status = 0;
}

/*
**	@brief	Clears command list
*/
void	ft_lstclear_cmnds(t_cmnd **cmnd)
{
	t_cmnd	*next;

	while (*cmnd)
	{
		next = (*cmnd)->next;
		ft_lstclear(&(*cmnd)->lst_arg);
		ft_lstclear(&(*cmnd)->redirects);
		if ((*cmnd)->arg)
			ft_split_free((*cmnd)->arg);
		(*cmnd)->arg = NULL;
		free(*cmnd);
		*cmnd = next;
	}
}