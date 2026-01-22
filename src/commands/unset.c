/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:27:49 by sandrzej          #+#    #+#             */
/*   Updated: 2026/01/22 16:27:50 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	unset(char *input, t_shell **shell)
{
	t_env	*envp;

	if (!*input)
	{
		(*shell)->last_exit_status = 0;
		return ;
	}
	envp = find_key(input, (*shell)->envp);
	if (envp)
	{
		free(envp->val);
		envp->val = ft_strdup("");
	}
	(*shell)->last_exit_status = 0;
}
