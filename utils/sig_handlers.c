#include "../minishell.h"

/**
 * @brief  if ctrl+C (SIGINT) sent, move onto a new readline 
 * 	   replace_line having 1 is still questionable as it
 * 	   clears the undo list
 *
 * @param sig  unused signal value as this funct only handles SIGINT
 *
 * @TODO  this should be able to quit processes later.
 */
void	sigint_action(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

/**
 * @brief  Initialize signal action handlers
 * 	   SIGINT: newline empty prompt
 * 	   SIGQUIT: ignore
 */
void	sig_manager(void)
{
	struct sigaction	psa;

	sigemptyset(&psa.sa_mask);
	psa.sa_handler = sigint_action;
	psa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &psa, NULL);
	psa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &psa, NULL);
}
