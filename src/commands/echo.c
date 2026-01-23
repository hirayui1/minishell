#include "../../minishell.h"

void	echo(char *input, t_shell **shell)
{
	char	*trimmed;

	input = ft_strnstr(input, " ", ECHO_OFFSET);
	if (!input || !*(++input))
		printf("\n");
	if (!ft_strncmp("-n ", input, N_OPTION_OFFSET))
	{
		trimmed = ft_strtrim(input + N_OPTION_OFFSET, " ");
		printf("%s", trimmed);
		free(trimmed);
	}
	else
		printf("%s\n", input);
	(*shell)->last_exit_status = EXIT_SUCCESS;
}
