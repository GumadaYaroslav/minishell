#include "minishell.h"

void	get_redirects(t_msh *msh, t_cmnd *cmnd)
{
	t_list	*redirect;

	redirect = cmnd->redirects;
	while (redirect)
	{
		if (!ft_strncmp(redirect->val, "<<", 2))
			;
		else if (!ft_strncmp(redirect->val, "<", 1))
			;
		else if (!ft_strncmp(redirect->val, ">>", 2))
			;
		else if (!ft_strncmp(redirect->val, ">", 1))
			;
		redirect = redirect->next;
	}
	dups_input_output(msh, cmnd);

}
