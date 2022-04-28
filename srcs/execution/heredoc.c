/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:24:51 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/28 17:39:55 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_heredoc_loop(char *stop)
{
	char	*line;
	char	*str;

	str = "";
	line = NULL;
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strlen(line) && !ft_strncmp(line, stop, ft_strlen(line)))
			break ;
		str = ft_strjoin(str, line);
		free (line);
		if (str)
			str = ft_strjoin(str, "\n");
	}
	ft_term_handler(1);
	return (str);
}

void	ft_heredoc_child(t_cmd *cmd, t_list *list)
{
	char	*str;

	dup2(cmd->stdin_copy, STDIN_FILENO);
	str = ft_heredoc_loop(list->content);
	write(cmd->pipe_heredoc_fd[1], str, ft_strlen(str));
	close(cmd->pipe_heredoc_fd[1]);
	dup2(cmd->pipe_heredoc_fd[0], STDIN_FILENO);
	close(cmd->pipe_heredoc_fd[0]);
	signal(SIGINT, ft_signal_exec_handler);
	ft_term_handler(1);
	exit(EXIT_SUCCESS);
}

void	ft_heredoc_parent(t_cmd *cmd, pid_t pid)
{
	waitpid(pid, &g_status, 0);
	if (WIFSIGNALED(g_status) == 1 && WTERMSIG(g_status) == SIGINT)
	{
		printf(">\n");
		ft_term_handler(1);
	}	
	close(cmd->pipe_heredoc_fd[1]);
	dup2(cmd->pipe_heredoc_fd[0], STDIN_FILENO);
	close(cmd->pipe_heredoc_fd[0]);
}
