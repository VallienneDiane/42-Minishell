/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 13:25:18 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/21 17:43:54 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exec_pipex(t_cmd *cmd)
{
	pid_t	pid;

	if (pipe(cmd->pipefd) < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	// ft_term_handler(1);
	// signal(SIGINT, ft_signal_exec);
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
		ft_execution(cmd);
		close(cmd->pipefd[1]);
	}
	else
	{
		close(cmd->pipefd[1]);
		dup2(cmd->pipefd[0], STDIN_FILENO);
		close(cmd->pipefd[0]);
		waitpid(pid, &errno, 0);
		// signal(SIGINT, ft_signal);
		// ft_term_handler(0);
	}
}
