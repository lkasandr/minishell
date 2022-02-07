#include "minishell.h"

static char	*handler_quot_two(char *str, int i, t_env *env)
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
	return (str);
}

int	check_str(char i)
{
	if (!i)
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		g_sh.exit_code = 1;
		return (0);
	}
	return (1);
}

void	fill_struct_redirect(t_store *token, char *str, int i)
{
	if (!token->word)
	{
		token->word = ft_substr(str, 0, i);
		if (!token->word)
			ft_error(1);
	}
	else
		token = add_node_token(token, str, i);
}

char	*get_str_redir(char *str, int *i, t_env *env)
{
	while (str[*i] && str[*i] != ' ' && str[*i] != '>'
		&& str[*i] != '<' && str[*i] != '|')
	{
		if (str[*i] == '\'')
		{
			str = single_quotes(str, i, env, 1);
			*i = *i - 2;
		}
		if (str[*i] == '\"')
		{
			str = double_quotes(str, i, env);
			*i = *i - 2;
		}
		if (str[*i] == '$')
		{
			str = process_dollar(str, i, env);
			if (!str)
				ft_error(1);
		}
		(*i)++;
	}
	return (str);
}

char	*cut_double_redirect(char *str, t_env *env, t_store *token, int i)
{
	char	*tmp;

	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!str[i])
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (NULL);
	}
	while (str[i] && str[i] != ' ' && str[i] != '>'
		&& str[i] != '<' && str[i] != '|')
	{
		str = handler_quot_two(str, i, env);
		i++;
	}
	fill_struct_redirect(token, str, i);
	tmp = ft_substr(str, i, ft_strlen(str) - i);
	if (!tmp)
		return (NULL);
	return (tmp);
}
