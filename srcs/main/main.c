/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:45:02 by dvallien          #+#    #+#             */
/*   Updated: 2022/05/03 14:51:25 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_main(t_cmd *cmd, char **env)
{
	g_status = 0;
	ft_cpy_env(env, cmd);
	signal(SIGINT, ft_signal_handler);
	cmd->stdin_copy = dup(STDIN_FILENO);
}

void	ft_manage_line(t_list **list, char *line, t_cmd *cmd)
{
	if (!line)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit(0);
	}
	if (line && line[0])
		add_history(line);
	if (line)
		ft_parsing(list, line, cmd);
}

void	ft_init_exec(t_cmd *cmd, t_list *list)
{
	cmd->infile_error = 0;
	cmd->valid_path = NULL;
	cmd->pipe_id = 0;
	signal(SIGINT, SIG_IGN);
	if (list)
		cmd->pipe_pids = ft_calloc(sizeof(pid_t), ft_lstlast(list)->block);
	else
		cmd->pipe_pids = NULL;
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_list	*list;
	t_cmd	cmd;

	ft_init_main(&cmd, env);
	while (1)
	{
		dup2(cmd.stdin_copy, STDIN_FILENO);
		list = NULL;
		ft_term_handler(0);
		line = readline("miniHell$ ");
		ft_term_handler(1);
		ft_manage_line(&list, line, &cmd);
		cmd.line_path = ft_get_line_path(&cmd);
		cmd.tab_path = ft_split(cmd.line_path, ':');
		if (!cmd.parse_error && line[0])
			ft_start_exec(list, &cmd);
		free(line);
		ft_free_split(cmd.tab_path);
		ft_lstclear(&list);
	}
	(void)ac;
	(void)av;
}
