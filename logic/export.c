#include "minishell.h"

void	ft_put_str_until_chr(char *str, char c)
{
	int	i;

	i = 0;
	while(str[i] && str[i] != c)
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	print_export(char **env)
{
	int	i;
	int j;

	i = 0;
	while(env[i])
	{
		j = 0;
		ft_putstr_fd(1, "declare -x");
		ft_putstr_fd(1, ft_substr)

		i++;
	}
}

int	ft_export(char **argv, t_msh msh)
{
	
}