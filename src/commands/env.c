#include "../../minishell.h"

void	print_env(t_shell **shell)
{
	t_env	*envp;

	envp = (*shell)->envp;
	while (envp)
	{
		if (envp->val[0])
			printf("%s\n", envp->val);
		envp = envp->next;
	}
	(*shell)->last_exit_status = EXIT_SUCCESS;
}
