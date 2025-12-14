#include "get_next_line.h"
static char *ft_extract_line_with_newline(char **stash, char *newline_ptr) {
    char *line;
    char *tmp;
    size_t i;

    i = newline_ptr - *stash + 1;
    line = malloc(i + 1);
    if (!line)
        return (0);

    i = 0;
    while ((*stash)[i] != '\n' && (*stash)[i] != '\0') {
        line[i] = (*stash)[i];
        i++;
    }
    line[i++] = '\n';
    line[i] = '\0';

    tmp = ft_strjoin(0, newline_ptr + 1);
    free(*stash);
    *stash = tmp;

    return (line);
}

static char *ft_extractline(char **stash) {
    char *line;
    char *newline_ptr;

    if (!*stash || !**stash)
        return (0);

    newline_ptr = ft_strchr(*stash, '\n');
    if (newline_ptr)
        return (ft_extract_line_with_newline(stash, newline_ptr));
    else {
        line = ft_strjoin(0, *stash);
        free(*stash);
        *stash = 0;
    }

    return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return NULL;
	stash = ft_readline(fd, stash);
	if (stash == NULL)
		return NULL;
	line = ft_extractline(&stash);
	if (line == NULL && stash != NULL)
	{
		free(stash);
		stash = NULL;
	}
	return line;
}
/*
// Test main
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("hello2", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return 1;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return 0;
}
*/
