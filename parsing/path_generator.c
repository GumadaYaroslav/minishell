#include "minishell.h"


char	**get_splited_path(t_msh *msh)
{
	char 	*val;
	char	**paths;

	val = get_value_from_envp(msh, "PATH");
	paths = ft_split(val, ':');
	free(val);
	return (paths);
}

// int	gen_next_path(t_msh *msh, t_cmnd *cmnd)
// {
// 	// static

// 	if (!cmnd->lst_arg)
// 		return (0);
	
// 	char *name = 
// }

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
			ft_raise_error(NULL, NULL);
		free(temp);
	}
	z++;
	return (1);
}

/*
**	@brief	open input or output files. create output file if not exist
**	
**	@param	fname		string with file name
**	@param	is_infile	is input file
**	@return	int			file descriptor
*/
int	my_open(t_param *p, char *fname, int mode)
{
	int	fd;

	if (mode == L_ARR)
	{
		fd = open(fname, O_RDONLY);
		p->infile = NULL;
	}
	else if (mode == R_ARR)
	{
		fd = open(fname, O_RDWR | O_CREAT | O_TRUNC, 00774);
		p->outfile = NULL;
	}
	else if (mode == R_D_ARR)
	{
		fd = open(fname, O_WRONLY | O_APPEND | O_CREAT, 00774);
		p->outfile = NULL;
	}
	else
		fd = -1;
	if (fd < 0)
		ft_raise_error(NULL, fname);
	return (fd);
}

/*
**	@brief	checks if the program name starts from character '/'
**	
**	@param	s	pointer to string
**	@return	int	1 if is path
*/
int	ft_is_path(char *s)
{
	while (*s && !ft_isalnum(*s))
		if (*s++ == '/')
			return (1);
	return (0);
}