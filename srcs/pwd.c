#include "minishell.h"

static int	check_argv(char **argv)
{
	int	count;

	count = 0;
	while (argv[count])
		count++;
	if (count == 1 && ft_strlen(argv[0]) > 3)
		return (0);
	return (1);
}

int	our_pwd(char **argv)
{
	char	dir[4096];

	errno = 0;
	if (!check_argv(argv))
	{
		print_error(argv[0]);
		return (0);
	}
	if (getcwd(dir, 4096))
		printf("%s\n", dir);
	else
		print_error(strerror(errno));
	return (0);
}
