/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarabab <bkarabab@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 09:57:14 by bkarabab          #+#    #+#             */
/*   Updated: 2026/01/24 09:57:14 by bkarabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* get env var value */
char	*find_envar(char *input, t_shell **shell)
{
	t_env	*envp;
	int		len;

	++input;
	if (!input)
		return (NULL);
	len = find_word_len(input);
	input = substr(input, len);
	if (!input)
		return (NULL);
	envp = find_key(input, (*shell)->envp);
	free(input);
	if (envp)
		return (ft_strchr(envp->val, '=') + 1);
	return (NULL);
}

/* skip 'quoted' section */
void	skip_single_quote(char **input, int *len)
{
	*len += 2;
	++(*input);
	while (**input && **input != '\'')
	{
		++(*len);
		++(*input);
	}
	if (**input == '\'')
		++(*input);
}

/* copy 'quoted' content */
void	copy_single_quote(char **out, char **input)
{
	*(*out)++ = *(*input)++;
	while (**input && **input != '\'')
		*(*out)++ = *(*input)++;
	if (**input == '\'')
		*(*out)++ = *(*input)++;
}
