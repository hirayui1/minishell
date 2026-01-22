#include "../../../minishell.h"

void	wait_for_children(int count, t_shell **shell)
{
	int	status;
	int	i;

	i = 0;
	while (i < count)
	{
		wait(&status);
		if (WIFEXITED(status))
			(*shell)->last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			(*shell)->last_exit_status = EXIT_SIGNAL_BASE + WTERMSIG(status);
		i++;
	}
}
