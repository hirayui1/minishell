#include "../minishell.h"

char  *find_envar(char *input, t_shell **shell)
{
  t_env *envp;
  int   len;

	input++;
  if (!input)
    return (0);
  len = find_word_len(input);
  input = substr(input, len);
  if (!input)
    return (0);
  envp = find_key(input, (*shell)->envp);
  free(input);
  if (envp)
    return (ft_strchr(envp->val, '=') + 1);
  return (0);
}

int	calc_total_len(char *input, int *len, t_shell **shell)
{
	char	*val;
	char	*tmp;

	val = ft_strchr(input, '$');
	if (!val)
		return (1);
	while (val)
	{
		*len += val - input;
		input += val - input;
		tmp = find_envar(val, shell);
		if (tmp)
			*len += ft_strlen(tmp);
		else if (find_word_len(input + 1) == 0)
			*len += 1;
		else
			*len += find_word_len(input + 1) + 1;
		input += find_word_len(input + 1) + 1;
		if (!*input)
			break;
		val = ft_strchr(input, '$');
	}
	if (*input)
		*len += ft_strlen(input);
	return (0);
}

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
		*out += 1;
	}
	*input += len + 1;
}
// char **c = "asd"
// **c += 1;
char	*rebuild_str(char *input, int len, t_shell **shell)
{
	char	*res;
	char	*out;

	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	out = res;
	while (*input)
	{
		if (*input == '$')
			insert_var(&out, &input, shell);
		else
		{
			*out = *input;
			out++;
			input++;
		}
	}
	*out = 0;
	return (res);
}

char  *expnd(char *input, t_shell **shell)
{
	int	len;

	len = 0;
	if (!calc_total_len(input, &len, shell))
		return (rebuild_str(input, len, shell));
	return (0);
 }
