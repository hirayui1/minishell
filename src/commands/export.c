/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:27:43 by sandrzej          #+#    #+#             */
/*   Updated: 2026/01/22 16:27:43 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exprt(char *input, t_shell **shell)
{
	if (!*input)
	{
		(*shell)->last_exit_status = 0;
		return ;
	}
	if (ft_strchr(input, '='))
		lst_append(input, (*shell)->envp);
	(*shell)->last_exit_status = 0;
}
