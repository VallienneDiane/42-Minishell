/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_redir_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:00:38 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/04 10:40:03 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_redir_dup(t_cmd *cmd, char **envp)
{
    int in;
    int out1;
    int out2;
    int heredoc;

    in = 0;
    out1 = 0;
    out2 = 0;
    heredoc = 0;
    if (cmd->tab_redir_in[0] != NULL)
    {
        in = dup(0);
        close(0);
        dup2(cmd->fd_in, 0);
    }
    if (cmd->tab_heredoc[0] != NULL)
    {
        heredoc = dup(0);
        close(0);
        dup2(cmd->fd_heredoc, 0);
    }
    if (cmd->tab_redir_out1[0] != NULL && cmd->last_out == 1)
    {
        out1 = dup(1);
        close(1);
        dup2(cmd->fd_out_trunc, 1);
    }
    if (cmd->tab_redir_out2[0] != NULL && cmd->last_out == 2)
    {
        out2 = dup(1);
        close(1);
        dup2(cmd->fd_out_append, 1);
    }
    ft_execute(cmd, envp);
    ft_redir_clean(cmd, in, out1, out2, heredoc);
}

void   ft_redir_clean(t_cmd *cmd, int in, int out1, int out2, int heredoc)
{
    if (cmd->tab_redir_in)
        dup2(in, 0);
    if (cmd->tab_heredoc)
        dup2(heredoc, 0);
    if (cmd->tab_redir_out1)
        dup2(out1, 1);
    if (cmd->tab_redir_out2)
        dup2(out2, 1);
}