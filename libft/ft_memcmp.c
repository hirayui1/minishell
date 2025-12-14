/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarabab <bkarabab@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 13:20:42 by bkarabab          #+#    #+#             */
/*   Updated: 2025/10/12 14:54:48 by bkarabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*sd1;
	unsigned char	*sd2;

	sd1 = (unsigned char *)s1;
	sd2 = (unsigned char *)s2;
	while (n--)
	{
		if (*sd1 != *sd2)
			return (*sd1 - *sd2);
		sd1++;
		sd2++;
	}
	return (0);
}
