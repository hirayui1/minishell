#include "../minishell.h"

/*
** handle_exit_status - Process $? expansion and update length
*/
int	handle_exit_status(int *len, t_shell **shell)
{
	char	*tmp_exit;

	tmp_exit = ft_itoa((*shell)->last_exit_status);
	if (tmp_exit)
	{
		*len += ft_strlen(tmp_exit);
		free(tmp_exit);
		return (1);
	}
	*len += 1;
	return (0);
}

/*
** calc_var_len - Calculate length contribution from a variable
*/
void	calc_var_len(char **input, int *len, t_shell **shell)
{
	char	*tmp;
	int		word_len;

	tmp = find_envar(*input, shell);
	word_len = find_word_len(*input + 1);
	if (tmp)
		*len += ft_strlen(tmp);
	else if (word_len == 0)
	{
		if ((*input)[1] == '?')
			handle_exit_status(len, shell);
		else
			*len += 1;
	}
	*input += word_len + 1;
}

/*
** insert_var - Insert variable value into output string
*/
void	insert_var(char **out, char **input, t_shell **shell)
{
	char	*val;
	int		len;

	if ((*input)[1] == '?')
	{
		val = ft_itoa((*shell)->last_exit_status);
		len = 1;
	}
	else
	{
		val = find_envar(*input, shell);
		len = find_word_len(*input + 1);
	}
	if (val)
	{
		ft_memcpy(*out, val, ft_strlen(val));
		*out += ft_strlen(val);
	}
	else if (len == 0)
	{
		**out = **input;
		(*out)++;
	}
	*input += len + 1;
}
