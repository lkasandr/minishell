#include "minishell.h"

int	check_pipe(t_env *env, t_env *export, t_store *token, char **envp)
{
	t_store	*p;
	int		if_pipe;

	if_pipe = 0;
	p = token;
	while (p)
	{
		if (!ft_strncmp(p->word, "|", 1))
			if_pipe = 1;
		p = p->next;
	}
	if (if_pipe == 1)
	{
		pipe_proc(env, envp, export, token);
		return (0);
	}
	return (1);
}

int	execute_command(t_env *env, t_env *export, t_store *token, char **envp)
{
	if (!token->word)
		return (0);
	if (!check_redirect(token, env))
		return (0);
	if (!check_pipe(env, export, token, envp))
		return (0);
	command_handler(env, export, token, envp);
	return (0);
}

t_env	*add_node_env(t_env *env, char *key, char *value)
{
	t_env	*temp;
	t_env	*p;

	temp = (t_env *)malloc(sizeof(t_env));
	if (!temp)
		ft_error(1);
	p = env->next;
	env->next = temp;
	temp->key = ft_strdup(key);
	if (!temp->key)
		ft_error(1);
	if (value)
	{
		temp->value = ft_strdup(value);
		if (!temp->value)
			ft_error(1);
	}
	else
		temp->value = "\0";
	temp->next = p;
	return (env);
}

static void	fill_env(t_env *env, char *key, char *value)
{
	if (!env->key)
	{
		env->key = ft_strdup(key);
		if (!env->key)
			ft_error(1);
		if (value)
		{
			env->value = ft_strdup(value);
			if (!env->value)
				ft_error(1);
		}
	}
	else
		env = add_node_env(env, key, value);
	free(key);
	free(value);
}

void	fill_struct_env(char **envp, t_env *env)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			key = get_key(envp[i]);
			value = get_value(envp[i]);
		}
		else
		{
			key = ft_strdup(envp[i]);
			if (!key)
				ft_error(1);
			value = NULL;
		}
		fill_env(env, key, value);
		i++;
	}
}
