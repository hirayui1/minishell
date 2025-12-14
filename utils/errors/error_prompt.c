#include "../../minishell.h"

void	write_error(void)
{
	write(2, "Error\n", 6);
}
