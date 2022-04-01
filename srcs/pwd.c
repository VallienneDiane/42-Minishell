/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:24:19 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/01 17:49:28 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_pwd(t_cmd *cmd)
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)))
    {
        if (cmd->last_out == 2)
            ft_putstr_fd(cwd, cmd->fd_stdout2);
        else
            ft_putstr_fd(cwd, cmd->fd_stdout);
        return (0);
    }
    return (1);
}