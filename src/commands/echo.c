/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarabab <bkarabab@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 09:53:58 by bkarabab          #+#    #+#             */
/*   Updated: 2026/01/24 09:53:59 by bkarabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	echo(char *input, t_shell **shell)
{
	char	*trimmed;

	input = ft_strnstr(input, " ", ECHO_OFFSET);
	if (!input || !*(++input))
		printf("\n");
	if (!ft_strncmp("-n ", input, N_OPTION_OFFSET))
	{
		trimmed = ft_strtrim(input + N_OPTION_OFFSET, " ");
		printf("%s", trimmed);
		free(trimmed);
	}
	else
		printf("%s\n", input);
	(*shell)->last_exit_status = EXIT_SUCCESS;
}
