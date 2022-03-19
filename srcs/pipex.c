/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 13:25:18 by dvallien          #+#    #+#             */
/*   Updated: 2022/03/19 19:01:00 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pipex(t_list *list, t_cmd *cmd, char **envp)
{
	(void)list;
	(void)cmd;
	(void)envp;
	
	int		pipefd[2];
	// pid_t	pid;

	dup2(pipefd[1], STDOUT_FILENO);
	list = list->next;
	ft_access_path(list, cmd, envp);
	// ft_parse_type(list, cmd, envp);
	// ft_parse_type(list, cmd, envp);
	
	// while (cmd->tab_args[i])
	// {
	// 	if (pipe(pipefd) < 0)
	// 		printf("Error pipe\n");
	// 	pid = fork();
	// 	if (pid < 0)
	// 		printf("Error fork\n");
	// 	if (pid == 0)
	// 	{ 
	// 		close(pipefd[0]);
	// 		dup2(pipefd[1], STDOUT_FILENO);
	// 		ft_execute(cmd, envp);
	// 	}
	// 	else
	// 	{
	// 		close(pipefd[1]);
	// 		dup2(pipefd[0], STDIN_FILENO);
	// 		waitpid(pid, &cmd->fd_status, 0);
	// 	}
	// }
	// if (dup2(cmd->fd2, 1) < 0)
	// 	printf("error dup2\n");

	// printf("previous %s\n", list->previous->content);

// cmd->fd2 = open(list->next->next->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
// printf("fd2 open %s\n", list->next->next->content);
}
	