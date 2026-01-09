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

char	*normalizer(char *input, t_shell **shell)
{
	char	*tmp;

	tmp = expnd(input, shell);
	if (tmp)
	{
		input = ft_strtrim(tmp, " ");
		return(free(tmp), remove_extra_chars(input, ' '));
	}
	else
	{
		tmp = ft_strtrim(input, " ");
		input = remove_extra_chars(input, ' ');
		return (free(tmp), input);
	}
	
}

int	cmd_manager(char *input, t_shell **shell)
{
	int	len;

	input = normalizer(input, shell);
	len = ft_strlen(input);
  if (!ft_strncmp("pwd", input, len))
		return (pwd(shell), free(input), 0);
	else if (!ft_strncmp("cd", input, len) || !ft_strncmp("cd ", input, 3))
		return(cd(input, shell), free(input), 0);
	else if (!ft_strncmp("env", input, 3))
		return (print_env(shell), free(input), 0);
	else if (!ft_strncmp("unset", input, 5))
		return (unset(input, shell), free(input), 0);
	else if (!ft_strncmp("export", input, 6))
		return (exprt(input, shell), free(input), 0);
	else if (!ft_strncmp("echo", input, len) || !ft_strncmp("echo ", input, 5))
		return (echo(input), free(input), 0);
  else if (!try_exec(input, shell)) //TODO: if try_exec can't find it, it
																		//should only return 1 if it cannot find
																		//input anywhere
    return (free(input), 0);
  else
			printf("%s: command not found.\n", input);
  free(input); // this is the input instance from parsing extra chars
	return (1);
}
