/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:31:57 by sandrzej          #+#    #+#             */
/*   Updated: 2026/01/22 16:32:00 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env * lst_append(char *val, t_env *envp)
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
