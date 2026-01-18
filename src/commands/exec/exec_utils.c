#include "../../../minishell.h"

/* child: run execve */
void	exe_child(char *dir, char **split, char **env, t_shell **shell)
{
	sig_manager(1);
	execve(dir, split, env);
	perror(split[0]);
	if (errno == ENOENT)
		ft_exit(shell, NULL, EXIT_CMD_NOT_FOUND);
	else if (errno == EACCES)
		ft_exit(shell, NULL, EXIT_NOT_EXECUTABLE);
	else
		ft_exit(shell, NULL, 1);
	exit(1);
}

/* parent: get exit status */
void	exe_parent(int status, char **env, t_shell **shell)
{
	if (WIFEXITED(status))
		(*shell)->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		(*shell)->last_exit_status = EXIT_SIGNAL_BASE + WTERMSIG(status);
	free_2d(env);
}

/* search PATH dirs for cmd */
char	*check_access(char *filename, char **path)
{
	int		i;
	char	*dir;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		dir = ft_strjoin(tmp, filename);
		free(tmp);
		if (!access(dir, F_OK))
			return (free_2d(path), dir);
		free(dir);
		i++;
	}
	return (free_2d(path), NULL);
}

/* lookup cmd in PATH */
char	*find_path(char *filename, t_shell **shell)
{
	char	**path;
	char	*dir;
	t_env	*envp;

	envp = find_key("PATH", (*shell)->envp);
	if (!envp)
		return (NULL);
	path = ft_split(envp->val + PATH_OFFSET, ':');
	dir = check_access(filename, path);
	return (dir);
}

/* child: setup redirs and exec */
void	exe_redir_child(t_cmd *cmd, t_shell **shell, char *dir, char **env)
{
	sig_manager(1);
	apply_heredoc_fd(cmd->heredoc_fd);
	setup_redirections(cmd->redirs);
	execve(dir, cmd->args, env);
	perror(cmd->args[0]);
	if (errno == ENOENT)
		ft_exit(shell, NULL, EXIT_CMD_NOT_FOUND);
	else if (errno == EACCES)
		ft_exit(shell, NULL, EXIT_NOT_EXECUTABLE);
	else
		ft_exit(shell, NULL, 1);
	exit(1);
}
