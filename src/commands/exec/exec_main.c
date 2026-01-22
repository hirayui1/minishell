/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:31:06 by sandrzej          #+#    #+#             */
/*   Updated: 2026/01/22 16:31:07 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/* run external cmd with redirs */
int	try_exec_external(t_cmd *cmd, t_shell **shell)
{
	char	*dir;

	if (cmd->args[0][0] == '/')
		dir = ft_strdup(cmd->args[0]);
	else if (!access(cmd->args[0], F_OK))
		dir = ft_strdup(cmd->args[0]);
	else
		dir = find_path(cmd->args[0], shell);
	if (!dir)
	{
		(*shell)->last_exit_status = 127;
		return (printf("-bash: %s: command not found\n", cmd->args[0]), 1);
	}
	if (access(dir, X_OK))
	{
		(*shell)->last_exit_status = EXIT_NOT_EXECUTABLE;
		perror(dir);
		free(dir);
		return (0);
	}
	exe_with_redir(cmd, shell, dir);
	return (0);
}

/* fork and exec with redirs */
void	exe_with_redir(t_cmd *cmd, t_shell **shell, char *dir)
{
	int		status;
	char	**env;
	pid_t	pid;

	status = 0;
	env = lst_to_array((*shell)->envp);
	if (!env)
		return ;
	pid = fork();
	if (pid == 0)
		exe_redir_child(cmd, shell, dir, env);
	else if (pid > 0)
	{
		sig_manager(1);
		waitpid(pid, &status, 0);
		sig_manager(0);
		if (WIFEXITED(status))
			(*shell)->last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			(*shell)->last_exit_status = EXIT_SIGNAL_BASE + WTERMSIG(status);
		free_2d(env);
		free(dir);
	}
	else
		perror("fork");
}
