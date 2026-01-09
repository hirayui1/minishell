#include "../minishell.h"

// in case its ever needed.
char  **lst_to_array(t_env *envp)
{
	char	**s;
	int		i;
	t_env	*tmp;

	tmp = envp;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	s	= malloc(sizeof(char *) * (i + 1));
	if (!s)
		return (0);
	i = 0;
	while (envp)
	{
		s[i] = ft_strdup(envp->val);
		envp = envp->next;
		i++;
	}
	s[i] = NULL;
	return (s);
}

t_env *find_key(char *key, t_env *envp)
{
  int len;

  len = ft_strlen(key);
  while (envp)
  {
    if (!ft_strncmp(key, envp->val, len))
      return (envp);
    envp = envp->next;
  }
  return (0);
}

t_env *load_list(char **envp)
{
	t_env	*head;
	t_env	*next;
	int		i;

	i = 0;
	next = lstnew(envp[i++]);
	if (!next)
		return (0);
	head = next;
	while (envp[i])
	{
		next->next = lstnew(envp[i++]);
		if (!next)
			return (lst_destroy(head), NULL);
		next = next->next;
	}
	return (head);
}
