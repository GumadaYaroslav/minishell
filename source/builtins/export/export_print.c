/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alchrist <alchrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 19:09:30 by alchrist          #+#    #+#             */
/*   Updated: 2021/08/02 19:09:31 by alchrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_put_str_until_chr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		write(1, &str[i], 1);
		i++;
	}
}

static void	ft_put_str_after_chr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i])
	{
		i++;
		ft_putstr_fd(&str[i], 1);
	}
}

void	print_export(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_put_str_until_chr(env[i], '=');
		if (ft_strrchr(env[i], '='))
		{
			write(1, "=", 1);
			write(1, "\"", 1);
			ft_put_str_after_chr(env[i], '=');
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
}
