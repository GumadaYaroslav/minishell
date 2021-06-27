#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_param	p;

	inicialize_param(argc, argv, envp, &p);
	get_commands(argc, argv, &p);
	get_paths(&p);
	pipex(&p);
}


void	pipex(t_param *p)
{
	size_t i = 0;
	while (i < p->cnt_cmnds) // итерируемся по командам слева направо
	{
		if (i) // если это не первая команда - пайп уже открыт и берем данные с него
		{
			wait(0); // ждем завершения работы прошлой команды
			if (dup2(p->fd[0], STDIN) < 0) // копируем с выхода "старого" пайпа
				ft_raise_error(NULL, NULL);
			close(p->fd[0]);
			
		}
		if (!i && p->infile && dup2(my_open(p, p->infile, L_ARR), STDIN) < 0) // если есть входной файл - берем данные с него (так работает баш)
			ft_raise_error(NULL, NULL);
		if (i + 1 < p->cnt_cmnds)
		{
			if (pipe(p->fd) < 0) // создаем новый пайп если это не последняя команда
				ft_raise_error(NULL, NULL);
			if (dup2(p->fd[1], STDOUT) < 0) // и заворачиваем в него вывод
				ft_raise_error(NULL, NULL);
			close(p->fd[1]);
		}
		if (i + 1 == p->cnt_cmnds) // заворачиваем вывод в файл для последней команды
		{
			if (dup2(my_open(p, p->outfile, R_ARR), STDOUT) < 0)
				ft_raise_error(NULL, NULL);
		}
		if (i + 1 < p->cnt_cmnds) // Делаем ребеночка, если это не последняя команда
			p->pid = fork();
		
		if (!p->pid || i + 1 == p->cnt_cmnds) // Запускаем саму команду, если это дитя или пришло время последней команды
			run_command(p, i);
		i++;
	}

}

void	run_command(t_param *p, size_t i)
{
	char	*cmnd;

	cmnd = p->cmnds[i][0];
	while (get_next_path(p, cmnd, i))
	{
		if (!access(p->cmnds[i][0], F_OK))
		{
			if (!access(p->cmnds[i][0], X_OK))
				execve(p->cmnds[i][0], p->cmnds[i], p->envp);
			break ;
		}
	}
	ft_raise_error(ft_strjoin("Command not found: ", cmnd), NULL);
}
