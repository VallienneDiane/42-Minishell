/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:24:51 by dvallien          #+#    #+#             */
/*   Updated: 2022/05/03 13:28:20 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_join_env_herrdoc(char *line, t_pars_info p_info, char *new_line)
{
	char	*env_name;

	p_info.j = 0;
	while (line[p_info.i])
	{
		if (line[p_info.i] == '$')
		{
			env_name = ft_env_name(line, &p_info);
			if (ft_strcmp(env_name, "?") == 0)
				new_line = ft_errno_join(new_line, &p_info);
			else
				new_line = ft_join_full_env(new_line, env_name, &p_info);
		}
		else
		{
			new_line[p_info.j] = line[p_info.i];
			p_info.i += 1;
			p_info.j += 1;
		}
	}
	free (line);
	return (new_line);
}

char	*ft_parsing_line(char *line, t_cmd *cmd)
{
	t_pars_info	p_info;
	char		*new_line;

	p_info.cmd = cmd;
	p_info.i = 0;
	p_info.j = 0;
	while (line[p_info.j])
	{
		if (line[p_info.j] == '$')
			ft_env_size(line, &p_info);
		else
			p_info.j += 1;
	}
	new_line = ft_calloc(sizeof(char), p_info.j + 1);
	new_line = ft_join_env_herrdoc(line, p_info, new_line);
	return (new_line);
}

char	*ft_heredoc_loop(char *stop, t_cmd *cmd)
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
		{
			g_status = 0;
			break ;
		}
		line = ft_parsing_line(line, cmd);
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
	str = ft_heredoc_loop(list->content, cmd);
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
		printf("> \n");
		ft_term_handler(1);
	}	
	close(cmd->pipe_heredoc_fd[1]);
	dup2(cmd->pipe_heredoc_fd[0], STDIN_FILENO);
	close(cmd->pipe_heredoc_fd[0]);
}
