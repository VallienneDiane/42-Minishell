/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:00:38 by dvallien          #+#    #+#             */
/*   Updated: 2022/03/31 18:03:59 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_redir_dup(t_cmd *cmd, char **envp)
{
    int out1;
    int out2;

    if (cmd->redir_in != NULL)
    {
        printf("redir dup \n");
        // in = dup(0);
        // close(0);
        dup2(cmd->fd_stdin, 0);
    }
    if (!(out1 = 0) && cmd->redir_out1 != NULL)
    {
        out1 = dup(1);
        close(1);
        dup2(cmd->fd_stdout, 1);
    }
    if (!(out2 = 0) && cmd->redir_out2 != NULL)
    {
        out2 = dup(2);
        close(2);
        dup2(cmd->fd_stderr, 2);
    }
    ft_execute(cmd, envp);
    ft_redir_clean(cmd, cmd->fd_stdin, out1, out2);
}

void   ft_redir_clean(t_cmd *cmd, int in, int out1, int out2)
{
    if (cmd->redir_in)
        dup2(in, 0);
    if (cmd->redir_out1)
        dup2(out1, 1);
    if (cmd->redir_out2)
        dup2(out2, 2);
}