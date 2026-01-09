#include "../minishell.h"

void  free_2d(char **split)
{
  int i;

  i = 0;
  while (split[i])
    free(split[i++]);
  free(split);
}

int	is_all(char *s, char c)
{
	if (!s || !c)
		return (0);
	while (*s)
	{
		if (*s != c)
			return (0);
		s++;
	}
	return (1);
}

char	*substr(char *s, int len)
{
	char	*res;
	int		i;

	i = 0;
	if (!s || len < 1)
		return (0);
	res = malloc(sizeof(char) * len + 1);
	if (!res)
		return (0);
	while (i < len)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

int	find_word_len(char *input)
{
	int	len;

	len = 0;
	while (input[len] && input[len] != ' ')
		len++;
	return (len);
}

char  *try_find(char *word, char **arr)
{
  int len;
  int i;

  len = ft_strlen(word);
  i = 0;
  while (arr[i])
  {
    if (!ft_strncmp(arr[i], word, len))
        return (arr[i]);
    i++;
  }
  return (0);
}

char	*remove_extra_chars(char *s, char c)
{
	char	*dst;
	int	i;
	int	j;

	dst = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!dst)
			return (0);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c && (s[i + 1] && s[i + 1] == c))
		{
		  // do nothing, duplicate char
		}
		else if (s[i] == c && s[i + 1])
			dst[j++] = c; // end of dup, append c
		else
			dst[j++] = s[i]; // append the word
		i++;
	}
	dst[j] = 0;
	return (dst);
}
