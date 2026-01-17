#include "../minishell.h"

void	input_handler(char **input, t_shell **shell)
{
	if (!*input)
		ft_exit(shell, input, 1);
	else if (ft_strlen(*input))
	{
		add_history(*input);
		cmd_manager(*input, shell);
	}
}

static char	*normalizer(char *input, t_shell **shell)
{
	char	*tmp;
	char	*trimmed;

	tmp = expnd(input, shell);
	trimmed = ft_strtrim(tmp, " ");
	free(tmp);
	tmp = remove_extra_chars(trimmed, ' ');
	free(trimmed);
	return (tmp);
}

int	run_single_cmd(char *input, t_shell **shell)
{
	t_cmd	cmd;

	parse_command(input, &cmd, shell);
	cmd.heredoc_fd = -1;
	collect_heredocs(cmd.redirs, &cmd.heredoc_fd);
	if (!cmd.args || !cmd.args[0])
	{
		if (cmd.heredoc_fd != -1)
			close(cmd.heredoc_fd);
		return (free_cmd(&cmd), 0);
	}
	execute_command(&cmd, shell);
	if (cmd.heredoc_fd != -1)
		close(cmd.heredoc_fd);
	return (free_cmd(&cmd), 0);
}

int	cmd_manager(char *input, t_shell **shell)
{
	int	pipe_count;

	input = normalizer(input, shell);
	pipe_count = count_pipes(input);
	if (pipe_count == 0)
	{
		run_single_cmd(input, shell);
		free(input);
		return (0);
	}
	run_pipeline(input, pipe_count, shell);
	free(input);
	return (0);
}
