/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarabab <bkarabab@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 10:01:16 by bkarabab          #+#    #+#             */
/*   Updated: 2026/01/24 10:01:17 by bkarabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize(t_shell **shell, char **envp)
{
	sig_manager(0);
	*shell = malloc(sizeof(t_shell));
	(*shell)->pwd = ft_strdup(getenv("PWD"));
	(*shell)->envp = load_list(envp);
	(*shell)->last_exit_status = EXIT_SUCCESS;
}

void	cleanup_shell(t_shell **shell)
{
	if (!*shell)
		return ;
	if ((*shell)->pwd)
		free((*shell)->pwd);
	lst_destroy((*shell)->envp);
	free(*shell);
	*shell = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	*shell;

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
