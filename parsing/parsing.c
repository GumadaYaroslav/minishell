#include "minishell.h"

t_cmnd	*new_command(void)
{
	t_cmnd	*new_cmnd;

	new_cmnd = ft_calloc(1, sizeof(*new_cmnd));
	if (!new_cmnd)
		ft_raise_error(NULL, NULL); // return NULL;
	// new_cmnd->ind = ind;
	new_cmnd->next = NULL;
	return new_cmnd;
}


void	parsing_by_words(t_msh *msh, char *s)
{
	size_t	i;
	bool	empty_cmnd;

	ft_lstadd_front(&msh->cmnd, new_command());
	empty_cmnd = true;
	i = 0;
	while(s[i] && s[i] != '\n')
	{
		if (s[i] == '|')
		{
			if (empty_cmnd)
				ft_raise_error("syntax error near unexpected token '|'", NULL);
			ft_lstadd_front(&msh->cmnd, new_command());
			empty_cmnd = true;
		}
		else if (!ft_ch_in_str(s[i], ' \t'))
		{
			empty_cmnd = false;
			parsing_keyword(msh->cmnd, s, &i);
		

		}
		i++;

		
	}
}

size_t	parsing_keyword(t_msh *msh, char *s, size_t *i)
{
	t_list	*word;

	word = NULL;
	// if (s[*i] == '<')
	// 	word = msh->cmnd->l_arrow;
	// else if (s[*i] == '>')
	// 	word = msh->cmnd->r_arrow;
	// else
	// 	word = msh->cmnd->lst_arg;
	if (s[*i] == '<' || s[*i] == '>')
	{
		ft_lstadd_back(&word, ft_lstnew(ft_chrdup(s[(*i)++])));
		if (s[*i - 1] == s[*i])
			ft_lstadd_back(&word, ft_lstnew(ft_chrdup(s[(*i)++])));
		while (ft_ch_in_str(s[*i], " \t"))
			(*i)++;
	}
	while (s[*i] && !ft_ch_in_str(s[*i], "<>| \n")) // todo add '"$
	{
		ft_lstadd_back(&word, ft_lstnew(ft_chrdup(s[(*i)++])));
	}
}