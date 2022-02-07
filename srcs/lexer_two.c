#include "minishell.h"

int	parser(char *str, t_env *env, t_store **token, t_env *export)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	check_exit(str, *token, env, export);
	while (*str == ' ' || *str == '\t')
		str++;
	while (str[i] && str[i] != '|' && str[i] != '>' && str[i] != '<')
	{
		str = handler_quot(str, i, env);
		i++;
	}
	if (i != 0)
	{
		flag = 1;
		(*token)->word = ft_substr(str, 0, i);
		if (!(*token)->word)
			ft_error(1);
		str = ft_substr(str, i, ft_strlen(str));
		if (!str)
			ft_error(1);
	}
	parse_redir_pipe(str, env, token, flag);
	return (0);
}

int	count(char *word)
{
	int	i;
	int	count_word;

	i = 0;
	count_word = 0;
	while (word[i])
	{
		if (word[i] == '|')
		{
			word[i] = ' ';
			i++;
		}
		if (word[i] == ' ')
		{
			while (word[i] == ' ')
				i++;
			count_word++;
		}
		i++;
	}
	count_word++;
	return (count_word);
}

char	**split_token_word(char *word)
{
	char	**argv;
	int		i;
	int		count_word;

	i = 0;
	count_word = 0;
	count_word = count(word);
	argv = ft_split(word, ' ');
	if (!argv)
		ft_error(1);
	return (argv);
}

int	count_argument(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	check_redirect(t_store *token, t_env *env)
{
	t_store	*p;

	p = token;
	while (p)
	{
		if (!ft_strncmp(p->word, ">", 1) || !ft_strncmp(p->word, "<", 1))
		{
			if (!our_redirect(p->word, env, token))
				return (0);
		}
		p = p->next;
	}
	return (1);
}
