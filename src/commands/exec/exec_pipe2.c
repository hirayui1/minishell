/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarabab <bkarabab@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:31:12 by sandrzej          #+#    #+#             */
/*   Updated: 2026/01/24 09:58:08 by bkarabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	setup_pipe_fds(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

void	pipe_exec_external(t_cmd *cmd, t_shell **shell)
{
	char	*dir;
	char	**env;

	dir = find_path(cmd->args[0], shell);
	if (!dir)
		dir = ft_strdup(cmd->args[0]);
	env = lst_to_array((*shell)->envp);
	execve(dir, cmd->args, env);
	free_2d(env);
	perror(cmd->args[0]);
	free(dir);
	free_pipeline((*shell)->pl);
	cleanup_shell(shell);
	exit(EXIT_CMD_NOT_FOUND);
}

void	child_process_helper(t_cmd *cmd, t_shell **shell)
{
	int	status;

	if (setup_redirections(cmd->redirs))
	{
		free_pipeline((*shell)->pl);
		cleanup_shell(shell);
		exit(EXIT_FAILURE);
	}
	if (!cmd->args || !cmd->args[0])
	{
		free_pipeline((*shell)->pl);
		cleanup_shell(shell);
		exit(EXIT_SUCCESS);
	}
	else if (is_builtin(cmd->args))
	{
		execute_builtin(cmd, shell);
		status = (*shell)->last_exit_status;
		free_pipeline((*shell)->pl);
		cleanup_shell(shell);
		exit(status);
	}
}

void	child_process(t_cmd *cmd, int in_fd, int out_fd, t_shell **shell)
{
	sig_manager(3);
	setup_pipe_fds(in_fd, out_fd);
	apply_heredoc_fd(cmd->heredoc_fd);
	child_process_helper(cmd, shell);
	pipe_exec_external(cmd, shell);
}

void	run_pipe_cmd(t_cmd *cmd, int *in_fd, int pipefd[2], t_shell **shell)
{
	pid_t	pid;
	int		out_fd;

	if (cmd->next)
		out_fd = pipefd[1];
	else
		out_fd = STDOUT_FILENO;
	pid = fork();
	if (pid == 0)
	{
		if (cmd->next)
			close(pipefd[0]);
		child_process(cmd, *in_fd, out_fd, shell);
	}
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	if (cmd->next)
	{
		close(pipefd[1]);
		*in_fd = pipefd[0];
	}
}
