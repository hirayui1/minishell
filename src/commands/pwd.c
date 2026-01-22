/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:27:46 by sandrzej          #+#    #+#             */
/*   Updated: 2026/01/22 16:27:47 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	}
	free(tmp);
	(*shell)->last_exit_status = 0;
}
