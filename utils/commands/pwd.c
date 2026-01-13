#include "../../minishell.h"

void	pwd(t_shell **shell)
{
	t_env	*envp;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (!tmp)
	{
		perror("pwd");
		(*shell)->last_exit_status = 1;
		return ;
	}
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
	(*shell)->last_exit_status = 0;
}
