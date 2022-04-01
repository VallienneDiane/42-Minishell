/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:10:43 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/01 17:47:58 by dvallien         ###   ########.fr       */
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
            if (cmd->last_out == 2)
                ft_putstr_fd(cmd->tab_str[i], cmd->fd_stdout2);
            else
                ft_putstr_fd(cmd->tab_str[i], cmd->fd_stdout);
            is_arg = 1;
        }
        i++;
    }
    if (!option)
    {
        if (cmd->last_out == 2)
            ft_putstr_fd("\n", cmd->fd_stdout2);
        else
            ft_putstr_fd("\n", cmd->fd_stdout);
    }
    return (0);
}