#include "../minishell.h"

/* add redir node to cmd */
void	add_redir(t_cmd *cmd, t_redir_type type, char *file, char *delim)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->type = type;
	if (file)
		new_redir->file = ft_strdup(file);
	else
		new_redir->file = NULL;
	if (delim)
		new_redir->delimiter = ft_strdup(delim);
	else
		new_redir->delimiter = NULL;
	new_redir->next = cmd->redirs;
	cmd->redirs = new_redir;
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

/* skip whitespace */
void	skip_spaces(char **ptr)
{
	while (**ptr == ' ')
		(*ptr)++;
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
