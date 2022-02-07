#include "minishell.h"

static char	**get_argv(t_store *token)
{
	char	**argv;

	if (strncmp(token->word, ">", 1) && strncmp(token->word, "<", 1))
		argv = split_token_word(token->word);
	else
		argv = NULL;
	return (argv);
}

static void	error_command(void)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putnbr_fd(g_sh.exit_code, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	builtin(char **argv, int count, t_env *env, t_env *export)
{
	if (ft_strncmp(argv[0], "echo", 4) == 0)
		our_echo(argv);
	else if (ft_strncmp(argv[0], "pwd", 3) == 0)
		our_pwd(argv);
	else if (ft_strncmp(argv[0], "cd", 2) == 0)
		our_cd(count, argv, env, export);
	else if (ft_strncmp(argv[0], "export", 6) == 0)
		our_export(count, env, export, argv);
	else if (ft_strncmp(argv[0], "unset", 5) == 0)
		our_unset(env, export, argv, count);
	else if (ft_strncmp(argv[0], "env", 3) == 0)
		our_env(env, argv, count);
}

int	command_handler(t_env *env, t_env *export, t_store *token, char **envp)
{
	int		count;
	char	**argv;

	argv = get_argv(token);
	count = count_argument(argv);
	if (argv)
	{
		if (!ft_strncmp(argv[0], "echo", 4) || !ft_strncmp(argv[0], "pwd", 3) || \
			!ft_strncmp(argv[0], "cd", 2) || !ft_strncmp(argv[0], "export", 6) || \
			!ft_strncmp(argv[0], "unset", 5) || !ft_strncmp(argv[0], "env", 3))
			builtin(argv, count, env, export);
		else if (ft_strcmp(argv[0], "$?") == 0)
		{
			error_command();
			ft_clearing(argv);
			return (0);
		}
		else if (ft_strcmp(argv[0], "exit") == 0)
			free_exit(token, env, export, 0);
		else
			exec_bin(argv, env, envp);
	}
	g_sh.exit_code = 0;
	return (0);
}
