#include "minishell.h"

t_list	*ft_split_to_list(char **env)
{
	t_list *env_list;
	int		i;

	i = 1;
	env_list = ft_lstnew(env[0]);
	while (env[i])
	{
		ft_lstadd_back(&env_list, ft_lstnew(env[i]));
		i++;
	}
	return (env_list);
}

void	ft_swap_str(void **p1, void **p2)
{
	char *tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

int	my_str_cmp(void *s1, void *s2)
{
	char	*one;
	char	*two;
	int		i;

	one = (char *)s1;
	two = (char *)s2;
	i = 0;
	while (one[i] == two[i] && two[i] && one[i])
		i++;
	if (one[i] == two[i])
		return (0);
	return (one[i] - two[i]);
}

void	sort_the_env(t_msh *msh, int len_env)
{
	int		i;
	int 	j;
	char	*tmp;

	i = 0;
	while (i < len_env)
	{
		j = 0;
		while (j < len_env - 1)
		{
			if (my_str_cmp(msh->env[j], msh->env[j + 1]) > 0)
			{
				tmp = msh->env[j];
				msh->env[j] = msh->env[j + 1];
				msh->env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static int ft_write_error_export(char *exp)
{
	write(2, "export: '", 10);
	write(2, exp, ft_strlen(exp));
	write(2, "': not a valid identifier\n", 26);
	return (1);
}

int check_export(char *exp)
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
	ft_putnbr_fd(i, 1);
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
	else if (elem  != NULL && flag == OK)
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
	return (0);
}