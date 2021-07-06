#include "minishell.h"

void test_print_arr(char **arr)
{
	for (size_t i = 0; arr[i]; i++)
		printf("%zu: %s\n", i, arr[i]);
}

void	test_print_lst(t_list *lst)
{
	for (int i = 0; lst; i++, lst=lst->next)
		printf("|%s| ", lst->val);
	printf("\n");
}

void test_print_command(t_cmnd *cmnd)
{
	size_t i = 0;
	while (cmnd)
	{
		i++;
		printf("------%4zu ------\nCOMMANDS: ", i);
		test_print_lst(cmnd->lst_arg);
		printf("REDIRECTS: ");
		test_print_lst(cmnd->redirects);
		cmnd = cmnd->next;
	}
}