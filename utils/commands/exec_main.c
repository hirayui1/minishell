#include "../../minishell.h"

/*
** resolve_dir - Resolve path for command execution
*/
static char	*resolve_dir(char **split, t_shell **shell, int *flag)
{
	char	*dir;

	*flag = 1;
	if (split[0][0] == '/')
		return (split[0]);
	else if (!access(split[0], F_OK))
		return (split[0]);
	*flag = 0;
	dir = find_path(split[0], shell);
	return (dir);
}

/*
** exe - Execute external command in child process
*/
void	exe(char *dir, char **split, t_shell **shell)
{
	int		status;
	char	**env;
	pid_t	pid;

	env = lst_to_array((*shell)->envp);
	if (!env)
		return ;
	pid = fork();
	if (pid == 0)
		exe_child(dir, split, env, shell);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		exe_parent(status, env, shell);
	}
	else
		perror("bash");
}

/*
** try_exec - Locate and execute command from input string
*/
int	try_exec(char *input, t_shell **shell)
{
	char	**split;
	char	*dir;
	int		flag;

	input = ft_strtrim(input, " ");
	split = ft_split(input, ' ');
	dir = resolve_dir(split, shell, &flag);
	free(input);
	if (!dir)
		return (free_2d(split), 1);
	if (access(dir, X_OK) != 0)
	{
		(*shell)->last_exit_status = EXIT_NOT_EXECUTABLE;
		perror("permission denied");
		free_2d(split);
		if (!flag)
			free(dir);
		return (0);
	}
	exe(dir, split, shell);
	if (!flag)
		free(dir);
	free_2d(split);
	return (0);
}

/*
** try_exec_external - Find and execute external command with redirections
*/
int	try_exec_external(t_cmd *cmd, t_shell **shell)
{
	char	*dir;
	int		flag;

	flag = 1;
	if (cmd->args[0][0] == '/')
		dir = cmd->args[0];
	else if (!access(cmd->args[0], F_OK))
		dir = cmd->args[0];
	else
	{
		flag = 0;
		dir = find_path(cmd->args[0], shell);
	}
	if (!dir)
	{
		(*shell)->last_exit_status = 127;
		return (printf("-bash: %s: command not found\n", cmd->args[0]), 1);
	}
	if (access(dir, X_OK))
	{
		(*shell)->last_exit_status = EXIT_NOT_EXECUTABLE;
		perror("permission denied");
		if (!flag)
			free(dir);
		return (0);
	}
	exe_with_redir(cmd, shell, dir, flag);
	return (0);
}

/*
** exe_with_redir - Execute external command with redirections
*/
void	exe_with_redir(t_cmd *cmd, t_shell **shell, char *dir, int flag)
{
	int		status;
	char	**env;
	pid_t	pid;

	env = lst_to_array((*shell)->envp);
	if (!env)
		return ;
	pid = fork();
	if (pid == 0)
		exe_redir_child(cmd, shell, dir, env);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			(*shell)->last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			(*shell)->last_exit_status = EXIT_SIGNAL_BASE + WTERMSIG(status);
		free_2d(env);
		if (!flag)
			free(dir);
	}
	else
		perror("fork");
}
