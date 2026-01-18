#include "../../minishell.h"

/* copy quoted section */
static int	skip_in_quotes(char *s, char *dst, int *i, int j)
{
	char	quote;

	quote = s[*i];
	dst[j++] = s[(*i)++];
	while (s[*i] && s[*i] != quote)
		dst[j++] = s[(*i)++];
	if (s[*i] == quote)
		dst[j++] = s[(*i)++];
	return (j);
}

/* collapse repeated chars */
char	*remove_extra_chars(char *s, char c)
{
	char	*dst;
	int		i;
	int		j;

	dst = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			j = skip_in_quotes(s, dst, &i, j);
		else if (s[i] == c && s[i + 1] && s[i + 1] == c)
			++i;
		else if (s[i] == c && s[i + 1])
			dst[j++] = s[i++];
		else
			dst[j++] = s[i++];
	}
	dst[j] = '\0';
	return (dst);
}
