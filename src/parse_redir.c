/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarabab <bkarabab@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:41:03 by bkarabab          #+#    #+#             */
/*   Updated: 2026/01/23 16:41:04 by bkarabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_redir(t_redir *redir, t_redir_type type, char *file, char *d)
{
	redir->type = type;
	redir->file = NULL;
	redir->delimiter = NULL;
	redir->next = NULL;
	if (file)
		redir->file = ft_strdup(file);
	if (d)
		redir->delimiter = ft_strdup(d);
}

/* add redir node to cmd (append to end for correct order) */
void	add_redir(t_cmd *cmd, t_redir_type type, char *file, char *delim)
{
	t_redir	*new_redir;
	t_redir	*temp;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	init_redir(new_redir, type, file, delim);
	if (!cmd->redirs)
	{
		cmd->redirs = new_redir;
		return ;
	}
	temp = cmd->redirs;
	while (temp->next)
		temp = temp->next;
	temp->next = new_redir;
}

/* handle < or << */
void	parse_redir_in(char **ptr, t_cmd *cmd)
{
	char	*token;

	(*ptr)++;
	if (**ptr == '<')
	{
		(*ptr)++;
		skip_spaces(ptr);
		token = extract_token(ptr);
		add_redir(cmd, REDIR_HEREDOC, NULL, token);
		free(token);
	}
	else
	{
		skip_spaces(ptr);
		token = extract_token(ptr);
		add_redir(cmd, REDIR_IN, token, NULL);
		free(token);
	}
}

/* handle > or >> */
void	parse_redir_out(char **ptr, t_cmd *cmd)
{
	char	*token;

	(*ptr)++;
	if (**ptr == '>')
	{
		(*ptr)++;
		skip_spaces(ptr);
		token = extract_token(ptr);
		add_redir(cmd, REDIR_APPEND, token, NULL);
		free(token);
	}
	else
	{
		skip_spaces(ptr);
		token = extract_token(ptr);
		add_redir(cmd, REDIR_OUT, token, NULL);
		free(token);
	}
}
