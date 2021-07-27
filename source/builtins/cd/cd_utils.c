#include "minishell.h"

int	chdir_error(char *dir)
{
	ft_putstr_fd("minishell: cd: ", 2);
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
	return (ft_export(argv, msh));
}

int	set_new_pwd(t_msh *msh)
{
	char	*argv[3];
	char	*tmp;
	char	*pwd;

	tmp = ft_calloc(1024, 1);
	pwd = getcwd(tmp, 1024);
	if (pwd == NULL)
	{
		free(tmp);
		return (print_errno());
	}
	argv[0] = "export";
	argv[1] = ft_strjoin("PWD=", pwd);
	argv[2] = NULL;
	free(tmp);
	return (ft_export(argv, msh));
}
