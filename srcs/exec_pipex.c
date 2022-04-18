/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 13:25:18 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/18 13:55:27 by dvallien         ###   ########.fr       */
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
		dup2(cmd->pipefd[1], STDOUT_FILENO);
		ft_execution(cmd, envp);
		close(cmd->pipefd[1]);
	}
	else
	{
		close(cmd->pipefd[1]);
		dup2(cmd->pipefd[0], STDIN_FILENO);
		close(cmd->pipefd[0]);
		waitpid(pid, &errno, 0);
	}
}
