#include "minishell.h"

/*
**		@brief		Parses commands string
**		@return	int		0 if string correct, else error status
*/
int	parsing(t_msh *msh, char *s)
{
	parsing_check_pipes(s);
	if (g_status)
		return (1);
	parsing_by_words(msh, s);
	if (!g_status && msh->cmnd && msh->cmnd->lst_arg)
		update_underscore(msh, msh->cmnd->lst_arg->val);
	return (g_status);
}

/*
**		@brief		Simple check if pipes are closed	
*/
void	parsing_check_pipes(char *str)
{
	bool	keyword;
	bool	pipes;

	pipes = false;
	while (*str)
	{
		if (*str == '|')
		{
			pipes = true;
			if (!keyword)
				return ft_raise_error(ERR_PIPE, 0);
			keyword = false;
		}
		else if (!ft_ch_in_str(*str, " \t"))
			keyword = true;
		if (ft_ch_in_str(*str, "'\""))
			str += skip_brackets(str);
		str++;
	}
	if (pipes && !keyword)
		ft_raise_error(ERR_NEWL, 0);
}

/*
**		@brief	parsing command to list commands by pipes	
*/
void	parsing_by_words(t_msh *msh, char *s)
{
	size_t	i;

	msh->cmnd = new_command();
	i = 0;
	while (s[i] && !g_status)
	{
		if (s[i] == '|')
		{
			ft_cmnd_add_end(&msh->lst_cmnd, msh->cmnd);
			msh->cmnd = new_command();
			i++;
		}
		else if (!ft_ch_in_str(s[i], " \t"))
			parsing_word(msh, s, &i);
		else
			i++;
	}
	ft_cmnd_add_end(&msh->lst_cmnd, msh->cmnd);
}

/*
**		@brief		Parsing a string keyword wrapped with spaces.
*/
void	parsing_word(t_msh *msh, char *s, size_t *i)
{
	t_list	*chars;
	bool	is_redirect;

	is_redirect = false;
	chars = NULL;
	if (s[*i] == '<' || s[*i] == '>')
	{
		is_redirect = true;
		ft_lstadd_back(&chars, ft_lstnew(ft_chrdup(s[(*i)++])));
		if (s[*i - 1] == s[*i])
			ft_lstadd_back(&chars, ft_lstnew(ft_chrdup(s[(*i)++])));
		while (ft_ch_in_str(s[*i], " \t"))
			(*i)++;
	}
	parsing_word_p2(msh, s, i, &chars);
	add_keyword(msh, &chars, is_redirect);
}

/*
**		@brief		Parsing a string keyword wrapped with spaces. part2.
*/
void	parsing_word_p2(t_msh *msh, char *s, size_t *i, t_list **chars)
{
	char	*key;

	while (s[*i] && !ft_ch_in_str(s[*i], " <>|\n"))
	{
		if (s[*i] == '$')
		{
			key = get_key(0, s, i);
			if (!ft_strncmp(key, "?", 2))
				ft_lstadd_back(chars, ft_lstnew(ft_itoa(msh->old_status)));
			else
				ft_lstadd_back(chars, ft_lstnew(get_value_from_envp(msh, key)));
			free(key);
		}
		else if (ft_ch_in_str(s[*i], "'\""))
			ft_lstadd_back(chars, ft_lstnew(get_quotes_string(msh, s, i)));
		else
			ft_lstadd_back(chars, ft_lstnew(ft_chrdup(s[(*i)++])));
	}
}
