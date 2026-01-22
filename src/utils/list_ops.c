/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarabab <bkarabab@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:36:14 by bkarabab          #+#    #+#             */
/*   Updated: 2026/01/22 16:36:27 by bkarabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

	t_env *
	lst_append(char *val, t_env *envp)
{
	while (envp->next)
		envp = envp->next;
	envp->next = lstnew(val);
	return (envp);
}

t_env	*lstnew(char *val)
{
	t_env	*a;

	a = malloc(sizeof(t_env));
	if (!a)
		return (NULL);
	a->val = ft_strdup(val);
	a->next = NULL;
	return (a);
}

void	lst_destroy(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->val);
		free(head);
		head = tmp;
	}
}
