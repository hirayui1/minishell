/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarabab <bkarabab@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 09:53:33 by bkarabab          #+#    #+#             */
/*   Updated: 2026/01/24 09:53:34 by bkarabab         ###   ########.fr       */
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
	(*shell)->last_exit_status = EXIT_SUCCESS;
}
