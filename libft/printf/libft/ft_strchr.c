/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarabab <bkarabab@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:01:13 by bkarabab          #+#    #+#             */
/*   Updated: 2025/10/04 13:21:42 by bkarabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char			*sd;
	unsigned char	uc;
	int				i;

	i = 0;
	sd = (char *)s;
	uc = (unsigned char)c;
	while (s[i])
	{
		if (uc == s[i])
		{
			return (sd + i);
		}
		else
			i++;
	}
	if (uc == '\0')
		return (sd + i);
	return (0);
}
