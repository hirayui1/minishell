/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarabab <bkarabab@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 09:53:51 by bkarabab          #+#    #+#             */
/*   Updated: 2026/01/24 09:53:51 by bkarabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/* skip whitespace */
void	skip_spaces(char **ptr)
{
	while (**ptr == ' ')
		(*ptr)++;
}

/* copy content inside quotes */
static int	copy_quoted(char *dst, char **src, char quote)
{
	int	len;

	len = 0;
	++(*src);
	while (**src && **src != quote)
	{
		dst[len++] = **src;
		++(*src);
	}
	if (**src == quote)
		++(*src);
	return (len);
}

/* get token length, skip quotes */
static int	calc_token_len(char *input)
{
	int		len;
	char	quote;

	len = 0;
	while (*input && *input != ' ' && *input != '<' && *input != '>')
	{
		if (*input == '\'' || *input == '"')
		{
			quote = *input++;
			while (*input && *input != quote)
			{
				++len;
				++input;
			}
			if (*input == quote)
				++input;
		}
		else
		{
			++len;
			++input;
		}
	}
	return (len);
}

/* get next token, advances ptr */
char	*extract_token(char **input)
{
	char	*token;
	int		len;
	int		i;

	len = calc_token_len(*input);
	token = malloc(sizeof(char) * (len + 1));
	if (!token)
		return (NULL);
	i = 0;
	while (**input && **input != ' ' && **input != '<' && **input != '>')
	{
		if (**input == '\'' || **input == '"')
			i += copy_quoted(token + i, input, **input);
		else
			token[i++] = *(*input)++;
	}
	token[i] = '\0';
	return (token);
}
