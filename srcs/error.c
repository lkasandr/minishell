#include "minishell.h"

void	ft_error(int code)
{
	if (code == 1)
		printf("Error: malloc.\n");
	if (code == 2)
		printf("Can't read file\n");
	g_sh.exit_code = 1;
	exit(EXIT_FAILURE);
}

void	print_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_sh.exit_code = 127;
}
