#include "minishell.h"

void	parsing_by_words(t_msh *msh, char *s)
{
	size_t	i;
	int		pipes;

	printf("add %c\n", s[0]);
	msh->cmnd = new_command();
	printf("after create new cmnd\n");
	pipes = 0;
	i = 0;
	while(s[i] && s[i] != '\n')
	{
		if (s[i] == '|')
		{
			if (!msh->cmnd->redirects && !msh->cmnd->lst_arg)
				ft_raise_error("syntax error near unexpected token '|'", NULL);
			ft_cmnd_add_end(&msh->lst_cmnd, msh->cmnd);
			msh->cmnd = new_command();
			pipes++;
			i++;
		}
		else if (!ft_ch_in_str(s[i], " \t"))
			parsing_keyword(msh, s, &i);
		else
			i++;
	}
	if (pipes && !msh->cmnd->redirects && !msh->cmnd->lst_arg)
		ft_raise_error("syntax error near unexpected token '|'", NULL);
	ft_cmnd_add_end(&msh->lst_cmnd, msh->cmnd);
}

void *malloc_x(size_t size)
{
	void *ptr;

	ptr  = malloc(size);
	if (!ptr)
		exit(1);
	else
		return ptr;
}
t_cmnd	*new_command(void)
{
	t_cmnd	*new_cmnd;

	new_cmnd = ft_calloc(1, sizeof(*new_cmnd));
	if (!new_cmnd)
		ft_raise_error(NULL, NULL); // return NULL;
	// new_cmnd->ind = ind;
	new_cmnd->next = NULL;
	printf("create new cmnd\n");
	return new_cmnd;
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
	while (s[*i] && !ft_ch_in_str(s[*i], " <>|\n")) // todo add '"$
	{
		printf("check %c\n", s[*i]);
		if (s[*i] == '$')
		{
			printf("run dollar\n");
			ft_lstadd_back(&chars, ft_lstnew(get_value_from_envp(msh, get_key(0, s, i))));
			printf("dolar = %s\n", chars->val);
		}
		else if (ft_ch_in_str(s[*i], "'\""))
		{
			printf("run quotes %zu:%c\n", *i, s[*i]);
			ft_lstadd_back(&chars, ft_lstnew(get_quotes_string(msh, s, i)));
			printf("quote content= %s\n", ft_lstlast(chars)->val);
		}
		else
			ft_lstadd_back(&chars, ft_lstnew(ft_chrdup(s[(*i)++])));
	}
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


void	add_keyword(t_msh *msh, t_list **chars, bool is_redirect)
{
	char *keyword;

	keyword = ft_lstdup_str(*chars);

	ft_lstclear(chars);
	printf("found word: %s\n", keyword);
	if (is_redirect)
	{
		if (ft_strlen(keyword) == 1 || (ft_strlen(keyword) == 2 && keyword[0] == keyword[1]))
			ft_raise_error("Unexpected error near ", keyword);
		ft_lstadd_back(&msh->cmnd->redirects, ft_lstnew(keyword));
	}
	else
		ft_lstadd_back(&msh->cmnd->lst_arg, ft_lstnew(keyword));
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