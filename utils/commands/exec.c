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
		//sig_manager(1);
    execve(dir, split, env);
		//free_2d(split);
		//free_2d(env);
		//ft_exit(shell, &dir, 1); // if execve fails, free and kill child
		exit(1);
	}
	else if (pid > 0) // child_pid is returned to parent, make parent wait
	{
		waitpid(pid, &status, 0);
		free_2d(env);
	}
  else
    perror("fork");		
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
	{
		dir = split[0];
	}
	else // path
	{
		flag = 0;
		dir = find_path(split[0], shell);
	}
  free(input);
  if (dir)
  {
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
