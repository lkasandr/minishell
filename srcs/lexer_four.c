#include "minishell.h"

char	*double_quotes_two(char *str, int *i, t_env *env)
{
	int		j;
	char	*tmp;

	j = *i;
	tmp = NULL;
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == '$')
			str = process_dollar(str, i, env);
		if (str[*i] == '\"')
			break ;
		(*i)++;
	}
	if (*i == ft_strlen(str))
	{
		printf("minishell: missing second quote.");
		return ("\0");
	}
	tmp = ft_strdup(str);
	return (tmp);
}

char	*get_tmp(char *str, int j, int i, int flag)
{
	char	*tmp;

	tmp = NULL;
	if (flag != 0)
		tmp = copy_str_without_quotes(str, j, i);
	else
		tmp = ft_strdup(str);
	return (tmp);
}

char	*single_quotes(char *str, int *i, t_env *env, int flag)
{
	int		j;
	char	*tmp;

	j = *i;
	tmp = NULL;
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == '$' && flag == 0)
			str = process_dollar(str, i, env);
		if (str[*i] == '\'')
			break ;
		(*i)++;
	}
	if (*i == ft_strlen(str))
	{
		printf("minishell: missing second quote.");
		return ("\0");
	}
	tmp = get_tmp(str, j, *i, flag);
	ft_free(str);
	if (tmp == NULL)
		return ("\0");
	return (tmp);
}

t_store	*get_last(t_store *token)
{
	if (token == NULL)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}

t_store	*add_node_token(t_store *token, char *str, int i)
{
	t_store	*temp;
	t_store	*p;

	p = get_last(token);
	temp = (t_store *)malloc(sizeof(t_store));
	if (!temp)
		ft_error(1);
	temp->word = ft_substr(str, 0, i);
	temp->next = NULL;
	p->next = temp;
	return (token);
}
