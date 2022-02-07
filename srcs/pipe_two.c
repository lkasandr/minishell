#include "minishell.h"

void	check_and_handler(t_env *env, t_env *export, t_store *tmp, char **envp)
{
	if (check_redirect_in_pipe(tmp->word))
		redir_in_pipe(env, export, envp, tmp);
	else
		command_handler(env, export, tmp, envp);
	exit(0);
}

void	our_pipe(t_store *tmp, t_env *env, t_env *export, char **envp)
{
	int			fd[2];
	int			fd2[2];
	int			i;
	pid_t		pid[4000];
	int			len;

	i = 0;
	len = token_size(tmp);
	while (tmp != NULL)
	{
		pipe(fd);
		pid[i] = fork();
		if (pid[i] == 0)
		{
			change_fd_pipe(i, fd, fd2, len);
			check_and_handler(env, export, tmp, envp);
		}
		else
		{
			close_fd(fd, fd2, i);
			tmp = tmp->next;
			i++;
		}
	}
	waiting_pids(i);
}

int	pipe_proc(t_env *env, char **envp, t_env *export, t_store *token)
{
	t_store	*tmp;

	tmp = get_pipe_struct(token);
	our_pipe(tmp, env, export, envp);
	return (1);
}
