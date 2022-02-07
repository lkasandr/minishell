#include "minishell.h"

char	*get_key(char *token)
{
	char	*key;
	int		i;

	key = NULL;
	i = 0;
	while (token[i])
	{
		if (token[i] == '=')
			break ;
		i++;
	}
	key = ft_substr(token, 0, i);
	if (!key)
		ft_error(1);
	return (key);
}

char	*get_value(char *token)
{
	char	*value;
	int		i;
	int		len;

	value = NULL;
	i = 0;
	len = ft_strlen(token);
	while (token[i])
	{
		if (token[i] == '=')
			break ;
		i++;
	}
	if (i != len - 1)
	{
		value = ft_substr(token, i + 1, len - i);
		if (!value)
			ft_error(1);
	}
	return (value);
}

int	export_error(char *str)
{
	if (check_export_argument(str) == -1)
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_sh.exit_code = 1;
		return (0);
	}
	return (1);
}

void	fill_export(char *str, t_env *env, t_env *export)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	if (ft_strchr(str, '='))
	{
		key = get_key(str);
		value = get_value(str);
		add_env_export(key, value, env, export);
	}
	else
	{
		key = ft_strdup(str);
		if (check_repeat(key, value, export) == 0)
			export = add_node_env(export, key, value);
	}
}

int	process_export(int count, char **argv, t_env *env, t_env *export)
{
	int		i;

	i = 1;
	while (i < count)
	{
		if (!export_error(argv[i]))
			return (0);
		fill_export(argv[i], env, export);
		i++;
	}
	return (0);
}
