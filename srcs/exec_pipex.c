/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 13:25:18 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/06 17:58:34 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exec_pipex(t_list *list, t_cmd *cmd, char **envp)
{
	(void)list;
	(void)envp;
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) < 0)
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
	if (pid == 0) // processus enfant
	{
		// protection dup2 et close if < 0 
		// Ferme sortie pipe et remplace sortie cmd 1 par l'entree du pipe
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		ft_execute(cmd, envp);
	}
	else
	{
		// Ferme entree du pipe et remplace entree cmd 2 par sortie du pipe
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO); // STDIN = 0
		close(pipefd[0]);
		waitpid(pid, &cmd->fd_status, 0);
	}
}

