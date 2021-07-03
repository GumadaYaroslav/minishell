#include "minishell.h"

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


void	parsing_by_words(t_msh *msh, char *s)
{
	size_t	i;
	bool	empty_cmnd;

	printf("add %c\n", s[0]);
	ft_lstadd_front(&msh->cmnd, new_command());
	printf("after create new cmnd\n");
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
		else if (!ft_ch_in_str(s[i], " \t"))
		{
			empty_cmnd = false;
			printf("before park key\n");
			parsing_keyword(msh, s, &i);
		

		}
		i++;

		
	}
}

size_t	parsing_keyword(t_msh *msh, char *s, size_t *i)
{
	t_list	*chars;
	char	*keyword;

	chars = NULL;
	if (s[*i] == '<' || s[*i] == '>')
	{
		ft_lstadd_back(&chars, ft_lstnew(ft_chrdup(s[(*i)++])));
		if (s[*i - 1] == s[*i])
			ft_lstadd_back(&chars, ft_lstnew(ft_chrdup(s[(*i)++])));
		while (ft_ch_in_str(s[*i], " \t"))
			(*i)++;
	}
	while (s[*i] && !ft_ch_in_str(s[*i], " <>|\n")) // todo add '"$
	{
		if 
		ft_lstadd_back(&chars, ft_lstnew(ft_chrdup(s[(*i)++])));
	}
	keyword = ft_lstdup_str(chars);
	ft_lstclear(&chars);
	printf("found word: %s\n", keyword);
	if (ft_ch_in_str(keyword[0], "<>"))
		ft_lstadd_back(&msh->cmnd->redirects, ft_lstnew(keyword));
	else
		ft_lstadd_back(&msh->cmnd->lst_arg, ft_lstnew(keyword));

}