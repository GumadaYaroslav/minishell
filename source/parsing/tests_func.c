/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alchrist <alchrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 19:12:06 by alchrist          #+#    #+#             */
/*   Updated: 2021/08/02 19:12:07 by alchrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_print_arr(char **arr)
{
	if (!DEBUG)
		return ;
	for (size_t i = 0; arr[i]; i++)
		printf("%zu: %s\n", i, arr[i]);
}

void	test_print_lst(t_list *lst)
{
	if (!DEBUG)
		return ;
	for (int i = 0; lst; i++, lst=lst->next)
		printf("|%s| ", lst->val);
	printf("\n");
}

void	test_print_command(t_cmnd *cmnd)
{
	size_t i;
	
	if (!DEBUG)
		return ;
	i = 0;
	ft_putstr_fd(BLUE, 1);
	while (cmnd)
	{
		i++;
		printf("------%4zu ------\nCOMMANDS: ", i);
		test_print_lst(cmnd->lst_arg);
		printf("REDIRECTS: ");
		test_print_lst(cmnd->redirects);
		cmnd = cmnd->next;
	}
	printf("\n");
	ft_putstr_fd(STND, 1);
}

void	printos(char *msg, char *str)
{
	if (DEBUG)
	{
		ft_putstr_fd(BLUE, 2);
		if (msg)
		{
			ft_putstr_fd(msg, 2);
			ft_putstr_fd(": ", 2);
		}
		ft_putendl_fd(str, 2);
		ft_putstr_fd(STND, 2);
	}
}

void	printod(char *msg, int x)
{
	if (DEBUG)
	{
		ft_putstr_fd(BLUE, 2);
		if (msg)
		{
			ft_putstr_fd(msg, 2);
			ft_putstr_fd(": ", 2);
		}
		ft_putnbr_fd(x, 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd(STND, 2);
	}
}
