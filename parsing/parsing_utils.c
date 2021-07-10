#include "minishell.h"

t_cmnd	*new_command(void)
{
	t_cmnd	*new_cmnd;

	new_cmnd = ft_calloc(1, sizeof(*new_cmnd));
	if (!new_cmnd)
		ft_critical_error(NULL, NULL);
	new_cmnd->next = NULL;
	return new_cmnd;
}

void	parsing_word(t_msh *msh, char *s, size_t *i, t_list **chars)
{
	char	*key;
	
	while (s[*i] && !ft_ch_in_str(s[*i], " <>|\n"))
	{
		if (s[*i] == '$')
		{
			key = get_key(0, s, i);
			ft_lstadd_back(chars, ft_lstnew(get_value_from_envp(msh, key)));
			free(key);
		}
		else if (ft_ch_in_str(s[*i], "'\""))
			ft_lstadd_back(chars, ft_lstnew(get_quotes_string(msh, s, i)));
		else
			ft_lstadd_back(chars, ft_lstnew(ft_chrdup(s[(*i)++])));
	}
}

void	add_keyword(t_msh *msh, t_list **chars, bool is_redirect)
{
	char	*keyword;
	char	*msg;

	keyword = ft_lstdup_str(*chars);

	ft_lstclear(chars);
	// printf("found word: %s\n", keyword);
	if (is_redirect)
	{
		if (ft_strlen(keyword) == 1 || (ft_strlen(keyword) == 2 && keyword[0] == keyword[1]))
		{
			msg = ft_strjoin("Unexpected error near ", keyword);
			ft_raise_error(msh, msg, 0);
			free(msg);
			free(keyword);
			return ;
		}
		ft_lstadd_back(&msh->cmnd->redirects, ft_lstnew(keyword));
	}
	else
		ft_lstadd_front(&msh->cmnd->lst_arg, ft_lstnew(keyword));
}

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

