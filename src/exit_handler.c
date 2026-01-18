#include "../minishell.h"

void	ft_exit(t_shell **shell, char **input, int exit_code)
{
	if (input && *input)
		free(*input);
	cleanup_shell(shell);
	clear_history();
	exit(exit_code);
}
