#include "../minishell.h"

/*
** find_envar - Find environment variable value
*/
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

/*
** skip_single_quote - Skip single quoted section, add to length
*/
static void	skip_single_quote(char **input, int *len)
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

/*
** calc_in_dquote - Calculate length inside double quotes
*/
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

/*
** calc_total_len - Calculate total length of expanded string
*/
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

/*
** copy_single_quote - Copy single quoted content with quotes
*/
static void	copy_single_quote(char **out, char **input)
{
	*(*out)++ = *(*input)++;
	while (**input && **input != '\'')
		*(*out)++ = *(*input)++;
	if (**input == '\'')
		*(*out)++ = *(*input)++;
}

/*
** copy_in_dquote - Copy double quoted content with expansion and quotes
*/
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

/*
** rebuild_str - Build expanded string with variable values
*/
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

/*
** expnd - Expand environment variables in input string
*/
char	*expnd(char *input, t_shell **shell)
{
	int	len;

	len = 0;
	calc_total_len(input, &len, shell);
	return (rebuild_str(input, len, shell));
}
