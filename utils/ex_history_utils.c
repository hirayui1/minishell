#include "../minishell.h"

/**
 * @param prompt  Command prompt entered by the user
 *
 * @return  New list node with prompt placed inside.
 */
t_history	*new_history(char *prompt)
{
	t_history	*a;

	a = malloc(sizeof(t_history));
	if (!a)
		return (0);
	a->prompt = prompt;
	a->next = 0;
	return (a);
}

/**
 * @brief  Adds a command to the start of history list
 * 	
 * @param history  header for list of nodes containing prompts
 * @param prompt   Prompt itself
 *
 * @return int  1 for error, 0 for success of malloc
 */
int	add_to_history(t_history **history, char *prompt)
{
	t_history	*tmp;

	tmp = *history;
	*history = new_history(prompt);
	if (!(*history))
		return (1);
	(*history)->next = tmp;
	return (0);
}

/**
 * @brief  clean user history to prevent leaks, call at program quit
 *
 * @param history  header for list of nodes containing prompts
 *
 * @return void
 */
void	clean_history(t_history **history)
{
	t_history	*next;
	t_history	*tmp;

	next = *history;
	while (next)
	{
		free(next->prompt);
		tmp = next->next;
		free(next);
		next = tmp;
	}
	history = 0;
}
