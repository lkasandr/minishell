#include "minishell.h"

void	setup_term(void)
{
	struct termios	mini;

	tcgetattr(0, &mini);
	mini.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &mini);
}

void	init_and_fill(t_env *env, char **envp, t_env *export)
{
	init_mini();
	setup_term();
	init_struct_env(env);
	fill_struct_env(envp, env);
	init_struct_env(export);
	fill_struct_env(envp, export);
}

void	mini_loop(t_store *token, t_env *env, t_env *export, char **envp)
{
	char	*str;

	g_sh.pipe_flag = 0;
	g_sh.fd_in_old = dup(STDIN_FILENO);
	g_sh.fd_out_old = dup(STDOUT_FILENO);
	token = (t_store *)malloc(sizeof(t_store));
	if (!token)
		ft_error(1);
	str = NULL;
	init_struct_store(token);
	str = readline("minishell$ ");
	add_history(str);
	if (parser(str, env, &token, export) != -1)
		execute_command(env, export, token, envp);
	free(str);
	free_struct_store(token);
	dup2(g_sh.fd_out_old, 1);
	dup2(g_sh.fd_in_old, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_store	*token;
	t_env	*env;
	t_env	*export;

	(void)argc;
	(void)argv;
	token = NULL;
	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		ft_error(1);
	export = (t_env *)malloc(sizeof(t_env));
	if (!export)
		ft_error(1);
	init_and_fill(env, envp, export);
	signal(SIGINT, (void *) our_sig_proc);
	signal(SIGQUIT, (void *)our_sig_proc);
	while (1)
	{
		mini_loop(token, env, export, envp);
	}
	sleep(100);
	return (0);
}
