#include "../minishell.h"

/*
** free_2d - Free a 2D array of strings
*/
void	free_2d(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

/*
** is_all - Check if all characters in string are the same
*/
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

/*
** substr - Extract substring from string
*/
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

/*
** find_word_len - Find length of alphanumeric word
*/
int	find_word_len(char *input)
{
	int	len;

	len = 0;
	while (*input && ft_isalnum(input[len]))
		++len;
	return (len);
}
