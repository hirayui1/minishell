#include "../../minishell.h"

static void	ls1(char *input, int size, int len);

/**
 * @brief  due to norminette, the size of the array needs to become
 * 	   apparent before anything is done here, once the args size
 * 	   is found, the process is delegated to ls1
 */
void	ls(char *input)
{
	int	len;

	len = ft_strlen(input);
	if (!ft_strncmp("ls", input, len)
			|| !ft_strncmp("/bin/ls", input, len))
		ls1(input, 2, len);
	else if (!ft_strncmp("ls ", input, 3)
			|| !ft_strncmp("/bin/ls ", input, 9))
		ls1(input, 3, len);
}

/**
 * @param size  2 = ls pwd, 3 = ls {given_directory}
 * @param len   length of input
 *
 * @brief  initialize a 2D array from the elements of the given input,
 * 	   fork a child process to run ls with the arguments given.
 */
static void	ls1(char *input, int size, int len)
{
	char	*args[size];
	int	status;

	args[0] = "/bin/ls";
	if (size == 3)
	{
		args[1] = ft_strnstr(input, " ", len) + 1;
		if (!ft_strncmp(" ", args[1], ft_strlen(args[1])))
			args[1] = NULL;
	}
	args[size-1] = NULL;
	if (!fork())
		execve(args[0], args, NULL);
	else
		wait(&status);
}
