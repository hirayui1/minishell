/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarabab <bkarabab@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:23:01 by bkarabab          #+#    #+#             */
/*   Updated: 2025/10/13 18:23:46 by bkarabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*node;

	if (!lst)
		return (0);
	if (!lst->next)
		return (1);
	node = lst->next;
	size = 2;
	while (node->next)
	{
		size++;
		node = node->next;
	}
	return (size);
}
