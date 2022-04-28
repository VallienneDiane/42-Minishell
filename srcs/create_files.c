/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:06:35 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/28 13:37:19 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_create_file_in(t_cmd *cmd)
{
	cmd->fd_in = open(cmd->tab_redir_in[0], O_RDONLY);
	if (!cmd->tab_redir_in || cmd->fd_in == -1)
	{
		cmd->infile_error = 1;
		printf("miniHell: %s: No such file or directory\n", \
		cmd->tab_redir_in[0]);
		g_status = 256;
	}
	return (0);
}

int	ft_create_file_out1(t_cmd *cmd)
{
	cmd->fd_out_trunc = open(cmd->tab_redir_out1[0], \
	O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (0);
}

int	ft_create_file_out2(t_cmd *cmd)
{
	cmd->fd_out_append = open(cmd->tab_redir_out2[0], \
	O_CREAT | O_RDWR | O_APPEND, 0644);
	return (0);
}
