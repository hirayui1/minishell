#include "../../minishell.h"

void  exe(char *dir, char  **split, t_shell **shell)
{
	int   status;
	char	**env;
	pid_t	pid;
	
	env = lst_to_array((*shell)->envp);
	if (!env)
	return ;
	pid = fork();
	if (pid == 0) // 0 is success
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
	else if (pid > 0) // child_pid is returned to parent, make parent wait
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status)) // check if exited normally
		(*shell)->last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status)) // check if terminated by signal
		(*shell)->last_exit_status = EXIT_SIGNAL_BASE + WTERMSIG(status);
		free_2d(env);
	}
	else
	perror("bash"); // fork error
}

char	*check_access(char *filename, char **path)
{
	int		i;
	char  *dir;
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
	return (free_2d(path), NULL); //TODO: free on failcase
}

/*
* magic number is the length of key(PATH=) in env
*/
char  *find_path(char *filename, t_shell **shell)
{
	char  **path;
	char  *tmp;
	char	*dir;
	t_env	*envp;
	
	envp = find_key("PATH", (*shell)->envp);
	if (!envp)
	return (0);
	tmp = envp->val + 5;
	if (!tmp)
	return (0);
	path = ft_split(tmp, ':');
	dir = check_access(filename, path);
	if (!dir)
	return (NULL);
	return (dir);
}

/*
* if the dir is found in path, we don't want to free it to avoid messing envp.
* flag variable helps with this.
*/
int try_exec(char *input, t_shell **shell)
{
	char  **split;
	char  *dir;
	int   flag;
	
	flag = 1;
	input = ft_strtrim(input, " ");
	split = ft_split(input, ' ');
	if (input[0] == '/') // absolute
	dir = split[0];
	else if (!access(split[0], F_OK)) // current dir
	dir = split[0];
	else // path
	{
		flag = 0;
		dir = find_path(split[0], shell);
	}
	free(input);
	if (dir)
	{
		if (access(dir, X_OK) != 0) {
			(*shell)->last_exit_status = EXIT_NOT_EXECUTABLE;
			perror("permission denied");
			free_2d(split);
			if (!flag)
			free(dir);
			return 0; // already handled
		}
		exe(dir, split, shell);
		if (!flag)
		free(dir);
		free_2d(split);
		return (0);
	}
	else
	free_2d(split);
	return (1);
}
