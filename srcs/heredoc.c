/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:24:51 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/19 13:35:24 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_heredoc_loop(char *stop)
{
	char	*line;
	char	*str;

	str = "";
	line = NULL;
	while (1)
	{
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
