#include "../minishell.h"

/**
 * @brief  checks if s is only made of c chars
 *
 * @return  1 for success, 0 for failure.
 */
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

/**
 * @brief  checks if s is only made of the set of chars in any order.
 *
 * @return  1 for success, 0 for failure. 
 */
int	is_set(char *s, char *c)
{
  int i;

  i = 0;
	if (!s || !*c)
		return (0);
	while (*s)
	{
    while (c[i])
    {
		  if (*s != c[i++])
		  	return (0);
    }
		s++;
	}
	return (1);
}

/**
 * @brief  checks if the array starts with word in every array in a 2D array
 *         Particularly useful for fetching a variable from envp.
 *
 * @return  returns a partial pointer of the 2D array.
 *          its undesirable to free this, hence failure returns 0 instead
 *          of empty string.
 */
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
/**
 * @brief  should reduce trailing char c to only one,
 * 	   but also make sure to leave one of them.
 * 	   (/////home//user///folder////) -> (/home/user/folder)
 */
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
