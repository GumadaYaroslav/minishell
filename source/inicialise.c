/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inicialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alchrist <alchrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 19:12:32 by alchrist          #+#    #+#             */
/*   Updated: 2021/08/08 15:26:52 by alchrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	g_status = 0;
	save_stnd_io(msh);
	restore_stnd_io(msh);
}

/*
**		@brief		increase SHLVL from enviroments
*/
void	update_shlvl(t_msh *msh)
{
	char	*shlvl;
	char	*temp_lvl;
	char	*new_shlvl;

	shlvl = get_value_from_envp(msh, "SHLVL");
	temp_lvl = ft_itoa(ft_atoi(shlvl) + 1);
	new_shlvl = ft_strjoin("SHLVL=", temp_lvl);
	insert_or_update_elem_from_envp(msh, new_shlvl);
	free(shlvl);
	free(temp_lvl);
	free(new_shlvl);
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
	if (msh->lst_cmnd)
		ft_lstclear_cmnds(&msh->lst_cmnd);
	if (ft_strlen(str))
		msh->old_status = g_status;
	g_status = 0;
	free(str);
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
