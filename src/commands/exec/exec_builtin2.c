/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarabab <bkarabab@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 10:00:00 by sandrzej          #+#    #+#             */
/*   Updated: 2026/01/24 09:57:04 by bkarabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static char	*get_arg_or_empty(char **args)
{
	if (args[1])
		return (args[1]);
	return ("");
}

static void	run_echo(t_cmd *cmd, t_shell **shell)
{
	char	*echo_input;
	char	*tmp;
	int		i;

	if (!cmd->args[1])
	{
		printf("\n");
		(*shell)->last_exit_status = EXIT_SUCCESS;
		return ;
	}
	if (!ft_strncmp(cmd->args[1], "-n", 3) && !cmd->args[2])
		return ((*shell)->last_exit_status = EXIT_SUCCESS, (void)0);
	echo_input = ft_strdup("echo");
	i = 1;
	while (cmd->args[i])
	{
		tmp = ft_strjoin(echo_input, " ");
		free(echo_input);
		echo_input = ft_strjoin(tmp, cmd->args[i]);
		free(tmp);
		i++;
	}
	echo(echo_input, shell);
	free(echo_input);
}

static int	run_arg_builtin(t_cmd *cmd, t_shell **shell)
{
	if (!ft_strncmp(cmd->args[0], "cd", 3))
	{
		cd(get_arg_or_empty(cmd->args), shell);
		return (1);
	}
	if (!ft_strncmp(cmd->args[0], "unset", 6))
	{
		unset(get_arg_or_empty(cmd->args), shell);
		return (1);
	}
	if (!ft_strncmp(cmd->args[0], "export", 7))
	{
		exprt(get_arg_or_empty(cmd->args), shell);
		return (1);
	}
	return (0);
}

static int	run_simple_builtin(t_cmd *cmd, t_shell **shell)
{
	if (!ft_strncmp(cmd->args[0], "pwd", 4))
		return (pwd(shell), 1);
	if (!ft_strncmp(cmd->args[0], "env", 4))
		return (print_env(shell), 1);
	if (!ft_strncmp(cmd->args[0], "echo", 5))
		return (run_echo(cmd, shell), 1);
	if (!ft_strncmp(cmd->args[0], "exit", 5))
		return (builtin_exit(cmd, shell), 1);
	return (0);
}

void	execute_builtin(t_cmd *cmd, t_shell **shell)
{
	if (setup_redirections(cmd->redirs))
	{
		(*shell)->last_exit_status = EXIT_FAILURE;
		return ;
	}
	if (run_arg_builtin(cmd, shell))
		return ;
	run_simple_builtin(cmd, shell);
}
