#include "../minishell.h"

static t_pipeline	*build_pipeline(char **segs, int count, t_shell **shell)
{
	t_pipeline	*pl;
	int			i;

	pl = malloc(sizeof(t_pipeline));
	if (!pl)
		return (NULL);
	pl->cmds = malloc(sizeof(t_cmd) * count);
	if (!pl->cmds)
		return (free(pl), NULL);
	pl->cmd_count = count;
	i = -1;
	while (++i < count)
	{
		parse_command(segs[i], &pl->cmds[i], shell);
		pl->cmds[i].heredoc_fd = -1;
		collect_heredocs(pl->cmds[i].redirs, &pl->cmds[i].heredoc_fd);
		if (i < count - 1)
			pl->cmds[i].next = &pl->cmds[i + 1];
		else
			pl->cmds[i].next = NULL;
	}
	return (pl);
}

int	run_pipeline(char *input, int pipe_count, t_shell **shell)
{
	char		**segments;
	t_pipeline	*pl;

	segments = split_by_pipe(input, pipe_count);
	if (!segments)
		return (1);
	pl = build_pipeline(segments, pipe_count + 1, shell);
	free_2d(segments);
	if (!pl)
		return (1);
	execute_pipeline(pl, shell);
	free_pipeline(pl);
	return (0);
}
