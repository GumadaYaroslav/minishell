#include "minishell.h"

static int	home_not_set(void)
{
	ft_putstr_fd("minishell: cd : HOME not set \n", 2);
	return (1);
}

int ft_cd(char **argv, t_msh *msh)
{
	char	*home;
	int		r_vel;

	if (ft_split_len(argv) > 2)
	{
		ft_putstr_fd("minishell: cd: to many arguments\n", 2);
		return (1);
	}
	if (ft_split_len(argv) == 1)
	{
		home = get_value_from_envp(msh, "HOME");
		if (home[0] == '\0')
			return (home_not_set);
		
	}		
}