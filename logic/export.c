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

void	sort_the_env(t_msh *msh, int len_env)
{
	int		i;
	int 	j;
	char	*tmp;

	i = 0;
	while (i < len_env)
	{
		j = 0;
		while (j < len_env -1)
		{
			if (ft_strcmp(msh->env[j], msh->env[j + 1]) > 0)
			{
				tmp = msh->env[j];
				msh->env[j] = msh->env[j + 1];
				msh->env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	// write(1, "2\n", 2);
	ft_lstclear(&msh->lst_env);
	// write(1, "2\n", 2);
	msh->lst_env = ft_split_to_list(msh->env);
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
	while (exp[i] && exp[i] != 0)
	{
		if (!ft_isalpha(exp[i]) && !ft_isdigit(exp[i]))
			return (ft_write_error_export(exp));
		i++;
	}
	return (0);
}

int	ft_export(char **argv, t_msh *msh)
{
	int	i;

	i = 1;
	if (ft_split_len(argv) == 1)
	{
		sort_the_env(msh, ft_split_len(msh->env));
		print_export(msh->env);
		return (0);
	}
	while (argv[i])
	{
		if (!check_export(argv[i]))
			insert_or_update_elem_from_envp(msh, argv[i]);
		i++;
	}
	sort_the_env(msh, ft_split_len(msh->env));
	return (0);
}