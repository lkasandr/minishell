#include "minishell.h"

void	sort_struct_2(t_env *min, t_env *tmp)
{
	char	*key;
	char	*value;

	key = tmp->key;
	value = tmp->value;
	tmp->key = min->key;
	tmp->value = min->value;
	min->key = key;
	min->value = value;
}

void	sort_struct1(t_env *tmp)
{
	t_env	*min;
	t_env	*r;
	int		i;

	min = tmp;
	r = tmp->next;
	while (r)
	{
		i = 1;
		while (i <= ft_strlen(min->key))
		{
			if (strncmp(min->key, r->key, i) > 0)
			{
				min = r;
				break ;
			}
			i++;
		}
		r = r->next;
	}
	sort_struct_2(min, tmp);
}

void	sort_struct(t_env *export)
{
	t_env	*tmp;

	tmp = export;
	while (tmp)
	{
		sort_struct1(tmp);
		tmp = tmp->next;
	}
}

int	check_argv(char **argv)
{
	int	count;

	count = 0;
	while (argv[count])
		count++;
	if (count == 1 && ft_strlen(argv[0]) > 6)
		return (0);
	return (1);
}

int	our_export(int count, t_env *env, t_env *export, char **argv)
{
	if (!check_argv(argv))
	{
		print_error(argv[0]);
		return (0);
	}
	if (count == 1)
		print_declare_export(export);
	else
		process_export(count, argv, env, export);
	return (0);
}
