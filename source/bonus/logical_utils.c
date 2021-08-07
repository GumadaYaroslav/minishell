/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alchrist <alchrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 16:34:20 by alchrist          #+#    #+#             */
/*   Updated: 2021/08/07 12:53:53 by alchrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pass_comma(char *s)
{
	char	comma;
	
	comma = *s;
	while (*s && *s != comma)
		s++;
	if (*s)
		s++;
	return (s);
}

size_t	ft_pass_comma_ind(char *s)
{
	size_t	i;

	i = 1;
	while (s[i] && s[i] != s[0])
		i++;
	if (s[i])
		i++;
	return (i);
}