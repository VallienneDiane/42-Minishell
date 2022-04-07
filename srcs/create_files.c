/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:06:35 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/07 12:48:55 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_create_file(t_cmd *cmd, int type)
{
	if (type == 0)
		return (ft_create_file_in(cmd));
	if (type == 1)
		return (ft_create_file_out1(cmd));
	if (type == 2)
		return (ft_create_file_out2(cmd));
	return (0);
}

int	ft_create_file_in(t_cmd *cmd)
{
	cmd->fd_in = open(cmd->tab_redir_in[0], O_RDONLY);
	if (!cmd->tab_redir_in || cmd->fd_in == -1)
	{
		printf("No such file or directory\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	ft_create_file_out1(t_cmd *cmd)
{
	cmd->fd_out_trunc = open(cmd->tab_redir_out1[0], \
	O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (!cmd->tab_redir_out1 || cmd->fd_out_trunc == -1)
	{
		printf("No such file or directory\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	ft_create_file_out2(t_cmd *cmd)
{
	cmd->fd_out_append = open(cmd->tab_redir_out2[0], \
	O_CREAT | O_RDWR | O_APPEND, 0644);
	if (!cmd->tab_redir_out2 || cmd->fd_out_append == -1)
	{
		printf("No such file or directory\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}
