/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:27:38 by sandrzej          #+#    #+#             */
/*   Updated: 2026/01/22 16:27:39 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_env(t_shell **shell)
{
	t_env	*envp;

	envp = (*shell)->envp;
	while (envp)
	{
		if (envp->val[0])
			printf("%s\n", envp->val);
		envp = envp->next;
	}
	(*shell)->last_exit_status = 0;
}
