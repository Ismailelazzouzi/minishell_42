#include "minishell.h"

void	setup_signal_handlers(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_ctrl_c(int a)
{
	(void)a;
	g_var_tn = 1;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}



void	child_ctrl_c(int sig_num)
{
	if (sig_num == 2)
		g_var_tn = 130;
	else
	{
		ft_putstr_fd("Quit", 1);
		g_var_tn = 131;
	}
	write(1, "\n", 1);
} 