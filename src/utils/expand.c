/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:31:47 by sandrzej          #+#    #+#             */
/*   Updated: 2026/01/22 16:31:49 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* calc len inside "quotes" */
static void	calc_in_dquote(char **input, int *len, t_shell **shell)
{
	*len += 2;
	++(*input);
	while (**input && **input != '"')
	{
		if (**input == '$')
			calc_var_len(input, len, shell);
		else
		{
			++(*len);
			++(*input);
		}
	}
	if (**input == '"')
		++(*input);
}

/* calc expanded string len */
int	calc_total_len(char *input, int *len, t_shell **shell)
{
	while (*input)
	{
		if (*input == '\'')
			skip_single_quote(&input, len);
		else if (*input == '"')
			calc_in_dquote(&input, len, shell);
		else if (*input == '$')
			calc_var_len(&input, len, shell);
		else
		{
			++(*len);
			++input;
		}
	}
	return (0);
}

/* copy "quoted" with expansion */
static void	copy_in_dquote(char **out, char **input, t_shell **shell)
{
	*(*out)++ = *(*input)++;
	while (**input && **input != '"')
	{
		if (**input == '$')
			insert_var(out, input, shell);
		else
			*(*out)++ = *(*input)++;
	}
	if (**input == '"')
		*(*out)++ = *(*input)++;
}

/* build expanded string */
char	*rebuild_str(char *input, int len, t_shell **shell)
{
	char	*res;
	char	*out;

	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	out = res;
	while (*input)
	{
		if (*input == '\'')
			copy_single_quote(&out, &input);
		else if (*input == '"')
			copy_in_dquote(&out, &input, shell);
		else if (*input == '$')
			insert_var(&out, &input, shell);
		else
			*out++ = *input++;
	}
	*out = '\0';
	return (res);
}

/* expand $vars in input */
char	*expnd(char *input, t_shell **shell)
{
	int	len;

	len = 0;
	calc_total_len(input, &len, shell);
	return (rebuild_str(input, len, shell));
}
