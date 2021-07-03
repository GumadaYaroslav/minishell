#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/errno.h>

# include "libft.h"
// #include <readline/readline.h>
// #include <readline/history.h>
# include "history.h"
# include "readline.h"


# define STDIN 0
# define STDOUT 1


typedef	struct s_flag
{
	bool	quote;
	bool	d_quote;
	size_t	pipe;
}	t_flag;


typedef struct s_cmnd
{
	struct s_cmnd	*next;
	char			**arg;
	t_list			*lst_arg;
	t_list			*redirects;
}	t_cmnd;

typedef	struct s_minishell
{
	// char	**path;
	t_list	*lst_env;
	char	**env;

	t_cmnd	*cmnd;
}	t_msh;


// parcing / minishell
int		main(int argc, char **argv, char **envp);

// parsing / parsing
void	parsing_keyword(t_msh *msh, char *s, size_t *i);
void	parsing_by_words(t_msh *msh, char *s);
void	add_keyword(t_msh *msh, t_list **chars, bool is_redirect);
char	*get_quotes_string(t_msh *msh, char *s, size_t *i);
char	*get_key(char quote, char *s, size_t *i);

t_cmnd	*new_command(void);
t_cmnd	*inicialise_cmnd(t_msh *msh, size_t ind);

// parsing / envp
void	inicialise_struct(t_msh *msh, int argc, char **argv, char **envp);
char	*get_value_from_envp(t_msh *msh, char *key);

// parcing / tests_func
void 	test_print_arr(char **arr);
void	test_print_command(t_cmnd *cmnd);
void	test_print_lst(t_list *lst);


//parsing / raiser_error
void	ft_raise_error(char *msg, char *errno_msg);


////////////////// pipex block ///////////////

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

////////////////// pipex block end ///////////////

#endif