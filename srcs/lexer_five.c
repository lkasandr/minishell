#include "minishell.h"

int	ft_free(char *str)
{
	if (str)
		free(str);
	str = NULL;
	return (0);
}

char	*copy_str_without_quotes(char *str, int j, int i)
{
	char	*tmp;
	int		k;
	int		l;

	tmp = NULL;
	k = -1;
	l = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) - 2) + 1);
	if (!tmp)
		ft_error(1);
	while (str[++k] && (k != j))
		tmp[l++] = str[k];
	k = j;
	while (str[++k] && (k != i))
		tmp[l++] = str[k];
	k = i;
	while (str[++k])
		tmp[l++] = str[k];
	tmp[l] = '\0';
	return (tmp);
}

static char	*get_second_tmp(char *str, int j, int i, t_env *env)
{
	char	*tmp;
	int		len;
	int		flag;
	t_env	*p;

	tmp = ft_substr(str, j + 1, i - j - 1);
	if (!tmp)
		ft_error(1);
	len = ft_strlen(tmp);
	flag = 0;
	p = env;
	while (p != NULL)
	{
		if (!ft_strcmp(p->key, tmp))
		{
			free(tmp);
			tmp = ft_strdup(p->value);
			flag = 1;
			break ;
		}
		p = p->next;
	}
	if (flag == 0)
		tmp = "\0";
	return (tmp);
}

char	*process_dollar(char *str, int *i, t_env *env)
{
	int		j;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	(*i)++;
	if (!str[*i] || str[*i] == '\'' || str[*i] == '\"' || str[*i] == '?')
		return (str);
	while (str[*i])
	{
		if (str[*i] != '_' && !ft_isalnum(str[*i]))
			break ;
		(*i)++;
	}
	tmp1 = ft_substr(str, 0, j);
	tmp2 = get_second_tmp(str, j, *i, env);
	tmp3 = ft_substr(str, *i, ft_strlen(str));
	tmp2 = ft_strjoin(tmp1, tmp2);
	str = ft_strjoin(tmp2, tmp3);
	return (str);
}

char	*double_quotes(char *str, int *i, t_env *env)
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
	tmp = copy_str_without_quotes(str, j, *i);
	return (tmp);
}
