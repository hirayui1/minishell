#include "../../minishell.h"

/*
 * skips first 5 chars which are "echo " and prints
 */
void	echo(char *input, t_shell **shell)
{
	input = ft_strnstr(input, " ", ECHO_LEN);
	if (!input || !(++input))
		return (printf("\n"), (void)0);
	if (!ft_strncmp("-n ", input, N_OPTION_LEN))
	{
		input = ft_strtrim(input + N_OPTION_LEN, " ");
		printf("%s", input);
	}
	else
		printf("%s\n", input);
	(*shell)->last_exit_status = 0;
}
