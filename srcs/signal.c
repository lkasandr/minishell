#include "minishell.h"

void	our_sig_proc(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		if (g_sh.fork_status == 1)
			g_sh.exit_code = 1;
		else
			g_sh.exit_code = 130;
	}
	else if (sig == SIGQUIT)
	{
		if (g_sh.fork_status == 1)
			write(1, "Quit: 3", 7);
		g_sh.exit_code = 131;
		rl_on_new_line();
		rl_redisplay();
	}
}
