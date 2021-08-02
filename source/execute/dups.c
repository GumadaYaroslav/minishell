/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alchrist <alchrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 19:11:02 by alchrist          #+#    #+#             */
/*   Updated: 2021/08/02 19:11:03 by alchrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	@brief	save standart input/output
**	
**	@param	msh		
*/
void	save_stnd_io(t_msh *msh)
{
	msh->old_in = dup(STDIN);
	msh->old_out = dup(STDOUT);
	if (msh->old_in < 0 || msh->old_out < 0)
		ft_raise_error(0, 0);
}

/*
**	@brief	restore standart input/output	
**	
**	@param	msh	main structure
*/
void	restore_stnd_io(t_msh *msh)
{
	close(STDIN);
	close(STDOUT);
	if (dup2(msh->old_in, STDIN) < 0)
		ft_raise_error(0, 0);
	if (dup2(msh->old_out, STDOUT) < 0)
		ft_raise_error(0, 0);
	close(msh->old_in);
	close(msh->old_out);
}

/*
**	@brief	replace standart inputs/outputs 
**			to opens fd for command (pipe or files)
**	
**	@param	msh		main structure
**	@param	cmnd	command	
*/
void	dups_input_output(t_cmnd *cmnd)
{
	if (cmnd->in != STDIN)
	{
		if (dup2(cmnd->in, STDIN) < 0)
		{
			if (cmnd->is_fork)
				ft_critical_error(0, 0);
			return (ft_raise_error(0, 0));
		}
		close(cmnd->in);
	}
	if (cmnd->out != STDOUT)
	{
		if (dup2(cmnd->out, STDOUT) < 0)
		{
			if (cmnd->is_fork)
				ft_critical_error(0, 0);
			return (ft_raise_error(0, 0));
		}
		close(cmnd->out);
	}
}
