#include "minishell.h"

// TODO: I want to go with a struct that holds things here,
//       so change to that later

void	initialize(t_shell **shell, char **envp)
{
	sig_manager();
	*shell = malloc(sizeof(t_shell));
	(*shell)->pwd = ft_strdup(getenv("PWD"));
	(*shell)->envp = load_list(envp); // no need to free this
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_shell		*shell;

	(void)argc;
	(void)argv;
	initialize(&shell, envp);
	while (1)
	{
		input = readline("minishell$>");
		input_handler(&input, &shell);
		free(input);
	}
	return (0);
}

