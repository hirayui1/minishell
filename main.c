#include "minishell.h"

void	initialize(t_shell **shell, char **envp)
{
	sig_manager(0);
	*shell = malloc(sizeof(t_shell));
	(*shell)->pwd = ft_strdup(getenv("PWD"));
	(*shell)->envp = load_list(envp); // need to free the list on exit
}

int	main(int argc, char **argv, char **envp)
{
	char			*input;
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
