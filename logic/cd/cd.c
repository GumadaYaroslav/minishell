#include "minishell.h"

int	help_change_dir(char *oldpwd, char *dir, t_msh *msh)
{
	if (!oldpwd)
		return (print_errno());
	if (chdir(dir) == -1)
		return (chdir_error(dir));
	if (set_new_oldpwd(oldpwd, msh) != 0)
		return (print_errno());
	if (set_new_pwd(msh) != 0)
		return (print_errno());
	return (0);
}

int	change_dir(char *dir, t_msh *msh)
{
	char	*oldpwd;
	char	*tmp;
	int		ret_v;

	tmp = ft_calloc(1024, 1);
	if (!tmp)
		print_errno();
	oldpwd = getcwd(tmp, 1024);
	ret_v = help_change_dir(oldpwd, dir, msh);
	free(tmp);
	return (ret_v);
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
	return (0);
}
