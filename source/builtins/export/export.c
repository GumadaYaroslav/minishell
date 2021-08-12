/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alchrist <alchrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 19:09:39 by alchrist          #+#    #+#             */
/*   Updated: 2021/08/02 19:09:40 by alchrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_export(char *exp)
{
	int	i;

	i = 0;
	if (exp[0] == '=' || ft_isdigit(exp[0]) || !ft_isalpha(exp[0]))
		return (ft_write_error_export(exp));
	while (exp[i] && exp[i] != '=')
	{
		if (!ft_isalpha(exp[i]) && !ft_isdigit(exp[i]))
			return (ft_write_error_export(exp));
		i++;
	}
	return (0);
}

char	*ft_strdub_chr(char *str, char c, int *flag)
{
	char	*new_str;
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] != '=')
		*flag = 0;
	new_str = ft_calloc(i + 1, sizeof(char));
	if (new_str == NULL)
		exit(errno);
	i = 0;
	while (str[i] && str[i] != c)
	{
		new_str[i] = str[i];
		i++;
	}
	return (new_str);
}

int	ft_export(char **argv, t_msh *msh)
{
	int	i;
	int	ret_vel;

	i = 1;
	ret_vel = 0;
	if (ft_split_len(argv) == 1)
	{
		sort_the_env(msh, ft_split_len(msh->env));
		print_export(msh->env);
		return (ret_vel);
	}
	while (argv[i])
	{
		if (!check_export(argv[i]))
			insert_or_update_elem_from_envp(msh, argv[i]);
		else
			ret_vel = 1;
		i++;
	}
	return (ret_vel);
}
