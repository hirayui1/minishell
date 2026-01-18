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

/* apply all redirections */
void	setup_redirections(t_redir *redirs)
{
	int	fd;
	int	target;

	while (redirs)
	{
		if (redirs->type != REDIR_HEREDOC)
		{
			fd = open_redir_fd(redirs);
			if (fd == -1)
			{
				perror("minishell");
				exit(1);
			}
			if (redirs->type == REDIR_IN)
				target = STDIN_FILENO;
			else
				target = STDOUT_FILENO;
			dup2(fd, target);
			close(fd);
		}
		redirs = redirs->next;
	}
}

/* read lines until delimiter */
void	handle_heredoc(t_redir *redir, int pipefd[2])
{
	char	*line;
	size_t	len;

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
			handle_heredoc(redir, pipefd);
			if (*heredoc_fd != -1)
				close(*heredoc_fd);
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
