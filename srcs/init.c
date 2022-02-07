#include "minishell.h"

void	init_struct_store(t_store *token)
{
	token->word = NULL;
	token->next = NULL;
}

void	init_mini(void)
{
	g_sh.exit_code = 0;
	g_sh.fork_status = 0;
	g_sh.pipe_flag = 0;
}

void	init_struct_env(t_env *env)
{
	env->key = NULL;
	env->value = NULL;
	env->next = NULL;
}
