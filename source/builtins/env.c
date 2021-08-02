/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alchrist <alchrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 19:10:34 by alchrist          #+#    #+#             */
/*   Updated: 2021/08/02 19:10:36 by alchrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **argv, char **env, t_msh *msh)
{
	t_list	*inv;

	inv = msh->lst_env;
	(void)argv;
	(void)env;
	while (inv->next)
	{
		if (ft_strrchr(inv->val, '='))
		{
			ft_putstr_fd(inv->val, 1);
			ft_putstr_fd("\n", 1);
		}
		inv = inv->next;
	}
	if (ft_strrchr(inv->val, '='))
	{
		ft_putstr_fd(inv->val, 1);
		ft_putstr_fd("\n", 1);
	}
	return (0);
}
