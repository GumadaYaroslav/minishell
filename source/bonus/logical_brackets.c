/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_brackets.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alchrist <alchrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 16:34:20 by alchrist          #+#    #+#             */
/*   Updated: 2021/08/07 12:51:04 by alchrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_brackets(char *s, bool open_bracket)
{
	int		cmnd_cond;

	cmnd_cond = 0;
    while (*s && *s != ')')
	{
		if (ft_ch_in_str(*s, "'\""))
			s = ft_pass_comma(s);
		else
		{
			s = check_brackets_p2(s, open_bracket, &cmnd_cond);
			if (!s)
				return (s);
		}
	}
	if ((open_bracket && *s != ')') || (!open_bracket && *s == ')'))
		return (ft_error_token(ft_strjoin(ERR_TKN, "(")));
	if (cmnd_cond == 2 || (open_bracket && cmnd_cond == 0))
		return (ft_error_token(ft_strjoin(ERR_TKN, ")")));
	return (s);
}


char	*check_brackets_p2(char *s, bool open_bracket, int *cmnd_cond)
{
	if (ft_isalnum(*s))
		*cmnd_cond = 1;
	else if (!ft_strncmp(s, "||", 2) || !ft_strncmp(s, "&&", 2))
	{
		if (*cmnd_cond != 1)
			return (ft_error_token(ft_strjoin(ERR_TKN, s)));
		else
			*cmnd_cond = 2;
		s++;
	}
	else if (*s == '(' && open_bracket && *cmnd_cond == 1)
		return (ft_error_token(ft_strjoin(ERR_TKN, s)));
	else if (*s == '(')
	{
		s = check_brackets(s + 1, true);
		*cmnd_cond = 1;
		if (!s || !*s)
			return (NULL);
	}
	s++;
	return (s);
}