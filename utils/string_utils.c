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
			dst[j++] = '/'; // end of dup
		else
			dst[j++] = s[i]; // append the word
		printf("*s: %c, *dst: %s, i: %d, j: %d\n", s[i], dst, i, j);
		i++;
	}
	dst[j] = 0;
	return (dst);
}
