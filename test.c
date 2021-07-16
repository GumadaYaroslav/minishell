
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>



int main()
{
	write(1, "\b\b  \b\b", strlen("\b\b  \b\b"));
	return (1);
}