#include "minishell.h"

void test_print_arr(char **arr)
{
	for (size_t i = 0; arr[i]; i++)
		printf("%zu: %s\n", i, arr[i]);
}
