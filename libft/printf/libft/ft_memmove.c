/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarabab <bkarabab@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:54:18 by bkarabab          #+#    #+#             */
/*   Updated: 2025/10/12 18:59:08 by bkarabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tmp;
	unsigned char	*s;

	tmp = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (dest <= src)
	{
		while (n--)
			*tmp++ = *s++;
	}
	else
	{
		s += n;
		tmp += n;
		while (n--)
			*--tmp = *--s;
	}
	return (dest);
}
