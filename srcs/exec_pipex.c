/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 13:25:18 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/07 18:09:09 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exec_pipex(t_cmd *cmd, char **envp)
{
	pid_t	pid;

	if (pipe(cmd->pipefd) < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(cmd->pipefd[0]);
		// if (cmd->tab_str[0])
			dup2(cmd->pipefd[1], STDOUT_FILENO);
		// else
		// 	dup2(cmd->pipefd[1], cmd->pipe_heredoc_fd[0]);
		ft_execution(cmd, envp);
		close(cmd->pipefd[1]);
		// close(cmd->pipe_heredoc_fd[1]);
	}
	else
	{
		close(cmd->pipefd[1]);
		dup2(cmd->pipefd[0], STDIN_FILENO);
		close(cmd->pipefd[0]);
		waitpid(pid, NULL, 0);
	}
}
