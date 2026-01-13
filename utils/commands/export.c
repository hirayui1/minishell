#include "../../minishell.h"

void	exprt(char *input, t_shell **shell)
{
	if (!ft_strnstr(input, " ", 7))
	{
		(*shell)->last_exit_status = 1;
		return ;
	}
	input = ft_strnstr(input, " ", 7) + 1;
	if (ft_strchr(input, '='))
		lst_append(input, (*shell)->envp);
	(*shell)->last_exit_status = 0;
}