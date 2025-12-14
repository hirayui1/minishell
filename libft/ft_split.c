/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarabab <bkarabab@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 13:18:08 by bkarabab          #+#    #+#             */
/*   Updated: 2025/10/13 19:55:41 by bkarabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_word_count(const char *str, char c);
static char	*ft_fill_2d(char const *s, int start, int end);
static void	*ft_free(char **result, int count);
static void	ft_init(size_t *i, int *j, int *wlen);

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	i;
	int		j;
	int		wlen;

	if (!s)
		return (0);
	ft_init(&i, &j, &wlen);
	res = ft_calloc((ft_word_count(s, c) + 1), sizeof(char *));
	if (!res)
		return (0);
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && wlen < 0)
			wlen = i;
		else if ((s[i] == c || i == ft_strlen(s)) && wlen >= 0)
		{
			res[++j] = ft_fill_2d(s, wlen, i);
			if (!(res[j]))
				return (ft_free(res, j));
			wlen = -1;
		}
	}
	return (res);
}

static void	ft_init(size_t *i, int *j, int *wlen)
{
	*wlen = -1;
	*i = -1;
	*j = -1;
}

static int	ft_word_count(const char *str, char c)
{
	int	count;
	int	word;

	count = 0;
	word = 0;
	while (*str)
	{
		if (*str != c && word == 0)
		{
			word = 1;
			count++;
		}
		else if (*str == c)
			word = 0;
		str++;
	}
	return (count);
}

static char	*ft_fill_2d(char const *s, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (0);
	while (start < end)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = 0;
	return (word);
}

static void	*ft_free(char **result, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(result[i++]);
	free(result);
	return (0);
}
/*
char	*ft_hi(void)
{
	return (0);
}
// if you pass null to ft_split, you'll get segfault
// from the while loop that tests it.
// this issue happens because you are trying to check an index
//  that does not exist, ft_hi is the proof of this
//  and you can comment while loop out if you want to pass null
//  to test out if you will indeed get a segfault from ft_split
int	main(void)
{
	printf("%s", ft_hi());
	
	char **s = ft_split(0, ' ');
	int i = 0;
	while (s[i])
		printf("%s\n", s[i++]);
	return (0);
}
*/
