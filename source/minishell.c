/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alchrist <alchrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 19:10:11 by alchrist          #+#    #+#             */
/*   Updated: 2021/08/08 16:16:48 by alchrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_status;

/*
**		@brief		Hello world!
*/
int	main(int argc, char **argv, char **envp)
{
	t_msh	msh;
	char	*str;

	g_status = 0;
	rl_outstream = stderr;
	inicialise_struct(&msh, argc, argv, envp);
	ft_signal_main();
	while (true)
	{
		str = readline(MSH_AVE);
		if (g_status == 130)
		{
			msh.old_status = 1;
			g_status = 0;
		}
		if (!str)
			str = ft_strdup("exit");
		add_history(str);
		if (!parsing(&msh, str))
			run_commands_via_pipes(&msh);
		cleaning(&msh, str);
	}
}
