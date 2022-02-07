#include "minishell.h"

static int	check_argv(char **argv)
{
	int	count;

	count = 0;
	while (argv[count])
		count++;
	if (count == 1 && ft_strlen(argv[0]) > 4)
		return (0);
	return (1);
}

static void	get_echo(char **argv, int i)
{
	while (argv[i])
	{
		if (!ft_strcmp(argv[i], "$?"))
			printf("%d", g_sh.exit_code);
		else
			printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
}

int	our_echo(char **argv)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (!argv)
		printf("\n");
	if (!check_argv(argv))
	{
		print_error(argv[0]);
		return (0);
	}
	if (argv[i] && ft_strcmp(argv[i], "-n") == 0)
	{
		n = 1;
		i++;
	}
	get_echo(argv, i);
	if (!n)
		printf("\n");
	return (0);
}
