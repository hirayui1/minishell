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
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_MISUSE 2
# define EXIT_NOT_EXECUTABLE 126
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_CHILD_SUCCESS 128
# define EXIT_CHILD_SIGINT 130

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

/* src/utils/list_utils.c */
t_env	*load_list(char **envp);
char	**lst_to_array(t_env *envp);
t_env	*find_key(char *key, t_env *envp);

/* src/utils/list_ops.c */
t_env	*lst_append(char *val, t_env *envp);
t_env	*lstnew(char *val);
void	lst_destroy(t_env *envp);

/* src/utils/input_utils.c */
void	input_handler(char **input, t_shell **shell);
int		cmd_manager(char *input, t_shell **shell);
int		run_single_cmd(char *input, t_shell **shell);

/* src/utils/input_utils2.c */
int		run_pipeline(char *input, int pipe_count, t_shell **shell);

/* src/utils/string_utils.c */
int		is_all(char *s, char c);
void	free_2d(char **split);
char	*substr(char *s, int len);
int		find_word_len(char *input);
int		has_unclosed_quote(char *input);

/* src/utils/string_utils2.c */
char	*remove_extra_chars(char *s, char c);

/* src/utils/expand.c */
char	*expnd(char *input, t_shell **shell);
char	*find_envar(char *input, t_shell **shell);

/* src/utils/expand_utils.c */
int		handle_exit_status(int *len, t_shell **shell);
void	calc_var_len(char **input, int *len, t_shell **shell);
void	insert_var(char **out, char **input, t_shell **shell);

/* src/utils/sig_handlers.c */
void	sig_manager(int level);

/* main.c */
void	cleanup_shell(t_shell **shell);

/* src/exit_handler.c */
void	ft_exit(t_shell **shell, char **input, int exit_code);
void	builtin_exit(t_cmd *cmd, t_shell **shell);

/* src/commands/cd.c */
void	cd(char *input, t_shell **shell);
/* src/commands/pwd.c */
void	pwd(t_shell **shell);
/* src/commands/env.c */
void	print_env(t_shell **shell);
/* src/commands/unset.c */
void	unset(char *input, t_shell **shell);
/* src/commands/export.c */
void	exprt(char *input, t_shell **shell);
/* src/commands/echo.c */
void	echo(char *input, t_shell **shell);

/* src/parse.c */
void	parse_command(char *input, t_cmd *cmd);
void	free_cmd(t_cmd *cmd);

/* src/parse_redir.c */
void	add_redir(t_cmd *cmd, t_redir_type type, char *file, char *delim);
void	parse_redir_in(char **ptr, t_cmd *cmd);
void	parse_redir_out(char **ptr, t_cmd *cmd);

/* src/parse_redir2.c */
void	skip_spaces(char **ptr);
char	*extract_token(char **input);

/* src/commands/exec/exec_main.c */
int		try_exec_external(t_cmd *cmd, t_shell **shell);
void	exe_with_redir(t_cmd *cmd, t_shell **shell, char *dir);

/* src/commands/exec/exec_utils.c */
void	exe_child(char *dir, char **split, char **env, t_shell **shell);
void	exe_parent(int status, char **env, t_shell **shell);
char	*check_access(char *filename, char **path);
char	*find_path(char *filename, t_shell **shell);
void	exe_redir_child(t_cmd *cmd, t_shell **shell, char *dir, char **env);

/* src/commands/exec/exec_redir.c */
int	setup_redirections(t_redir *redirs);
int		collect_heredocs(t_redir *redir, int *heredoc_fd);
void	apply_heredoc_fd(int heredoc_fd);

/* src/commands/exec/exec_builtin.c */
int		is_builtin(char **args);
void	execute_builtin(t_cmd *cmd, t_shell **shell);
void	execute_command(t_cmd *cmd, t_shell **shell);

/* src/commands/exec/exec_pipe.c */
void	execute_pipeline(t_pipeline *pl, t_shell **shell);
int		count_pipes(char *input);
char	**split_by_pipe(char *input, int count);
void	free_pipeline(t_pipeline *pl);

/* src/commands/exec/exec_pipe3.c */
void	wait_for_children(int count, t_shell **shell);

#endif
