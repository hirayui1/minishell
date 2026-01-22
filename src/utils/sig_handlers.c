#include "../../minishell.h"

static void	sigint_action(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

static void	sigint_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

static void	sigint_parent(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	sig_manager(int level)
{
	struct sigaction	psa;

	sigemptyset(&psa.sa_mask);
	psa.sa_flags = 0;
	if (level == 1)
		psa.sa_handler = sigint_parent;
	else if (level == 2)
		psa.sa_handler = sigint_heredoc;
	else if (level == 3)
		psa.sa_handler = SIG_DFL;
	else
	{
		psa.sa_flags = SA_RESTART;
		psa.sa_handler = sigint_action;
	}
	sigaction(SIGINT, &psa, NULL);
	if (level == 3)
		psa.sa_handler = SIG_DFL;
	else
		psa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &psa, NULL);
}
