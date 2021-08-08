/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raise_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alchrist <alchrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 19:12:39 by alchrist          #+#    #+#             */
/*   Updated: 2021/08/08 16:31:56 by alchrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	@brief	raises error message and exit from program
*/
void	ft_critical_error(char *msg, char *errno_msg, int err)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	else
		perror(errno_msg);
	if (err)
		exit (err);
	else if (errno)
		exit (errno);
	else
		exit(1);
}

/*
**	@brief	raises error message and change error code
*/
void	ft_raise_error(char *msg, char *errno_msg)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	else
		perror(errno_msg);
	if (errno)
		g_status = errno;
	else
		g_status = 1;
}

/*
**	@brief	raises error message and change error status to new code
*/
void	ft_raise_error_n(char *msg, int err_n)
{
	ft_putendl_fd(msg, 2);
	g_status = err_n;
}

int	print_errno(void)
{
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 2);
	return (errno);
}
