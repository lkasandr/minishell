#include "minishell.h"

int	double_right_redirect(char *word)
{
	char	*filename;
	int		fd_out;

	word++;
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

int	left_redirect(char *word)
{
	char	*filename;
	int		fd_in;

	word++;
	fd_in = 0;
	while (*word == ' ' || *word == '\t')
		word++;
	filename = ft_substr(word, 0, ft_strlen(word));
	if (!filename)
		ft_error(1);
	fd_in = open(filename, O_RDONLY, 0644);
	if (fd_in == -1)
	{
		printf("%s\n", strerror(errno));
		return (-1);
	}
	return (fd_in);
}

static void	redir_loop(char *filename, t_env *env, int fd_out)
{
	char	*str;

	str = NULL;
	str = readline("> ");
	while (str && ft_strcmp(str, filename))
	{
		str = process_str_redirect(str, env);
		ft_putstr_fd(str, fd_out);
		ft_putchar_fd('\n', fd_out);
		free(str);
		str = readline("> ");
	}
	free(str);
}

void	double_left_redirect(char *word, t_env *env, t_store *token)
{
	char	*filename;
	int		fd_out;
	int		fd_out_old;

	word++;
	word++;
	while (*word == ' ' || *word == '\t')
		word++;
	filename = ft_substr(word, 0, ft_strlen(word));
	if (!filename)
		ft_error(1);
	fd_out = open("heredoc", O_CREAT | O_WRONLY | O_EXCL, 0644);
	if (fd_out == -1)
		printf("%s\n", strerror(errno));
	fd_out_old = dup(1);
	redir_loop(filename, env, fd_out);
	close(fd_out);
	dup2(fd_out_old, fd_out);
	our_redirect("< heredoc", env, token);
	if (unlink("heredoc") == -1)
	{
		printf("%s\n", strerror(errno));
		g_sh.exit_code = 1;
	}
}

int	our_redirect(char *word, t_env *env, t_store *token)
{
	int		i;
	int		fd_in;
	int		fd_out;

	i = 0;
	fd_in = 0;
	fd_out = 1;
	if (word[i] == '>' && word[i + 1] != '>')
		fd_out = right_redirect(word);
	else if (word[i] == '>' && word[i + 1] == '>')
		fd_out = double_right_redirect(word);
	else if (word[i] == '<' && word[i + 1] != '<')
		fd_in = left_redirect(word);
	else if (word[i] == '<' && word[i + 1] == '<')
	{
		double_left_redirect(word, env, token);
		if (g_sh.exit_code == 1)
			return (0);
	}
	if (fd_out == -1 || fd_in == -1)
		return (0);
	dup2(fd_out, 1);
	dup2(fd_in, 0);
	return (1);
}
