#include "../../minishell.h"

void	cd(char *input, t_shell **shell)
{
	char	*dir;
  char  *tmp;

	dir = ft_strdup(ft_strnstr(input, " ", ft_strlen(input)) + 1);
	if (!chdir(dir))
	{
    tmp = (*shell)->pwd;
    (*shell)->pwd = getcwd(NULL, 0);
    free(tmp);
	}
	else
	{
		printf("-bash: cd: %s: No such file or directory\n", dir);
		free(dir);
	}
}
