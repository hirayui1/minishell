/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:32:20 by sandrzej          #+#    #+#             */
/*   Updated: 2026/01/22 16:32:21 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*read_until_closed(char *input)
{
	char	*line;
	char	*tmp;

  sig_manager(2);
	while (has_unclosed_quote(input))
	{
		line = readline("> ");
		if (!line)
			return (sig_manager(1), input);
		tmp = ft_strjoin(input, "\n");
		free(input);
		input = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
	}
	return (sig_manager(1), input);
}

void	input_handler(char **input, t_shell **shell)
{
	if (!*input)
		ft_exit(shell, input, 1);
	else if (ft_strlen(*input))
	{
		if (has_unclosed_quote(*input))
			*input = read_until_closed(ft_strdup(*input));
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

	parse_command(input, &cmd);
	free(input);
	cmd.heredoc_fd = -1;
	if (collect_heredocs(cmd.redirs, &cmd.heredoc_fd) == 1)
	{
		(*shell)->last_exit_status = 130;
		return (free_cmd(&cmd), 1);
	}
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
		return (0);
	}
	run_pipeline(input, pipe_count, shell);
	return (0);
}
