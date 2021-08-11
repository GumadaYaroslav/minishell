/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alchrist <alchrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 19:12:01 by alchrist          #+#    #+#             */
/*   Updated: 2021/08/11 22:02:12 by alchrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**		@brief		parsing and get value  from string, started by $				
*/
char	*parsing_dollar(t_msh *msh, char *s, size_t *i)
{
	char	*key;
	char	*value;

	(*i)++;
	if (s[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(msh->old_status));
	}
	if (ft_ch_in_str(s[(*i)], " <>|$'\"\n="))
		return (ft_strdup("$"));
	key = get_key(ft_isdigit(s[*i]), s, i);
	value = get_value_from_envp(msh, key);
	free(key);
	return (value);
}

/*
**		@brief	add the non empty enviroment value to chars list
*/
void	ft_add_env_or_no(t_list	**chars, char *env_val)
{
	if (*env_val)
		ft_lstadd_back(chars, ft_lstnew(env_val));
	else
		free(env_val);
}
