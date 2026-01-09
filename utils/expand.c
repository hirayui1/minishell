#include "../minishell.h"

char  *find_envar(char *input, t_shell **shell)
{
  t_env *envp;
  int   len;

  input = ft_strchr(input, '$');
  if (!input)
    return (0);
  input++;
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

int	len_of_envar(char *s, t_shell **shell)
{
	t_env	*envp;

	envp = find_key(s + 1, (*shell)->envp);
	if (!envp)
		return (0);
	return (ft_strlen(ft_strchr(envp->val, '=') + 1));
}

void	calc_total_len(char *input, int *len, t_shell **shell)
{
	char	**split;
	int		i;
	int		checker;

	split = ft_split(input, '$');
	i = 0;
	while (split[i])
	{
		checker = len_of_envar(split[i], shell);
		if (checker)
			*len += checker;
		else
			*len += ft_strlen(split[i]);
		i++;
	}
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
