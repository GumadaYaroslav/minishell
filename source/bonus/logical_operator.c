/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alchrist <alchrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 16:34:20 by alchrist          #+#    #+#             */
/*   Updated: 2021/08/08 13:40:52 by alchrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	logical_condition(t_msh *msh, char *str)
{
	msh->cond_and = true;
	msh->cond_status = 0;
	if (check_brackets(str, 0))
	{
		run_brackets(msh, str, 0);
	}
	else
		g_status = 2;
	printod(str, g_status);
	if (!strncmp(str, "exit", 4))
		exit(msh->old_status);
}

void	run_brackets(t_msh *msh, char *s, bool open_bracket)
{
	size_t	i;
	int		cmnd_cond;

	i = 0;
	while (s[i] && s[i] != ')')
	{
		if (ft_ch_in_str(s[i], "'\""))
			i += ft_pass_before(s + i);
		else if (!ft_strncmp(s + i, "||", 2) || !ft_strncmp(s + i, "&&", 2))
			msh->cond_and = ft_strncmp(s + i++, "||", 2);
		i++;
	}
}
