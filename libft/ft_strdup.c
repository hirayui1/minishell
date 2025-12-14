/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarabab <bkarabab@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 13:20:26 by bkarabab          #+#    #+#             */
/*   Updated: 2025/10/04 13:20:30 by bkarabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	char	*cpy;

	len = ft_strlen(s);
	cpy = malloc(sizeof(char) * len + 1);
	if (!cpy)
		return (0);
	ft_memcpy(cpy, s, len + 1);
	return (cpy);
}
