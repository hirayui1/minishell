/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarabab <bkarabab@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:31:23 by sandrzej          #+#    #+#             */
/*   Updated: 2026/01/24 09:56:26 by bkarabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	count_pipes(char *input)
{
	int	count;
	int	in_squote;
	int	in_dquote;

	count = 0;
	in_squote = 0;
	in_dquote = 0;
	while (*input)
	{
		if (*input == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (*input == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (*input == '|' && !in_squote && !in_dquote)
			count++;
		input++;
	}
	return (count);
}

static int	find_pipe_pos(char *input)
{
	int	i;
	int	in_squote;
	int	in_dquote;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (input[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (input[i] == '|' && !in_squote && !in_dquote)
			return (i);
		i++;
	}
	return (-1);
}

char	**split_by_pipe(char *input, int count)
{
	char	**segments;
	int		i;
	int		pos;

	segments = malloc(sizeof(char *) * (count + 2));
	if (!segments)
		return (NULL);
	i = 0;
	while (i <= count)
	{
		pos = find_pipe_pos(input);
		if (pos == -1)
			segments[i] = ft_strdup(input);
		else
		{
			segments[i] = ft_substr(input, 0, pos);
			input = input + pos + 1;
		}
		if (!segments[i])
			return (NULL);
		i++;
	}
	segments[i] = NULL;
	return (segments);
}

void	free_pipeline(t_pipeline *pl)
{
	int	i;

	if (!pl)
		return ;
	i = 0;
	while (i < pl->cmd_count)
	{
		free_cmd(&pl->cmds[i]);
		i++;
	}
	free(pl->cmds);
	free(pl);
}

void	execute_pipeline(t_pipeline *pl, t_shell **shell)
{
	int		pipefd[2];
	int		in_fd;
	int		i;
	t_cmd	*cmd;

	in_fd = STDIN_FILENO;
	i = 0;
	cmd = pl->cmds;
	(*shell)->pl = pl;
	while (i < pl->cmd_count)
	{
		if (i < pl->cmd_count - 1)
			pipe(pipefd);
		run_pipe_cmd(cmd, &in_fd, pipefd, shell);
		cmd = cmd->next;
		i++;
	}
	(*shell)->pl = NULL;
	sig_manager(1);
	wait_for_children(pl->cmd_count, shell);
	sig_manager(0);
}
