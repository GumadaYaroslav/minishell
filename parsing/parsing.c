#include "minishell.h"

int		parsing(t_msh *msh, char *s)
{
	parsing_check_pipes(msh, s);
	if (msh->status)
		return (1);
	parsing_by_words(msh, s);
	test_print_command(msh->lst_cmnd); // todo del
	return (msh->status);
}

void	parsing_check_pipes(t_msh *msh, char *s)
{
	bool	keyword;

	keyword = false;
	while (*s)
	{
		if (*s == '|')
		{
			if (!keyword)
			{
				ft_raise_error(msh, "syntax error near unexpected token '|'", 0);
				return ;
			}
			keyword = false;
		}
		else if (!ft_ch_in_str(*s, " \t"))
			keyword = true;
		s++;
	}
}

void	parsing_by_words(t_msh *msh, char *s)
{
	size_t	i;

	msh->cmnd = new_command();
	i = 0;
	while(s[i] && s[i] != '\n')
	{
		if (msh->status)
			return ;
		if (s[i] == '|')
		{
			ft_cmnd_add_end(&msh->lst_cmnd, msh->cmnd);
			msh->cmnd = new_command();
			i++;
		}
		else if (!ft_ch_in_str(s[i], " \t"))
			parsing_keyword(msh, s, &i);
		else
			i++;
	}
	ft_cmnd_add_end(&msh->lst_cmnd, msh->cmnd);
}

void	parsing_keyword(t_msh *msh, char *s, size_t *i)
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
	parsing_word(msh, s, i, &chars);
	add_keyword(msh, &chars, is_redirect);
}

char	*get_quotes_string(t_msh *msh, char *s, size_t *i)
{
	t_list	*chars;
	char	quote;
	char	*quote_str;

	chars = NULL;
	quote = s[(*i)++];
	while (s[*i] && s[*i] != quote)
	{
		if (s[*i] == '$' && quote == '\"')
			ft_lstadd_back(&chars, ft_lstnew(get_value_from_envp(msh, get_key(quote, s, i))));
		else
			ft_lstadd_back(&chars, ft_lstnew(ft_chrdup(s[(*i)++])));
	}
	if (s[*i])
		(*i)++;
	quote_str = ft_lstdup_str(chars);
	ft_lstclear(&chars);
	return (quote_str);
}
