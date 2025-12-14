#include "../minishell.h"

void	ft_exit(t_shell **shell, char **input, int exit_code)
{
	if (*input)
	{
		free(*input);
	}
	if (*shell) // TODO: destroy node and update variable func
	{
		if ((*shell)->pwd)
			free((*shell)->pwd);
		free(*shell);
		shell = 0;
	}
	exit(exit_code);
}
