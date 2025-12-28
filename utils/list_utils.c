#include "../minishell.h"

char  **lst_to_array(t_env *envp)
{
  
}

t_env *load_list(char **envp)
{
  t_env *head;
  t_env *next;
  int i;

  head = malloc(sizeof(t_env));
  next = head;
  i = 0;
  while (envp[i])
  {
    next->val = envp[i++];
    if (envp[i])
    {
      next->next = malloc(sizeof(t_env));
      next= next->next;
    }
  }
  return (head);
}

