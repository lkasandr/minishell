#include "minishell.h"

void	push_start(t_store **token, char *join)
{
	t_store	*p;

	p = (t_store *)malloc(sizeof(t_store));
	if (!p)
		ft_error(1);
	p->word = ft_strdup(join);
	p->next = *token;
	*token = p;
}

char	*join_token(char *str, t_env *env, t_store **token, int flag)
{
	char	*tmp;
	char	*join;
	int		i;

	i = 0;
	join = NULL;
	while (*str == ' ' || *str == '\t')
		str++;
	while (str[i] && str[i] != '>' && str[i] != '<' && str[i] != '|')
	{
		str = handler_quot(str, i, env);
		i++;
	}
	join = ft_substr(str, 0, i);
	if (flag == 1)
		(*token)->word = ft_strjoin((*token)->word, join);
	if (flag == 0)
		push_start(token, join);
	free(join);
	tmp = ft_substr(str, i, ft_strlen(str) - i);
	if (!tmp)
		return (NULL);
	return (tmp);
}

void	check_exit(char *str, t_store *token, t_env *env, t_env *export)
{
	if (!str || *str == '\4' || *str == EOF)
	{
		printf("\033[Aminishell$ exit\n");
		free_exit(token, env, export, 0);
	}
}

static void	error_str(char *str)
{
	if (!str)
		ft_error(1);
}

void	parse_redir_pipe(char *str, t_env *env, t_store **token, int flag)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			str = process_redirect(str, env, *token);
			error_str(str);
			i = -1;
		}
		if (str[i] == '|')
		{
			str = process_pipe(str, env, *token);
			error_str(str);
			i = -1;
		}
		if (str[i] != '>' && str[i] != '<' && str[i] != ' ' && str[i] != '|')
		{
			str = join_token(str, env, token, flag);
			error_str(str);
			i = -1;
		}
		i++;
	}
}
