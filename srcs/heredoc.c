/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:24:51 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/01 13:08:02 by dvallien         ###   ########.fr       */
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
		line = readline("heredoc> ");
		if (!line || !ft_strncmp(line, stop, ft_strlen(line)))
			break ;
		str = ft_strjoin(str, line);
		if (str)
			str = ft_strjoin(str, "\n");
	}
	return (str);
}

int	ft_heredoc_process(char *stop)
{
    int		pipefd[2];
    pid_t	pid;
	char	*str;

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
		str = ft_heredoc_loop(stop);
		if (str)
			printf("%s", str);
        if (close(pipefd[0] < 0))
		{
            printf("close error\n");
			exit(EXIT_FAILURE);
		}
    }
	waitpid(pid, NULL, 0);
    return (0);
}
