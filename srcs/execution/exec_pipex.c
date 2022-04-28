/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 13:25:18 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/28 18:50:09 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exec_pipex(t_cmd *cmd)
{
	pid_t	pid;

	if (pipe(cmd->pipefd) < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	cmd->pipe_pids[cmd->pipe_id] = pid;
	cmd->pipe_id++;
	if (pid < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		ft_pipex_child(cmd);
	else
		ft_pipex_parent(cmd);
}

void	ft_pipex_child(t_cmd *cmd)
{
	close(cmd->pipefd[0]);
	dup2(cmd->pipefd[1], STDOUT_FILENO);
	ft_execution(cmd);
	close(cmd->pipefd[1]);
}

void	ft_pipex_parent(t_cmd *cmd)
{
	close(cmd->pipefd[1]);
	dup2(cmd->pipefd[0], STDIN_FILENO);
	close(cmd->pipefd[0]);
}
