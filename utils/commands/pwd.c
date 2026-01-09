#include "../../minishell.h"

void	pwd(t_shell **shell)
{
	t_env	*envp;
	char	*tmp;

	//TODO: print from pwd and now envp, update envp if exists
	tmp = getcwd(NULL, 0);
	printf("%s\n", tmp);
	envp = find_key("PWD", (*shell)->envp);
	if (envp)
	{
		free(envp->val);
		envp->val = ft_strjoin("PWD=", tmp);
		free(tmp);
	}
	else
		free(tmp);
	//printf("%s\n", (*shell)->pwd);
}
