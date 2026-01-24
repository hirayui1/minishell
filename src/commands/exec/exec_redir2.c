/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarabab <bkarabab@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 09:53:17 by bkarabab          #+#    #+#             */
/*   Updated: 2026/01/24 09:53:19 by bkarabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/* open file for redir */
int	open_redir_fd(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == REDIR_IN)
		fd = open(redir->file, O_RDONLY);
	else if (redir->type == REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == REDIR_APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

/* apply all redirections */
int	setup_redirections(t_redir *redirs)
{
	int	fd;
	int	target;

	while (redirs)
	{
		if (redirs->type != REDIR_HEREDOC)
		{
			fd = open_redir_fd(redirs);
			if (fd == -1)
				return (perror("minishell"), 1);
			if (redirs->type == REDIR_IN)
				target = STDIN_FILENO;
			else
				target = STDOUT_FILENO;
			dup2(fd, target);
			close(fd);
		}
		redirs = redirs->next;
	}
	return (0);
}
