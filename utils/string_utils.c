#include "../minishell.h"

/**
 * @brief  checks if s is only made of c chars
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
			printf("1");
			i++;
		}
		else if (s[i] == c && s[i + 1] != '\0')
		{
			printf("2");
			dst[j++] = '/';
		}
		else
		{
			printf("3");
			dst[j++] = s[i];
		}
		printf("*s: %c, *dst: %s, i: %d, j: %d\n", s[i], dst, i, j);
		i++;
	}
	dst[j] = 0;
	return (dst);
}
