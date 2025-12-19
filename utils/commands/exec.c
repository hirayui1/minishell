#include "../../minishell.h"

void  exe(char *dir, char  **split, t_shell **shell)
{
  int   status;

  if (!fork())
    execve(dir, split, (*shell)->envp);
  else
    wait(&status);
}

/**
 * @brief  appends every different variable in the path
 *         to the start of filename and checks if
 *         the file exists.
 *
 * @return matching dir on success, 0 on failure.
 */
char  *find_path(char *filename, t_shell **shell)
{
  int   i;
  char  *dir;
  char  **path;
  char  *tmp;

  i = 0;
  tmp = try_find("PATH", (*shell)->envp) + 5;
  if (!tmp)
    return (0);
  path = ft_split(tmp, ':');
  while (path[i])
  {
    tmp = ft_strjoin(path[i], "/");
    dir = ft_strjoin(tmp, filename);
    free(tmp);
    if (!access(dir, F_OK))
      return (dir);
    free(dir);
    i++;
  }
  return (0);
}

/**
 * @brief  if the file exists in absolute or relative path
 *         this function tries to execute it.
 *
 * @return  0 on success, 1 on failure.
 */
int try_exec(char *input, t_shell **shell)
{
  char  **split;
  char  *dir;
  int   i;

  input = ft_strtrim(input, " ");
  split = ft_split(input, ' ');
  if (input[0] != '/')
    dir = find_path(split[0], shell);
  else
    dir = split[0];
  free(input);
  i = 0;
  if (dir)
  {
    exe(dir, split, shell);
    while (split[i])
      free(split[i++]);
    free(split);
    return (0);
  }
  while (split[i])
    free(split[i++]);
  free(split);
  return (1);
}
