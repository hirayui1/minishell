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

void	*expand_helper(char **input, char **res, char *envar, int *len)
{
	char	*sign;

	sign = ft_strchr(*input, '$');
	while (*envar)
	{
		*res[*len] = *envar;
		envar++;
		*len++;
	}
	*input += find_word_len(sign);
}

char	*expand_one(char *input, char *sign, int len, t_shell **shell)
{
	char	*res;

	res = malloc(sizeof(char) * len + 1);
  len = 0;
  while (*input)
  {
    if (*input == '$')
    {
			expand_helper(&input, &res, envar, &len);
    }
    else
    {
      res[len] = *input;
      input++;
      len++;
    }
  }
  res[len] = 0;
  return (res);
}

char  *expnd(char *input, t_shell **shell)
{
	char	*tmp;
  char  *envar;
  char  *sign;
  int   len;

  envar = find_envar(input, shell);
	while (!envar || !*envar)
	{
		sign = ft_strchr(input, '$');
		len = find_word_len(sign);
		len = (sign - input)
			+ ft_strlen(envar)
			+ ft_strlen(sign + find_word_len(sign));
		tmp = input;
		input = expand_one(input, sign, len, shell);
		free(tmp);
		envar = find_envar(input, shell);
	}
	return (0);
 }
