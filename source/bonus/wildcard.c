/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alchrist <alchrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 16:34:20 by alchrist          #+#    #+#             */
/*   Updated: 2021/08/08 16:19:11 by alchrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**		@brief		gets filenames by wildcard mask for current directory	
*/
void	wildcard(t_msh *msh, char *wilds)
{
	char	*path;
	DIR		*dirp;

	path = getcwd(0, 1024);
	if (!path)
	{
		ft_raise_error(0, 0);
		return ;
	}
	dirp = opendir(path);
	free (path);
	if (!dirp)
	{
		ft_raise_error(0, 0);
		return ;
	}
	get_and_check_files(msh, dirp, wilds);
	free (wilds);
	closedir(dirp);
}

/*
**		@brief		Gets and addes to list arguments filenames
**					from current directory,	if their match to wildcard
*/
void	get_and_check_files(t_msh *msh, DIR *dirp, char *wilds)
{
	struct dirent	*f;
	bool			found_files;

	found_files = false;
	while (true)
	{
		f = readdir(dirp);
		if (!f)
			break ;
		if ((f->d_name[0] != '.' || wilds[0] == '.')
			&& (name_eq_wildcard(f->d_name, wilds)))
		{
			found_files = true;
			ft_lstadd_front(&msh->cmnd->lst_arg,
				ft_lstnew(ft_strdup(f->d_name)));
		}
	}
	if (!found_files)
		ft_lstadd_front(&msh->cmnd->lst_arg, ft_lstnew(ft_strdup(wilds)));
}

/*
**		@brief		recursive checks if the name matches the wildcard		
**		@return		1 if equals, else 0;		
*/
int	name_eq_wildcard(char *name, char *wilds)
{
	while (*name && *wilds == '*')
	{
		if (*name == *(wilds + 1))
			if (name_eq_wildcard(name, wilds + 1))
				return (1);
		name++;
	}
	if (*wilds == '*')
		wilds++;
	while (*name && *name == *wilds)
	{
		name++;
		wilds++;
	}
	if (!*name && !*wilds)
		return (1);
	if (*wilds == '*' && name_eq_wildcard(name, wilds))
		return (1);
	return (0);
}
