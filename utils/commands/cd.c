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
	if (!dir) // TODO: split these into smaller functions later
	{
		envp = find_key("HOME", (*shell)->envp);
		if (!envp)
		{
			printf("-bash: cd: HOME not set\n");
			(*shell)->last_exit_status = 1;
			return ;
		}
		if (chdir(ft_strchr(envp->val, '=') + 1) == -1)
		{
			perror("-bash: cd");
			(*shell)->last_exit_status = 1;
		}
		else
		{
			update_pwd(shell);
			(*shell)->last_exit_status = 0;
		}
	}
	else if (chdir(dir) == 0)
	{
		update_pwd(shell);
		(*shell)->last_exit_status = 0;
	}
	else
	{
		perror("-bash: cd");
		(*shell)->last_exit_status = 1;
	}
	free(dir);
}
