/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:28:57 by sandrzej          #+#    #+#             */
/*   Updated: 2026/01/22 16:28:58 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <fcntl.h>
# include "libft.h"
# include <errno.h>

# define PATH_OFFSET 5
# define N_OPTION "-n "
# define N_OPTION_OFFSET 3
# define ECHO_OFFSET 5
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_NOT_EXECUTABLE 126
# define EXIT_SIGNAL_BASE 128

typedef struct s_env
{
	struct s_env	*next;
	char			*val;
}	t_env;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	char			*delimiter;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	int				heredoc_fd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipeline
{
	t_cmd		*cmds;
	int			cmd_count;
}	t_pipeline;

typedef struct s_shell
{
	struct s_shell	*next;
	struct s_env	*envp;
	int				last_exit_status;
  t_pipeline *pl;
	char			*pwd;
}	t_shell;

/* utils/list_utils */
t_env	*load_list(char **envp);
char	**lst_to_array(t_env *envp);
t_env	*find_key(char *key, t_env *envp);

/* utils/list_ops */
t_env	*lst_append(char *val, t_env *envp);
t_env	*lstnew(char *val);
void	lst_destroy(t_env *envp);

/* utils/input_utils */
void	input_handler(char **input, t_shell **shell);
int		cmd_manager(char *input, t_shell **shell);
int		run_single_cmd(char *input, t_shell **shell);

/* utils/input_utils2 */
int		run_pipeline(char *input, int pipe_count, t_shell **shell);

/* utils/string_utils */
int		is_all(char *s, char c);
void	free_2d(char **split);
char	*substr(char *s, int len);
int		find_word_len(char *input);
int		has_unclosed_quote(char *input);

/* utils/string_utils2 */
char	*remove_extra_chars(char *s, char c);

/* utils/expand.c */
char	*expnd(char *input, t_shell **shell);
char	*find_envar(char *input, t_shell **shell);

/* utils/expand_utils.c */
int		handle_exit_status(int *len, t_shell **shell);
void	calc_var_len(char **input, int *len, t_shell **shell);
void	insert_var(char **out, char **input, t_shell **shell);

/* utils/sig_handlers */
void	sig_manager(int level);

/* utils/exit_handler */
void	ft_exit(t_shell **shell, char **input, int exit_code);
void	cleanup_shell(t_shell **shell);

/* utils/commands */
void	cd(char *input, t_shell **shell);
void	pwd(t_shell **shell);
void	print_env(t_shell **shell);
void	unset(char *input, t_shell **shell);
void	exprt(char *input, t_shell **shell);
void	echo(char *input, t_shell **shell);
void	builtin_exit(t_cmd *cmd, t_shell **shell);

/* utils/parse.c */
void	parse_command(char *input, t_cmd *cmd);
void	free_cmd(t_cmd *cmd);

/* utils/parse_redir.c */
void	add_redir(t_cmd *cmd, t_redir_type type, char *file, char *delim);
char	*extract_token(char **input);
void	skip_spaces(char **ptr);
void	parse_redir_in(char **ptr, t_cmd *cmd);
void	parse_redir_out(char **ptr, t_cmd *cmd);

/* utils/commands/exec_main.c */
int		try_exec_external(t_cmd *cmd, t_shell **shell);
void	exe_with_redir(t_cmd *cmd, t_shell **shell, char *dir, int flag);

/* utils/commands/exec_utils.c */
void	exe_child(char *dir, char **split, char **env, t_shell **shell);
void	exe_parent(int status, char **env, t_shell **shell);
char	*check_access(char *filename, char **path);
char	*find_path(char *filename, t_shell **shell);
void	exe_redir_child(t_cmd *cmd, t_shell **shell, char *dir, char **env);

/* utils/commands/exec_redir.c */
void	setup_redirections(t_redir *redirs);
int		collect_heredocs(t_redir *redir, int *heredoc_fd);
void	apply_heredoc_fd(int heredoc_fd);

/* utils/commands/exec_builtin.c */
int		is_builtin(char **args);
void	execute_builtin(t_cmd *cmd, t_shell **shell);
void	execute_command(t_cmd *cmd, t_shell **shell);

/* utils/commands/exec_pipe.c */
void	execute_pipeline(t_pipeline *pl, t_shell **shell);
int		count_pipes(char *input);
char	**split_by_pipe(char *input, int count);
void	free_pipeline(t_pipeline *pl);

/* utils/commands/exec_pipe3.c */
void	wait_for_children(int count, t_shell **shell);

#endif
