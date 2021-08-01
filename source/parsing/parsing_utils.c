#include "minishell.h"

/*
**		@brief		Inicialise new command element
*/
t_cmnd	*new_command(void)
{
	t_cmnd	*new_cmnd;

	new_cmnd = ft_calloc(1, sizeof(*new_cmnd));
	if (!new_cmnd)
		ft_critical_error(NULL, NULL);
	new_cmnd->next = NULL;
	new_cmnd->arg = NULL;
	new_cmnd->out = 1;
	return (new_cmnd);
}

/*
**		@brief		Get string wrapped by quotes	
*/
char	*get_quotes_string(t_msh *msh, char *s, size_t *i)
{
	t_list	*chars;
	char	quote;
	char	*key;
	char	*quote_str;

	chars = NULL;
	quote = s[(*i)++];
	while (s[*i] && s[*i] != quote)
	{
		if (s[*i] == '$' && quote == '\"')
		{
			key = get_key(quote, s, i);
			if (!ft_strncmp(key, "?", 2))
				ft_lstadd_back(&chars, ft_lstnew(ft_itoa(msh->old_status)));
			else
				ft_lstadd_back(&chars,
					ft_lstnew(get_value_from_envp(msh, key)));
			free(key);
		}
		else
			ft_lstadd_back(&chars, ft_lstnew(ft_chrdup(s[(*i)++])));
	}
	if (s[*i])
		(*i)++;
	quote_str = ft_lstdup_str(chars);
	ft_lstclear(&chars);
	return (quote_str);
}

/*
**		@brief	add the found word to commands list orredirects	list
*/
void	add_keyword(t_msh *msh, t_list **chars, bool is_redirect)
{
	char	*keyword;
	char	*msg;

	keyword = ft_lstdup_str(*chars);
	ft_lstclear(chars);
	if (is_redirect)
	{
		if (ft_strlen(keyword) == 1
			|| (ft_strlen(keyword) == 2 && keyword[0] == keyword[1]))
		{
			msg = ft_strjoin("msh: Unexpected error near ", keyword);
			ft_raise_error(msg, 0);
			free(msg);
		}
		ft_lstadd_back(&msh->cmnd->redirects, ft_lstnew(keyword));
	}
	else
		ft_lstadd_front(&msh->cmnd->lst_arg, ft_lstnew(keyword));
}

/*
**		@brief		Get the key from string after '$' character	
*/
char	*get_key(char quote, char *s, size_t *i)
{
	t_list	*key_chars;
	char	*key;

	key_chars = NULL;
	(*i)++;
	while (s[*i] && !ft_ch_in_str(s[*i], " <>|$'\n=") && s[*i] != quote)
		ft_lstadd_back(&key_chars, ft_lstnew(ft_chrdup(s[(*i)++])));
	key = ft_lstdup_str(key_chars);
	ft_lstclear(&key_chars);
	return (key);
}

/*
**		@brief		skips any characters in brackets (' or ")
*/
int	skip_brackets(char *str)
{
	int	i;

	i = 1;
	while (str[i] != str[0] && str[i] && str[i + 1])
		i++;
	return (i);
}