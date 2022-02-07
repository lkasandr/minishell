#include "minishell.h"

void	redir_in_pipe(t_env *env, t_env *export, char **envp, t_store *tmp)
{
	t_store	*redir;
	char	*word;
	int		i;

	word = NULL;
	i = 0;
	redir = (t_store *)malloc(sizeof(t_store));
	if (!redir)
		ft_error(1);
	redir->word = NULL;
	redir->next = NULL;
	while (tmp->word[i] != '>' && tmp->word[i] != '<')
		i++;
	if (!redir->word)
		redir->word = ft_substr(tmp->word, 0, i);
	else
	{
		word = ft_substr(tmp->word, i, ft_strlen(tmp->word) - i);
		redir = add_node_token(redir, word, ft_strlen(word));
	}
	execute_command(env, export, redir, envp);
}

void	change_fd_pipe(int i, int fd[2], int fd2[2], int len)
{
	if (i == 0)
	{	
		close(fd[0]);
		dup2(fd[1], 1);
	}
	else if (i == len - 1)
	{
		close(fd[1]);
		dup2(fd2[0], 0);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd2[1]);
		dup2(fd2[0], 0);
	}
}

void	close_fd(int fd[2], int fd2[2], int i)
{
	if (i > 0)
		close(fd2[0]);
	close(fd[1]);
	fd2[0] = fd[0];
	fd2[1] = fd[1];
}

void	waiting_pids(int i)
{
	int		status;

	while (i > 0)
	{
		wait(&status);
		if (WIFEXITED(status))
			g_sh.exit_code = WEXITSTATUS(status);
		i--;
	}
}

void	pid_err(char *str)
{
	ft_putendl_fd(str, 2);
	g_sh.exit_code = 1;
	exit(1);
}
