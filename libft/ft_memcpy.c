/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarabab <bkarabab@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:38:14 by bkarabab          #+#    #+#             */
/*   Updated: 2025/10/08 20:15:06 by bkarabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned char		*s;
	void				*ret;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	ret = dest;
	while (n--)
		*d++ = *s++;
	return (ret);
}
