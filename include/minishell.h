#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/errno.h>

# include "libft.h"
# include "history.h"
# include "readline.h"


# define STDIN 0
# define STDOUT 1
# define L_ARR 1
# define R_ARR 2
# define R_D_ARR 3

typedef struct s_param
{
	char	*infile;
	char	*outfile;
	char	*stop_word;
	char	**paths;
	int		paths_len;
	int		fd[2];
	pid_t	pid;
	char	**argv;
	char	**envp;
	size_t	cnt_cmnds;
	size_t	ind;
	char	***cmnds;
}	t_param;


// p_pipes
int		main(int argc, char **argv, char **envp);
void	pipex(t_param *p);
void	run_command(t_param *p, size_t i);

// p_raise_error
void	ft_raise_error(char *msg, char *errno_msg);
int		ft_is_path(char *s);

// p_redirects
int		ne_gnl(int fd, char **line, const char *keyword);
void	left_double_arrow(t_param *p);
void	child_left_double_arrow(t_param *p, int *fd);

// p_utils
void	inicialize_param(int argc, char **argv, char **envp, t_param *p);
void	get_commands(int argc, char **argv, t_param *p);
void	get_paths(t_param *p);
int		get_next_path(t_param *p, char *cmnd, int i);
int		my_open(t_param *p, char *fname, int mode);

#endif