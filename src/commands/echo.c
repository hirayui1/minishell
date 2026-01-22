/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:27:35 by sandrzej          #+#    #+#             */
/*   Updated: 2026/01/22 16:27:37 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	echo(char *input, t_shell **shell)
{
	char	*trimmed;

	input = ft_strnstr(input, " ", ECHO_OFFSET);
	if (!input || !*(++input))
		return (printf("\n"), (*shell)->last_exit_status = 0, (void)0);
	if (!ft_strncmp("-n ", input, N_OPTION_OFFSET))
	{
		trimmed = ft_strtrim(input + N_OPTION_OFFSET, " ");
		printf("%s", trimmed);
		free(trimmed);
	}
	else
		printf("%s\n", input);
	(*shell)->last_exit_status = 0;
}
