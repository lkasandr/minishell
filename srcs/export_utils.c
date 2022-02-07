#include "minishell.h"

int	get_k(char *arg)
{
	int	k;

	k = 0;
	while (arg[k])
	{
		if (arg[k] == '=')
			break ;
		k++;
	}
	return (k);
}

int	check_export_argument(char *arg)
{
	int		k;
	char	*str;

	k = 0;
	str = NULL;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (-1);
	if (ft_strchr(arg, '='))
	{
		k = get_k(arg);
		str = ft_substr(arg, 0, k);
	}
	else
		str = arg;
	k = 0;
	while (str[k])
	{
		if (!ft_isalnum(str[k]) && str[k] != '_')
			return (-1);
		k++;
	}
	return (0);
}

int	check_repeat(char *key, char *value, t_env *env)
{
	t_env	*p;
	int		flag;

	p = env;
	flag = 0;
	while (p)
	{
		if (ft_strcmp(key, p->key) == 0)
		{
			free(p->key);
			p->key = ft_strdup(key);
			if (value)
			{
				free(p->value);
				p->value = ft_strdup(value);
			}
			flag = 1;
		}
		p = p->next;
	}
	return (flag);
}

char	*process_value(char *val, t_env *env)
{
	int	i;

	i = 0;
	while (val[i])
	{
		if (val[i] == '\'')
		{
			val = single_quotes(val, &i, env, 1);
			i = i - 2;
		}
		if (val[i] == '\"')
		{
			val = double_quotes(val, &i, env);
			i = i - 2;
		}
		if (val[i] == '$')
			val = process_dollar(val, &i, env);
		i++;
	}
	return (val);
}

void	add_env_export(char *key, char *value, t_env *env, t_env *export)
{
	char	*val;

	val = NULL;
	if (value)
		val = process_value(value, env);
	if (check_repeat(key, val, env) == 0)
		add_node_env(env, key, val);
	if (check_repeat(key, val, export) == 0)
		add_node_env(export, key, val);
}
