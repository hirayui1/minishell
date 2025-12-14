/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarabab <bkarabab@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 13:22:22 by bkarabab          #+#    #+#             */
/*   Updated: 2025/10/04 13:22:46 by bkarabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*s;

	if (size != 0 && n > SIZE_MAX / size)
		return (0);
	s = malloc(n * size);
	if (!s)
		return (0);
	ft_bzero(s, n * size);
	return (s);
}
