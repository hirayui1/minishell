#include "../../minishell.h"

void	unset(char *input, t_shell **shell)
{
	t_env	*envp;

	input = ft_strnstr(input, " ", 6) + 1;
	envp = find_key(input, (*shell)->envp);
	if (envp)
	{
		free(envp->val);
		envp->val = ft_strdup(""); // TODO: probably sucks, but we'll see
	}
	// make it doubly linked list so that you can easily tie prev and next and
	// free current
}
