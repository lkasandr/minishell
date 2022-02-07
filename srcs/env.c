#include "minishell.h"

int	check_count(char **argv, int count)
{
	int	i;

	i = 0;
	if (count > 1)
	{
		while (i < 2)
		{
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd(": ", 2);
			i++;
		}
		ft_putstr_fd("No such file or directory\n", 2);
		return (0);
	}
	return (1);
}

int	our_env(t_env *env, char **argv, int count)
{
	t_env	*p;
	int		i;

	i = 0;
	if (!check_count(argv, count))
		return (0);
	p = env;
	while (p != NULL)
	{
		printf("%s=%s\n", p->key, p->value);
		p = p->next;
	}
	return (0);
}
