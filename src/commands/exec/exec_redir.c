/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:31:28 by sandrzej          #+#    #+#             */
/*   Updated: 2026/01/22 16:31:29 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/* open file for redir */
static int	open_redir_fd(t_redir *redir)
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
/* 
free_pipeline((*shell)->pl);
		    cleanup_shell(shell);
				exit(EXIT_FAILURE); */
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

/* read lines until delimiter */
static int	handle_heredoc(t_redir *redir, int pipefd[2])
{
	char	*line;
	size_t	len;
	int		stdin_backup;

	stdin_backup = dup(STDIN_FILENO);
	sig_manager(2);
	line = readline("> ");
	while (line)
	{
		len = ft_strlen(redir->delimiter);
		if (!ft_strncmp(line, redir->delimiter, len) && !line[len])
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	close(pipefd[1]);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	sig_manager(0);
	if (!line)
		return (1);
	return (0);
}

/* gather heredoc input before fork */
int	collect_heredocs(t_redir *redir, int *heredoc_fd)
{
	int	pipefd[2];

	*heredoc_fd = -1;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
		{
			if (pipe(pipefd) == -1)
				return (-1);
			if (handle_heredoc(redir, pipefd))
			{
				close(pipefd[0]);
				if (*heredoc_fd != -1)
					close(*heredoc_fd);
				return (1);
			}
			// RED
			// if (*heredoc_fd != -1)
			// 	close(*heredoc_fd);
			*heredoc_fd = pipefd[0];
		}
		redir = redir->next;
	}
	return (0);
}

/* set heredoc as stdin */
void	apply_heredoc_fd(int heredoc_fd)
{
	if (heredoc_fd != -1)
	{
		dup2(heredoc_fd, STDIN_FILENO);
		close(heredoc_fd);
	}
}
