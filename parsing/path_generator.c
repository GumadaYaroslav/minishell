#include "minishell.h"

/*
**	@brief	Get the splited by ':' PATH enviroment object
*/
char	**get_splited_path(t_msh *msh)
{
	char	*val;
	char	**paths;

	val = get_value_from_envp(msh, "PATH");
	paths = ft_split(val, ':');
	free(val);
	return (paths);
}

/*
**	@brief		generates a full path for the program using the proggram name
**				and the next path from enviroment PATH	
**	@return	int		0 if cannot generates new full path, else 1
*/
int	gen_next_path(char **argv, char **paths, char *name)
{
	static int	z;
	char		*temp;

	if (z > 1)
		free(argv[0]);
	if (z > ft_split_len(paths))
	{
		z = 0;
		argv[0] = name;
		return (0);
	}
	if (!z && !ft_is_path(name))
		z++;
	if (z)
	{
		temp = ft_strjoin(paths[z - 1], "/");
		argv[0] = ft_strjoin(temp, name);
		if (!temp || !argv[0])
			ft_critical_error(NULL, NULL);
		free(temp);
	}
	z++;
	return (1);
}

/*
**	@brief	checks if the program name starts from character '/'
**	
**	@param	s		pointer to string
**	@return	int		1 if is path, else 0
*/
int	ft_is_path(char *s)
{
	while (*s && !ft_isalnum(*s))
		if (*s++ == '/')
			return (1);
	return (0);
}
