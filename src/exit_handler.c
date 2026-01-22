/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:26:59 by sandrzej          #+#    #+#             */
/*   Updated: 2026/01/22 16:27:01 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_shell **shell, char **input, int exit_code)
{
	if (input && *input)
		free(*input);
	cleanup_shell(shell);
	clear_history();
	exit(exit_code);
}

void	builtin_exit(t_cmd *cmd, t_shell **shell)
{
	int	code;

	printf("exit\n");
	code = (*shell)->last_exit_status;
	if (cmd->args[1])
	{
		if (!is_numeric(cmd->args[1]))
		{
			printf("minishell: exit: numeric argument required\n");
			code = 2;
		}
		else
			code = ft_atoi(cmd->args[1]) % 256;
	}
	free_cmd(cmd);
	ft_exit(shell, NULL, code);
}
