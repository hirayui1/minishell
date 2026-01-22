/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:31:17 by sandrzej          #+#    #+#             */
/*   Updated: 2026/01/22 16:31:18 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	wait_for_children(int count, t_shell **shell)
{
	int	status;
	int	i;

	i = 0;
	while (i < count)
	{
		wait(&status);
		if (WIFEXITED(status))
			(*shell)->last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			(*shell)->last_exit_status = EXIT_CHILD_SUCCESS + WTERMSIG(status);
		i++;
	}
}
