#include "../../minishell.h"

void	print_env(t_shell **shell)
{
	int	i;
	char	**envp;

	envp = (*shell)->envp;
	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
}
