/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:27:30 by sandrzej          #+#    #+#             */
/*   Updated: 2026/01/22 16:27:31 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_pwd(t_shell **shell)
{
	t_env	*pwd;
	char	*tmp;

	pwd = find_key("PWD", (*shell)->envp);
	if (!pwd)
		return ;
	tmp = getcwd(NULL, 0);
	free(pwd->val);
	pwd->val = ft_strjoin("PWD=", tmp);
	free(tmp);
}

static int	cd_home(t_shell **shell)
{
	t_env	*envp;

	envp = find_key("HOME", (*shell)->envp);
	if (!envp)
	{
		(*shell)->last_exit_status = EXIT_FAILURE;
		printf("-bash: cd: HOME not set\n");
		return (1);
	}
	if (chdir(ft_strchr(envp->val, '=') + 1) == -1)
	{
		perror("-bash: cd");
		(*shell)->last_exit_status = EXIT_FAILURE;
		return (1);
	}
	update_pwd(shell);
	(*shell)->last_exit_status = EXIT_SUCCESS;
	return (0);
}

void	cd(char *input, t_shell **shell)
{
	char	*dir;

	if (!*input)
		dir = NULL;
	else
		dir = ft_strdup(input);
	if (!dir)
	{
		cd_home(shell);
		return ;
	}
	if (chdir(dir) == 0)
	{
		update_pwd(shell);
		(*shell)->last_exit_status = EXIT_SUCCESS;
	}
	else
	{
		perror("-bash: cd");
		(*shell)->last_exit_status = EXIT_FAILURE;
	}
	free(dir);
}
