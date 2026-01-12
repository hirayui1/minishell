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
		else
			*len += find_word_len(input);
		input += find_word_len(input);
		if (!*input)
			break;
		val = ft_strchr(input, '$');
	}

	if (*input)
		*len += ft_strlen(input);
	return (0);
}

char  *expnd(char *input, t_shell **shell)
{
	int	len;

	len = 0;
	calc_total_len(input, &len, shell);
	printf("%d\n", len);
	//#1 TODO: correctly calculate length
	//#2 TODO: create a string and start iterating over input
	//#3 TODO: check if the current char is $, if so check if envar exists
	//#4 TODO: if exists, fill in envar instead of current chars from input
	return (0);
 }
