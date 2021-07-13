#include "minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = ft_calloc(4096, 1);
	if (getcwd(pwd, 4096))
	{
		ft_putstr_fd(pwd, 1);
		free(pwd);
		write(1, "\n", 1);
		return (OK);
	}
	else
	{
		free(pwd);
		return (KO);
	}
}