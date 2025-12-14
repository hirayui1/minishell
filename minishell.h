#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"

typedef struct s_shell
{
	struct s_shell	*next;
	char	*pwd;
}	t_shell;

// utils/input_utils
void	input_handler(char **input, t_shell **shell);
int	try_exec(char *input, t_shell **shell);

// utils/sig_handlers
void	sig_manager(void);

// utils/errors/error_prompts
void	write_error(void);

// utils/exit_handler
void	ft_exit(t_shell **shell, char **input, int exit_code);

// utils/commands
void	ls(char *input);
void	cd(char *input, t_shell **shell);
void	pwd(t_shell **shell);
#endif
