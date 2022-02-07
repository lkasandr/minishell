#include "minishell.h"

t_env	*delete_node_env(t_env *lst, t_env *root)
{
	t_env	*temp;

	temp = root;
	while (temp->next != lst)
		temp = temp->next;
	temp->next = lst->next;
	return (temp);
}

static int	search_key(char *key, t_env *env)
{
	t_env	*p;
	int		flag;

	p = env;
	flag = 0;
	while (p)
	{
		if (ft_strcmp(key, p->key) == 0)
		{
			p = delete_node_env(p, env);
			flag = 1;
		}
		p = p->next;
	}
	return (flag);
}

static int	check_argv(char **argv)
{
	int	count;

	count = 0;
	while (argv[count])
		count++;
	if (count == 1 && ft_strlen(argv[0]) > 5)
		return (0);
	return (1);
}

int	our_unset(t_env *env, t_env *export, char **argv, int count)
{
	int	i;

	i = 1;
	if (!check_argv(argv))
	{
		print_error(argv[0]);
		return (0);
	}
	while (i < count)
	{
		if (check_export_argument(argv[i]) == -1)
		{
			printf("minishell: unset: `%s': not a valid identifier\n", argv[i]);
			return (0);
		}
		search_key(argv[i], env);
		search_key(argv[i], export);
		i++;
	}
	return (0);
}
