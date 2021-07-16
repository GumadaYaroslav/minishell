#include "minishell.h"

int	chdir_error(char *dir)
{
	ft_putstr_fd("minishell: cd:", 2);
	ft_putstr_fd(dir, 2);
	ft_putstr_fd(": ", 2);
	return (print_errno());
}

int	set_new_oldpwd(char *pwd_old, t_msh *msh)
{
	char	*argv[3];

	argv[0] = "export";
	argv[1] = ft_strjoin("OLDPWD=", pwd_old);
	argv[2] = NULL;
	return(ft_export(argv, msh));
}
