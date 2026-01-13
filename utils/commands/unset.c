#include "../../minishell.h"

void	unset(char *input, t_shell **shell)
{
	t_env	*envp;

	if (!input || !ft_strnstr(input, " ", 6))
	{
		(*shell)->last_exit_status = 1;
		return ;
	}
	input = ft_strnstr(input, " ", 6) + 1;
	envp = find_key(input, (*shell)->envp);
	if (envp)
	{
		free(envp->val);
		envp->val = ft_strdup("");
	}
	(*shell)->last_exit_status = 0;
}
