#include "../../minishell.h"

void	add_to_pwd(t_shell **shell, char *dir);
void	remove_from_pwd(t_shell **shell, char *dir);
void	update_pwd(t_shell **shell, char *dir);

/**
 * @brief  strnstr finds whatever is after the first space,
 * 	       the arguments, and removes all extra slashes.
 * 	       chdir returns 0 on success, and shell's pwd is changed.
 *
 * @brief-valgrind  old pwd needs to be freed before the new one.
 *		    strnstr does not create a new pointer but returns
 *		    the part of an already existing one so dir is only
 *		    a part of the input variable, which gets freed by
 *		    main at the end of the input cycle.
 */
void	cd(char *input, t_shell **shell)
{
	char	*dir;
  char  *tmp;

	dir = ft_strdup(ft_strnstr(input, " ", ft_strlen(input)) + 1);
  if (!is_all(dir, '/') && ft_strncmp("..", dir, 2))
  {
    tmp = dir;
    dir = remove_extra_chars(dir, '/');
    dir[ft_strlen(dir) - 1] = 0;
    free(tmp);
  }
	if ((*shell)->pwd[0] && !chdir(dir))
	{
		if (dir[0] == '/')
			update_pwd(shell, dir);
		else if (!ft_strncmp("..", dir, 2)
				&& !is_all((*shell)->pwd, '/'))
			remove_from_pwd(shell, dir);
		else if (ft_strncmp("..", dir, 2))
			add_to_pwd(shell, dir);
	}
	else
	{
		printf("-bash: cd: %s: No such file or directory\n", dir);
		free(dir);
	}
}

/**
 * @brief  replaces the pwd with the absolute path given.
 *         if the dir is only slashes, pwd becomes root dir.
 */ 
void	update_pwd(t_shell **shell, char *dir)
{
	if (is_all(dir, '/'))
	{
		free(dir);
		dir = ft_strdup("//");
	}
	free((*shell)->pwd);
	(*shell)->pwd = dir;
}

static void rm_last(t_shell **shell)
{
  char  *last;
  char  *next;

  next = ft_strnstr((*shell)->pwd, "/", ft_strlen((*shell)->pwd));
  while (next)
  {
    last = next;
    next = ft_strnstr(next + 1, "/", ft_strlen(next));
  }
  ft_bzero(last, ft_strlen(last));
  if ((*shell)->pwd[0] == '\0')
  {
    free((*shell)->pwd);
    (*shell)->pwd = ft_strdup("//");
  }
}

void	remove_from_pwd(t_shell **shell, char *dir)
{
  int   count;
  char  *next;

  count = 1;
  next = ft_strnstr(dir, "..", ft_strlen(dir));
  while (next)
  {
    next = ft_strnstr(next + 1, "..", ft_strlen(next));
    if (next)
      count++;
  }
  while (count--)
    rm_last(shell);
	free(dir);
}

void	add_to_pwd(t_shell **shell, char *dir)
{
	char	*tmp;
	char	*pwd;

	pwd = (*shell)->pwd;
	if (!ft_strncmp("//", pwd, 2))
		pwd[ft_strlen(pwd) - 1] = 0;
	if (pwd[0] && pwd[ft_strlen(pwd) - 1] != '/')
	{
		tmp = ft_strjoin(pwd, "/");
		free(pwd);
		pwd = tmp;
	}
	(*shell)->pwd = ft_strjoin(pwd, dir);
	free(pwd);
	free(dir);
}
