#include "../../minishell.h"

/* free string array */
void	free_2d(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

/* check if all chars match c */
int	is_all(char *s, char c)
{
	if (!s || !c)
		return (0);
	while (*s)
	{
		if (*s != c)
			return (0);
		++s;
	}
	return (1);
}

/* get substring of len */
char	*substr(char *s, int len)
{
	char	*res;
	int		i;

	if (!s || len < 1)
		return (NULL);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[i];
		++i;
	}
	res[i] = '\0';
	return (res);
}

/* get alnum word length */
int	find_word_len(char *input)
{
	int	len;

	len = 0;
	while (*input && ft_isalnum(input[len]))
		++len;
	return (len);
}

/* check for unmatched quotes */
int	has_unclosed_quote(char *input)
{
	int	in_squote;
	int	in_dquote;

	in_squote = 0;
	in_dquote = 0;
	while (*input)
	{
		if (*input == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (*input == '"' && !in_squote)
			in_dquote = !in_dquote;
		input++;
	}
	return (in_squote || in_dquote);
}
