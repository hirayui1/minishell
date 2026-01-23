/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:31:02 by sandrzej          #+#    #+#             */
/*   Updated: 2026/01/22 16:31:03 by sandrzej         ###   ########.fr       */
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

/* rebuild echo input string */
static void	run_echo(t_cmd *cmd, t_shell **shell)
{
	char	*echo_input;
	char	*tmp;
	int		i;

	echo_input = ft_strdup("echo");
	i = 1;
	while (cmd->args[i])
	{
		tmp = ft_strjoin(echo_input, " ");
		free(echo_input);
		echo_input = ft_strjoin(tmp, cmd->args[i]);
		free(tmp);
		++i;
	}
	echo(echo_input, shell);
	free(echo_input);
}

/* run builtin with redirs */
void	execute_builtin(t_cmd *cmd, t_shell **shell)
{
	if (setup_redirections(cmd->redirs))
    	return ((*shell)->last_exit_status=EXIT_FAILURE, (void)0);
	if (!ft_strncmp(cmd->args[0], "cd", 3))
	{
		if (cmd->args[1])
			cd(cmd->args[1], shell);
		else
			cd("", shell);
	}
	else if (!ft_strncmp(cmd->args[0], "pwd", 4))
		pwd(shell);
	else if (!ft_strncmp(cmd->args[0], "env", 4))
		print_env(shell);
	else if (!ft_strncmp(cmd->args[0], "unset", 6))
	{
		if (cmd->args[1])
			unset(cmd->args[1], shell);
		else
			unset("", shell);
	}
	else if (!ft_strncmp(cmd->args[0], "export", 7))
	{
		if (cmd->args[1])
			exprt(cmd->args[1], shell);
		else
			exprt("", shell);
	}
	else if (!ft_strncmp(cmd->args[0], "echo", 5))
		run_echo(cmd, shell);
	else if (!ft_strncmp(cmd->args[0], "exit", 5))
		builtin_exit(cmd, shell);
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
