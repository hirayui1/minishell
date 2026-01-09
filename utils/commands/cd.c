#include "../../minishell.h"

void	update_pwd(t_shell **shell)
{
	t_env	*pwd;
	char	*tmp;

	pwd = find_key("PWD", (*shell)->envp);
	if (pwd)
	{
		tmp = getcwd(NULL, 0);
		free(pwd->val);
		pwd->val = ft_strjoin("PWD=", tmp);
		free(tmp);
	}
}

void	cd(char *input, t_shell **shell)
{
	char	*dir;
	t_env	*envp;

	if (!ft_strncmp("cd", input, ft_strlen(input))
				|| !ft_strncmp("cd ", input, ft_strlen(input)))
		dir = 0;
	else
		dir = ft_strdup(ft_strnstr(input, " ", ft_strlen(input)) + 1);
	if (!dir)
	{
		envp = find_key("HOME", (*shell)->envp);
		if (!envp)
			return (printf("-bash: cd: HOME not set\n"), (void)0);
		chdir(envp->val);
		update_pwd(shell);
	}
	else if (!chdir(dir))
	{
		update_pwd(shell);
	}
	else
		printf("-bash: cd: %s: No such file or directory\n", dir);
	free(dir);
}
