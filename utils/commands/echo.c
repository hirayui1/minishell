#include "../../minishell.h"

void	echo(char *input)
{
	input = ft_strnstr(input, " ", 5) + 1;
	printf("%s\n", input);
}
