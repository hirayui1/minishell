#include "../minishell.h"

/*
 * parse_redir - Parse and add a single redirection from input
 */
static void	parse_redir(char **ptr, t_cmd *cmd)
{
	if (**ptr == '<')
		parse_redir_in(ptr, cmd);
	else if (**ptr == '>')
		parse_redir_out(ptr, cmd);
}

/*
 * add_arg - Add argument to args array (manual realloc replacement)
 */
static char	**add_arg(char **args, char *arg, int count)
{
	char	**new_args;
	int		i;

	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_args[i] = args[i];
		++i;
	}
	new_args[count] = arg;
	new_args[count + 1] = NULL;
	free(args);
	return (new_args);
}

/*
 * parse_command - Parse command string into arguments and redirections
 */
void	parse_command(char *input, t_cmd *cmd, t_shell **shell)
{
	char	*ptr;
	char	**args_list;
	int		arg_count;
	char	*arg;

	(void)shell;
	cmd->args = NULL;
	cmd->redirs = NULL;
	ptr = input;
	args_list = NULL;
	arg_count = 0;
	while (*ptr)
	{
		if (*ptr == ' ')
			++ptr;
		else if (*ptr == '<' || *ptr == '>')
			parse_redir(&ptr, cmd);
		else
		{
			arg = extract_token(&ptr);
			args_list = add_arg(args_list, arg, arg_count);
			++arg_count;
		}
	}
	cmd->args = args_list;
}

/*
 * free_cmd - Free all allocated memory in command structure
 */
void	free_cmd(t_cmd *cmd)
{
	t_redir	*redir;
	t_redir	*next;

	if (cmd->args)
		free_2d(cmd->args);
	redir = cmd->redirs;
	while (redir)
	{
		next = redir->next;
		free(redir->file);
		free(redir->delimiter);
		free(redir);
		redir = next;
	}
}