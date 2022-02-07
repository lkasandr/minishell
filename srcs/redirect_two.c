#include "minishell.h"

char	*check_right_redir(char *str, int i, t_env *env, t_store *token)
{
	char	*tmp;

	tmp = NULL;
	i++;
	if (!str[i])
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		g_sh.exit_code = 1;
		return (NULL);
	}
	if (str[i] != '>')
	{
		tmp = cut_redirect(str, env, token, 1);
		if (!tmp)
			ft_error(1);
		return (tmp);
	}
	if (str[i] == '>')
	{
		tmp = cut_redirect(str, env, token, 2);
		if (!tmp)
			ft_error(1);
		return (tmp);
	}
	return (tmp);
}

char	*check_left_redir(char *str, int i, t_env *env, t_store *token)
{
	char	*tmp;

	tmp = NULL;
	i++;
	if (!str[i])
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		g_sh.exit_code = 1;
		return (NULL);
	}
	if (str[i] != '<')
	{
		tmp = cut_redirect(str, env, token, 1);
		if (!tmp)
			ft_error(1);
		return (tmp);
	}
	if (*str == '<')
	{
		tmp = cut_double_redirect(str, env, token, 2);
		if (!tmp)
			ft_error(1);
		return (tmp);
	}
	return (tmp);
}

char	*process_redirect(char *str, t_env *env, t_store *token)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (*str == ' ' || *str == '\t')
		str++;
	if (str[i] == '>')
	{
		tmp = check_right_redir(str, i, env, token);
		return (tmp);
	}
	if (str[i] == '<')
	{
		tmp = check_left_redir(str, i, env, token);
		return (tmp);
	}
	return (tmp);
}

char	*process_str_redirect(char *str, t_env *env)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			str = single_quotes(str, &i, env, 0);
		 if (str[i] == '\"')
			str = double_quotes_two(str, &i, env);
		if (str[i] == '$')
			str = process_dollar(str, &i, env);
		i++;
	}
	return (str);
}

int	right_redirect(char *word)
{
	char	*filename;
	int		fd_out;

	filename = NULL;
	word++;
	fd_out = 0;
	while (*word == ' ' || *word == '\t')
		word++;
	filename = ft_substr(word, 0, ft_strlen(word));
	if (!filename)
		ft_error(1);
	fd_out = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out == -1)
	{
		printf("%s\n", strerror(errno));
		return (-1);
	}
	return (fd_out);
}
