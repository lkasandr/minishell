#include "minishell.h"

char	*handler_quot(char *str, int i, t_env *env)
{
	if (str[i] == '\'')
	{
		str = single_quotes(str, &i, env, 1);
		i = i - 2;
	}
	if (str[i] == '\"')
	{
		str = double_quotes(str, &i, env);
		i = i - 2;
	}
	if (str[i] == '$')
	{
		str = process_dollar(str, &i, env);
		if (!str)
			return (NULL);
	}
	return (str);
}

char	*put_err(char *str)
{
	ft_putstr_fd(str, 2);
	g_sh.exit_code = 258;
	return (NULL);
}

char	*process_pipe(char *str, t_env *env, t_store *token)
{
	char	*tmp;
	int		i;

	i = 1;
	while (*str == ' ' || *str == '\t')
		str++;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!str[i])
		return (put_err("syntax error near unexpected token `newline'\n"));
	while (str[i] && str[i] != '>' && str[i] != '<' && str[i] != '|')
	{
		str = handler_quot(str, i, env);
		i++;
	}
	if (!token->word)
		return (put_err("syntax error near unexpected token `|'\n"));
	else
		token = add_node_token(token, str, i);
	tmp = ft_substr(str, i, ft_strlen(str) - i);
	if (!tmp)
		return (NULL);
	return (tmp);
}
