#include "../../minishell.h"

void	exprt(char *input, t_shell **shell)
{
	input = ft_strnstr(input, " ", 7) + 1;
	if (ft_strchr(input, '='))
		lst_append(input, (*shell)->envp);
}
