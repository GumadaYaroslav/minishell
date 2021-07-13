#include "minishell.h"

/*
**	@brief	Inicialises main structure. Saves envp to new list.
**			Splits the builtins string. Increment SHLLVL.
*/
void	inicialise_struct(t_msh *msh, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	msh->lst_env = NULL;
	while (*envp)
		ft_lstadd_front(&msh->lst_env, ft_lstnew(ft_strdup(*envp++)));
	msh->env = ft_lst_get_array(msh->lst_env);
	update_shlvl(msh);
	msh->builtin = ft_split(BUILTINS, ':');
	msh->cmnd = NULL;
	msh->status = 0;
}

/*
**		@brief		increase SHLVL from enviroments
*/
void	update_shlvl(t_msh *msh)
{
	int		shlvl;
	char	*temp_lvl;
	char	*new_shlvl;

	shlvl = ft_atoi(get_value_from_envp(msh, "SHLVL"));
	temp_lvl = ft_itoa(++shlvl);
	new_shlvl = ft_strjoin("SHLVL=", temp_lvl);
	insert_or_update_elem_from_envp(msh, new_shlvl);
	free(temp_lvl);
	free(new_shlvl);
	printos(0, new_shlvl);
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