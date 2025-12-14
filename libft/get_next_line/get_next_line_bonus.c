#include "get_next_line.h"

static char	*ft_update_stash(char **stash, char *newline_ptr)
{
	char	*tmp;

	if (*(newline_ptr + 1) == '\0')
	{
		free(*stash);
		*stash = 0;
		return (0);
	}
	tmp = ft_strjoin(0, newline_ptr + 1);
	if (!tmp || *tmp == '\0')
	{
		if (*tmp == '\0')
			free(tmp);
		free(*stash);
		*stash = 0;
		return (0);
	}
	free(*stash);
	*stash = tmp;
	return (*stash);
}

static char	*ft_extract_line_with_newline(char **stash, char *newline_ptr)
{
	char	*line;
	size_t	i;

	i = newline_ptr - *stash + 1;
	line = malloc(i + 1);
	if (!line)
		return (0);
	i = 0;
	while((*stash)[i] && (*stash)[i] != '\n')
	{
		line[i] = (*stash)[i];
		i++;
	}
	line[i++] = '\n';
	line[i] = '\0';
	if (!ft_update_stash(stash, newline_ptr))
		*stash = 0;
	return (line);
}

static char	*ft_extractline(char **stash)
{
	char	*line;
	char	*newline_ptr;

	if (!*stash || !**stash)
		return (0);
	newline_ptr = ft_strchr(*stash, '\n');
	if (newline_ptr)
		return (ft_extract_line_with_newline(stash, newline_ptr));
	else
	{
		line = ft_strjoin(0, *stash);
		free(*stash);
		*stash = 0;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash[FD_SETSIZE];
	char		*line;

	if (fd < 0 || fd >= FD_SETSIZE || BUFFER_SIZE < 1)
		return (0);
	stash[fd] = ft_readline(fd, stash[fd]);
	if (!stash[fd] || !*stash[fd])
	{
		free(stash[fd]);
		stash[fd] = 0;
		return (0);
	}
	line = ft_extractline(&stash[fd]);
	if (!line && stash[fd])
	{
		free(stash[fd]);
		stash[fd] = 0;
	}
	return (line);
}
