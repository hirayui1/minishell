/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarabab <bkarabab@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 13:11:13 by bkarabab          #+#    #+#             */
/*   Updated: 2025/10/12 14:55:23 by bkarabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*sd;
	unsigned char	uc;

	sd = (unsigned char *)s;
	uc = (unsigned char)c;
	while (n--)
	{
		if (*sd == uc)
			return (sd);
		sd++;
	}
	return (0);
}
