#include "minishell.h"

char	*find_path(t_env *env, char *bin)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, bin))
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("");
}

int	token_size(t_store *token)
{
	t_store	*tmp;
	int		i;

	tmp = token;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

int	check_redirect_in_pipe(char *word)
{
	if (ft_strchr(word, '>') || ft_strchr(word, '<'))
		return (1);
	else
		return (0);
}

char	**get_pipe_array(t_store *token)
{
	t_store		*p;
	char		**array;
	char		*str;

	p = token;
	str = NULL;
	while (p)
	{
		if (!str)
			str = ft_strdup(p->word);
		else
			str = ft_strjoin(str, p->word);
		p = p->next;
	}
	array = ft_split(str, '|');
	free(str);
	if (!array)
		ft_error(1);
	return (array);
}

t_store	*get_pipe_struct(t_store *token)
{
	t_store	*tmp;
	char	**array;
	int		k;

	k = 0;
	array = get_pipe_array(token);
	tmp = (t_store *)malloc(sizeof(t_store));
	tmp->word = NULL;
	tmp->next = NULL;
	while (array[k])
	{
		if (*array[k] == ' ')
			array[k]++;
		if (!tmp->word)
			tmp->word = ft_strdup(array[k]);
		else
			tmp = add_node_token(tmp, array[k], ft_strlen(array[k]));
		k++;
	}
	return (tmp);
}
