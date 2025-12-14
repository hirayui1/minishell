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
		if (!try_exec(*input, shell))
		{
		}
		else
			printf("%s: command not found.\n", *input);
	}
}

int	try_exec(char *input, t_shell **shell)
{
	int	len;

	len = ft_strlen(input);
	if (!ft_strncmp("/bin/ls", input, len) 
			|| !ft_strncmp("ls", input, len)
			|| !ft_strncmp("ls ", input, 3)
			|| !ft_strncmp("/bin/ls ", input, 9))
		return (ls(input), 0);
	else if (!ft_strncmp("pwd", input, len))
		return (pwd(shell), 0);
	else if (!ft_strncmp("cd ", input, 3))
		return(cd(input, shell), 0);
	return (1);
}
