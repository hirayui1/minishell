#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char uc;

	uc = (unsigned char)c;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == uc)
			return ((char *)s);
		s++;
	}
	if (uc == '\0')
		return ((char *)s);
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if ((!s1 || !*s1) && (!s2 || !*s2))
		return (0);
	i = 0;
	j = 0;
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (0);
	while (s1 && s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	if (s1)
		free(s1);
	return (str);
}

char	*ft_readline(int fd, char *stash)
{
	char	*buf;
	ssize_t	read_len;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	read_len = 1;
	while (!ft_strchr(stash, '\n') && read_len > 0)
	{
		read_len = read(fd, buf, BUFFER_SIZE);
		if (read_len < 0)
		{
			free(buf);
			return (0);
		}
		buf[read_len] = '\0';
		stash = ft_strjoin(stash, buf);
		if (!stash)
		{
			free(buf);
			return (0);
		}
	}
	free(buf);
	return (stash);
}
