/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alchrist <alchrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 19:10:02 by alchrist          #+#    #+#             */
/*   Updated: 2021/08/02 19:10:02 by alchrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_msh *msh, char **ar, char **env)
{
	int	i;
	int	flag;

	(void)env;
	(void)msh;
	i = 1;
	flag = 1;
	if (ar[1])
	{
		if (ft_strcmp(ar[1], "-n") == 0)
			flag = 0;
		while (ar[i])
		{
			if (ft_strcmp(ar[i], "-n") != 0)
			{
				ft_putstr_fd(ar[i], 1);
				if (ar[i + 1] && ft_strlen(ar[i + 1]))
					write(1, " ", 1);
			}
			i++;
		}
	}
	if (flag)
		write(1, "\n", 1);
	return (0);
}

// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	ft_echo(NULL, argv, NULL);
// 	return (1);
// }