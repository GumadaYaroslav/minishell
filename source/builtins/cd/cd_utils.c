/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alchrist <alchrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 19:09:13 by alchrist          #+#    #+#             */
/*   Updated: 2021/08/02 19:09:20 by alchrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chdir_error(char *dir)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(dir, 2);
	ft_putstr_fd(": ", 2);
	return (print_errno());
}

int	set_new_oldpwd(char *pwd_old, t_msh *msh)
{
	char	*pwd;

	pwd = ft_strjoin("OLDPWD=", pwd_old);
	insert_or_update_elem_from_envp(msh, pwd);
	free(pwd);
	return (0);
}

int	set_new_pwd(t_msh *msh)
{
	char	*new_pwd;
	char	*tmp;
	char	*pwd;

	tmp = ft_malloc_x(1024);
	pwd = getcwd(tmp, 1024);
	if (pwd == NULL)
	{
		free(tmp);
		return (print_errno());
	}
	new_pwd = ft_strjoin("PWD=", pwd);
	insert_or_update_elem_from_envp(msh, new_pwd);
	free(new_pwd);
	free(tmp);
	return (0);
}
