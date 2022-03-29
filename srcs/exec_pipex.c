/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 13:25:18 by dvallien          #+#    #+#             */
/*   Updated: 2022/03/29 17:14:38 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exec_pipex(t_list *list, t_cmd *cmd, char **envp)
{
	(void)list;
	
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
	if (pid == 0)
	{ 
		// protection dup2 et close if < 0 
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		ft_execute(cmd, envp);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		waitpid(pid, &cmd->fd_status, 0);
	}
}

void	ft_execute(t_cmd *cmd, char **envp)
{
	if (execve(cmd->valid_path, cmd->tab_args, envp) < 0)
	{
		free(cmd->valid_path);
		free(cmd->tab_args);
		printf("Error : failure execve\n");
	}
}
