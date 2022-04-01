/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:06:35 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/01 14:38:57 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int   ft_create_file(t_cmd *cmd, int type)
{
    if (type == 0) //stdin
        return (ft_create_file_in(cmd));
    if (type == 1) //stdout
        return (ft_create_file_out1(cmd));
    if (type == 2) //stderr 
        return (ft_create_file_out2(cmd));
	return (0);
}

int ft_create_file_in(t_cmd *cmd)
{
    cmd->fd_stdin = open(cmd->redir_in[0], O_RDONLY);
    if (!cmd->redir_in || cmd->fd_stdin == -1)
    {
        printf("minishell: IN %s : No such file or directory\n", cmd->redir_in[0]);
        exit(EXIT_FAILURE);
    }
    return (0);
}

int ft_create_file_out1(t_cmd *cmd)
{
    cmd->fd_stdout = open(cmd->redir_out1[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (!cmd->redir_out1 || cmd->fd_stdout == -1)
    {
        printf("minishell: OUT1 %s : No such file or directory\n", cmd->redir_out1[0]);
        exit(EXIT_FAILURE);
    }
    return (0);
}

int ft_create_file_out2(t_cmd *cmd)
{
    cmd->fd_stdout2 = open(cmd->redir_out2[0], O_CREAT | O_RDWR | O_APPEND, 0644);
    // printf("FD OUT2 %d\n", cmd->fd_stdout2);
    if (!cmd->redir_out2 || cmd->fd_stdout2 == -1)
    {
        printf("minishell: OUT2 %s : No such file or directory\n", cmd->redir_out2[0]);
        exit(EXIT_FAILURE);
    }
    return (0);
}
