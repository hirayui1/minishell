#include "minishell.h"

// TODO: I want to go with a struct that holds things here,
//       so change to that later

void	initialize(t_shell **shell)
{
	sig_manager();
	*shell = malloc(sizeof(t_shell));
	(*shell)->pwd = ft_strdup(getenv("PWD"));
}

int	main(void)
{
	char		*input;
	t_shell		*shell;

	initialize(&shell);
	while (1)
	{
		input = readline("minishell$>");
		input_handler(&input, &shell);
		free(input);
	}
	return (0);
}
