#include "../../../minishell.h"

static char	*heredoc_runner(t_redir *redir, int pipefd[2])
{
	size_t	len;
	char	*line;

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
	if (!line)
		return (0);
	return (line);
}

/* read lines until delimiter */
static int	handle_heredoc(t_redir *redir, int pipefd[2])
{
	char	*line;
	int		stdin_backup;

	stdin_backup = dup(STDIN_FILENO);
	sig_manager(2);
	// heredoc_runner was here
	line = heredoc_runner(redir, pipefd);
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
