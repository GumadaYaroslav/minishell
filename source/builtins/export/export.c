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

t_list	*arr_to_list(char **arr, t_list *list)
{
	int	i;

	ft_lstclear(&list);
	i = 0;
	while(arr[i])
	{
		ft_lstadd_back(&list, ft_lstnew(arr[i]));
		i++;
	}
	return (list);
}

void	my_insert_or_update_elem_from_envp(t_msh *msh, char *argv)
{
	char	*s;
	int		flag;
	t_list	*elem;

	flag = OK;
	s = ft_strdub_chr(argv, '=', &flag);
	elem = ft_lstfind(msh->lst_env, s);
	if (elem != NULL && flag == KO)
		return ;
	else if (elem != NULL && flag == OK)
	{
		free(elem->val);
		elem->val = ft_strdup(argv);
		if (elem->val == NULL)
			exit(errno);
	}
	else
		ft_lstadd_back(&msh->lst_env, ft_lstnew(argv));
	ft_split_free(msh->env);
	msh->env = ft_lst_get_array(msh->lst_env);
	free(s);
}

int	ft_export(char **argv, t_msh *msh)
{
	int	i;

	i = 1;
	if (ft_split_len(argv) == 1)
	{
		print_export(msh->env);
		return (0);
	}
	while (argv[i])
	{
		if (!check_export(argv[i]))
			my_insert_or_update_elem_from_envp(msh, argv[i]);
		i++;
	}
	sort_the_env(msh, ft_split_len(msh->env));
	print_export(msh->env);
	// msh->lst_env = arr_to_list(msh->env, msh->lst_env);
	return (0);
}
