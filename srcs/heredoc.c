/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:24:51 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/06 18:02:49 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *ft_heredoc_loop(char *stop)
{
	char	*line;
    char	*str;

	str = "";
	line = NULL;
	while (1)
	{
		// rl_replace_line("", 0);
		printf("line : %s\n", line);
		line = readline("> ");
		if (ft_strlen(line) && !ft_strncmp(line, stop, ft_strlen(line)))
			break ;
		str = ft_strjoin(str, line);
		free (line);
		if (str)
			str = ft_strjoin(str, "\n");
	}
	return (str);
}

// int	ft_heredoc_process(char *stop, t_cmd *cmd, char **envp)
// {
// 	(void)cmd;
// 	(void)envp;
//     int		pipefd[2];
//     pid_t	pid;
// 	char	*str;

// 	if (pipe(pipefd) < 0)
// 	{
// 		perror("");
// 		exit(EXIT_FAILURE);
// 	}
// 	pid = fork();
//     if (pid < 0)
// 	{
// 		perror("");
// 		exit(EXIT_FAILURE);
// 	}
//     if (pid == 0)
//     {
// 		// printf("process enfant heredoc\n");
// 		str = ft_heredoc_loop(stop);
// 		write(pipefd[1], str, ft_strlen(str));
// 		close(pipefd[1]);
// 		dup2(pipefd[0], STDIN_FILENO);
// 		close(pipefd[0]);
// 		// ft_execute(cmd, envp);
//     }
// 	else
// 	{
// 		// printf("process parent heredoc\n");
// 		close(pipefd[0]);
// 		close(pipefd[1]);
// 		// dup2(pipefd[0], STDOUT_FILENO);
// 	}
// 		waitpid(pid, NULL, 0);
//     return (0);
// }
