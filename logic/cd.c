#include "minishell.h"

int	set_new_pwd(t_msh *msh)
{
	char	*argv[3];
	char	*pwd;

	pwd = getcwd(NULL, 1024);
	if (pwd == NULL)
		return (print_errno());
	argv[0] = "export";
	argv[1] = ft_strjoin("PWD=", pwd);
	argv[2] = NULL;
	free(pwd);
	return (ft_export(argv, msh));
}

int	change_dir(char *dir, t_msh *msh)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 1024);
	if (!oldpwd)
		return (print_errno());
	if (chdir(dir) == -1)
		return (chdir_error(dir));
	if (set_new_oldpwd(oldpwd, msh) != 0)
		return (errno);
	if (set_new_pwd(msh) != 0)
		return (errno);
	return (0);
}

int	cd_to_oldpwd(t_msh *msh)
{
	char	*oldpwd;
	int		r_vel;

	oldpwd = get_value_from_envp(msh, "OLDPWD");
	if (oldpwd[0] == '\0')
	{
		ft_putstr_fd("minishell: cd : HOME not set \n", 2);
		return (1);
	}
	r_vel = change_dir(oldpwd, msh);
	free(oldpwd);
	return (r_vel);
}

int	change_work_dir(char **argv, t_msh *msh)
{
	char	*argb[2];

	if (ft_strcmp(argv[1], "-") == 0)
		return (cd_to_oldpwd(msh));
	if (ft_strcmp(argv[1], "~") == 0)
	{
		argb[0] = "cd";
		argb[1] = NULL;
		return (ft_cd(argb, msh));
	}
	else
		return (change_dir(argv[1], msh));
}

int	ft_cd(char **argv, t_msh *msh)
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
		{
			ft_putstr_fd("minishell: cd : HOME not set \n", 2);
			return (1);
		}
		r_vel = change_dir(home, msh);
		free(home);
		return (r_vel);
	}
	if (ft_split_len(argv) == 2)
		return (change_work_dir(argv, msh));
}
