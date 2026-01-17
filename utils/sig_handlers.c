#include "../minishell.h"

static void	sigint_action(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	sig_manager(int level)
{
	struct sigaction	psa;

	sigemptyset(&psa.sa_mask);
	psa.sa_flags = SA_RESTART;
	if (level)
		psa.sa_handler = SIG_IGN;
	else
		psa.sa_handler = sigint_action;
	sigaction(SIGINT, &psa, NULL);
	psa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &psa, NULL);
}
