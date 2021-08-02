/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alchrist <alchrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 19:10:24 by alchrist          #+#    #+#             */
/*   Updated: 2021/08/02 19:10:26 by alchrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static u_int8_t	atoi_overflow(const char *str)
{
	int			i;
	int			minus;
	u_int64_t	num;

	i = 0;
	minus = 1;
	num = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while (str[i])
		num = (num * 10) + (str[i++] - '0');
	return (num * minus);
}

static int	is_not_num(char *argv)
{
	int	i;
	int	sign;

	sign = 0;
	i = 0;
	if (argv[i] == '+' || argv[i] == '-')
	{
		sign = 1;
		i++;
	}
	if ((int)ft_strlen(argv) > 21 + sign)
		return (1);
	while (argv[i])
	{
		if (ft_isdigit(argv[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

static	int	to_many_args(void)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd("too many arguments", 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

static int	exit_no_num_param(char *argv)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": numeric argument required", 2);
	ft_putstr_fd("\n", 2);
	exit(255);
	return (255);
}

int	ft_exit(char **argv, t_msh *msh)
{
	(void)msh;
	if (argv[1] == NULL)
		exit(msh->old_status);
	if (is_not_num(argv[1]))
		return (exit_no_num_param(argv[1]));
	if (ft_split_len(argv) > 2)
		return (to_many_args());
	else if (ft_split_len(argv) == 2)
		exit(atoi_overflow(argv[1]));
	return (0);
}
