/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:32:25 by sandrzej          #+#    #+#             */
/*   Updated: 2026/01/22 16:32:26 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	lst_count(t_env *envp)
{
	int	i;

	i = 0;
	while (envp)
	{
		i++;
		envp = envp->next;
	}
	return (i);
}

char	**lst_to_array(t_env *envp)
{
	char	**s;
	int		i;

	s = malloc(sizeof(char *) * (lst_count(envp) + 1));
	if (!s)
		return (NULL);
	i = 0;
	while (envp)
	{
		s[i++] = ft_strdup(envp->val);
		envp = envp->next;
	}
	s[i] = NULL;
	return (s);
}

t_env	*find_key(char *key, t_env *envp)
{
	int	len;
	int	keylen;

	keylen = ft_strlen(key);
	while (envp)
	{
		if (envp->val[0])
		{
			len = ft_strchr(envp->val, '=') - envp->val;
			if (keylen == len && !ft_strncmp(key, envp->val, len))
				return (envp);
		}
		envp = envp->next;
	}
	return (NULL);
}

t_env	*load_list(char **envp)
{
	t_env	*head;
	t_env	*cur;
	int		i;

	i = 0;
	head = lstnew(envp[i++]);
	if (!head)
		return (NULL);
	cur = head;
	while (envp[i])
	{
		cur->next = lstnew(envp[i++]);
		if (!cur->next)
			return (lst_destroy(head), NULL);
		cur = cur->next;
	}
	return (head);
}
