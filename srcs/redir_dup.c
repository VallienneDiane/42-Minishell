/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:00:38 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/01 14:45:52 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_redir_dup(t_cmd *cmd, char **envp)
{
    int in;
    int out1;
    int out2;

    in = 0;
    out1 = 0;
    out2 = 0;
    if (cmd->redir_in[0] != NULL)
    {
        in = dup(0);
        close(0);
        dup2(cmd->fd_stdin, 0);
    }
    if (cmd->redir_out1[0] != NULL && cmd->last_out == 1)
    {
        out1 = dup(1);
        close(1);
        dup2(cmd->fd_stdout, 1);
    }
    if (cmd->redir_out2[0] != NULL && cmd->last_out == 2)
    {
        out2 = dup(1);
        close(1);
        dup2(cmd->fd_stdout2, 1);
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