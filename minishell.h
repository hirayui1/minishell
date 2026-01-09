#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "libft.h"

// personal macros for reducing magic numbers
# define N_OPTION "-n "
# define N_OPTION_LEN 3
# define ECHO_LEN 5

typedef struct s_env
{
  struct s_env  *next;
  char  *val;
} t_env;

typedef struct s_shell
{
	struct s_shell	*next;
  struct s_env    *envp;
	char	*pwd;
}	t_shell;

// utils/list_utils
t_env *load_list(char **envp);
char	**lst_to_array(t_env *envp);
t_env	*find_key(char *key, t_env *envp);

// utils/list_ops
t_env	*lst_append(char *val, t_env *envp);
t_env	*lstnew(char *val);
void	lst_destroy(t_env *envp);

// utils/input_utils
void	input_handler(char **input, t_shell **shell);
int	  cmd_manager(char *input, t_shell **shell);

// utils/string_utils
char	*expnd(char *input, t_shell **shell);
int	  is_all(char *s, char c);
int   is_set(char *s, char *c);
char	*remove_extra_chars(char *s, char c);
char  *try_find(char  *word, char **arr);
void	free_2d(char **split);
char	*substr(char *s, int len);
int		find_word_len(char *input);

// utils/expand.c


// utils/sig_handlers
void	sig_manager(int level);

// utils/errors/error_prompts
void	write_error(void);

// utils/exit_handler
void	ft_exit(t_shell **shell, char **input, int exit_code);

// utils/commands
void	cd(char *input, t_shell **shell);
void	pwd(t_shell **shell);
void	print_env(t_shell **shell);
void	unset(char *input, t_shell **shell);
void	exprt(char *input, t_shell **shell);
void  echo(char *input);
int   try_exec(char *input, t_shell **shell);
#endif
