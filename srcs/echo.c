/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:10:43 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/05 13:28:54 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_option(char *arg)
{
    int i;

    i = 1;
    while (arg[i])
    {
        if (arg[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

void    ft_redir_putstr(t_cmd *cmd, char *str)
{
    if (cmd->last_out == 2)
        ft_putstr_fd(str, cmd->fd_out_append);
    else if (cmd->last_out == 1)
        ft_putstr_fd(str, cmd->fd_out_trunc);
    else
        ft_putstr_fd(str, STDOUT_FILENO);
}

int ft_echo(t_cmd *cmd)
{
    int i;
    int is_arg;
    int option;

    i = 1;
    is_arg = 0;
    option = 0;
    while (cmd->tab_str[i])
    {
        if (is_arg)
            printf(" ");
        if (cmd->tab_str[i][0] == '-' && is_arg == 0)
        {
            if (ft_option(cmd->tab_str[i]))
                option = 1;
            else
                is_arg = 1;
        }
        if (is_arg || cmd->tab_str[i][0] != '-')
        {
            ft_redir_putstr(cmd, cmd->tab_str[i]);
            is_arg = 1;
        }
        i++;
    }
    if (!option)
    {
        ft_redir_putstr(cmd, "\n");
    }
    return (0);
}
