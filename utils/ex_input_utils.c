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
		if (cmd_manager(*input, shell))
			printf("%s: command not found.\n", *input);
	}
}

int	cmd_manager(char *input, t_shell **shell)
{
	int	len;

	len = ft_strlen(input);
  input = remove_extra_chars(input, ' ');
  if (!ft_strncmp("pwd", input, len))
		return (pwd(shell), free(input), 0);
	else if (!ft_strncmp("cd ", input, 3))
		return(cd(input, shell), free(input), 0);
	else if (!ft_strncmp("env", input, 3))
		return (print_env(shell), free(input), 0);
	else if (!ft_strncmp("echo ", input, 5))
		return (echo(input), free(input), 0);
  else if (!try_exec(input, shell))
    return (free(input), 0);
  free(input); // this is the input instance from parsing extra chars
	return (1);
}
