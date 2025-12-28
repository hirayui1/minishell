#include "../minishell.h"

void	input_handler(char **input, t_shell **shell)
{
	if (!*input) // null - ctrl + D
	{
		clear_history();
		ft_exit(shell, input, 1);
	}
	else if (ft_strlen(*input) != 0)
	{
		add_history(*input);
		cmd_manager(*input, shell);
	}
}

int	cmd_manager(char *input, t_shell **shell)
{
	int	len;
  char  *tmp;

  tmp = ft_strtrim(input, " ");
  input = remove_extra_chars(tmp, ' ');
	len = ft_strlen(input);
  free(tmp);
  if (!ft_strncmp("pwd", input, len))
		return (pwd(shell), 0);
	else if (!ft_strncmp("cd ", input, 3))
		return(cd(input, shell), 0);
	else if (!ft_strncmp("env", input, 3))
		return (print_env(shell), 0);
	else if (!ft_strncmp("echo ", input, 5))
		return (echo(input), 0);
  else if (!try_exec(input, shell))
    return (0);
  else
			printf("%s: command not found.\n", input);
  free(input); // this is the input instance from parsing extra chars
	return (1);
}
