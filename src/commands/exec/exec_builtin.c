/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarabab <bkarabab@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 09:52:23 by bkarabab          #+#    #+#             */
/*   Updated: 2026/01/24 09:52:23 by bkarabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/* check if cmd is builtin */
int	is_builtin(char **args)
{
	if (!args || !args[0])
		return (0);
	if (!ft_strncmp(args[0], "cd", 3))
		return (1);
	else if (!ft_strncmp(args[0], "pwd", 4))
		return (1);
	else if (!ft_strncmp(args[0], "env", 4))
		return (1);
	else if (!ft_strncmp(args[0], "unset", 6))
		return (1);
	else if (!ft_strncmp(args[0], "export", 7))
		return (1);
	else if (!ft_strncmp(args[0], "echo", 5))
		return (1);
	else if (!ft_strncmp(args[0], "exit", 5))
		return (1);
	return (0);
}

/* run builtin in child */
void	execute_builtin_fork(t_cmd *cmd, t_shell **shell)
{
	int	exit_status;

	apply_heredoc_fd(cmd->heredoc_fd);
	execute_builtin(cmd, shell);
	exit_status = (*shell)->last_exit_status;
	free_cmd(cmd);
	cleanup_shell(shell);
	exit(exit_status);
}

/* run cmd (builtin or external) */
void	execute_command(t_cmd *cmd, t_shell **shell)
{
	pid_t	pid;

	if (!is_builtin(cmd->args))
		return (try_exec_external(cmd, shell), (void)0);
	if (!cmd->redirs)
		return (execute_builtin(cmd, shell), (void)0);
	pid = fork();
	if (pid == 0)
		execute_builtin_fork(cmd, shell);
	else
		waitpid(pid, NULL, 0);
}
