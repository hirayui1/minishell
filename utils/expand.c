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

char  *expnd(char *input, t_shell **shell)
{
  char  *res;
  char  *envar;
  char  *sign;
  int   len;

  envar = find_envar(input, shell);
  if (!envar)
    return (0);
  sign = ft_strchr(input, '$');
  len = find_word_len(sign);
  len = (sign - input)
    + ft_strlen(envar)
    + ft_strlen(sign + find_word_len(sign));
  res = malloc(sizeof(char) * len + 1);
  len = 0;
  while (*input)
  {
    if (*input == '$')
    {
      while (*envar)
      {
        res[len] = *envar;
        envar++;
        len++;
      }
      input += find_word_len(sign);
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
