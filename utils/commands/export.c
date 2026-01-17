#include "../../minishell.h"

void	exprt(char *input, t_shell **shell)
{
	if (!*input)
	{
		(*shell)->last_exit_status = 0;
		return ;
	}
	if (ft_strchr(input, '='))
		lst_append(input, (*shell)->envp);
	(*shell)->last_exit_status = 0;
}