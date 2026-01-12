#include "../../minishell.h"

/*
 * skips first 5 chars which are "echo " and prints
 */
void	echo(char *input)
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
}
