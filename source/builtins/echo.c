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

int	ft_echo(t_msh *msh, char **argv, char **env)
{
	int	i;
	int	flag;

	(void)env;
	(void)msh;
	i = 1;
	flag = 1;
	
	// printf("%s\n", argv[3]);
	// printf("%s\n", argv[2]);
	// printf("%s\n", argv[1]);
	if (argv[1])
	{
		if (ft_strcmp(argv[1], "-n") == 0)
			flag = 0;
		while (argv[i])
		{
			if (ft_strcmp(argv[i], "-n") != 0)
			{
				ft_putstr_fd(argv[i], 1);
				if (argv[i + 1] && ft_strlen(argv[i]) != 0 && ft_strlen(argv[i + 1]))
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