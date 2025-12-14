#include "../../minishell.h"

void	pwd(t_shell **shell)
{
	printf("%s\n", (*shell)->pwd);
}
