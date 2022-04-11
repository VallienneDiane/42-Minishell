/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:24:19 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/07 12:04:41 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_cmd *cmd)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		if (cmd->last_out == 2)
			ft_putstr_fd(cwd, cmd->fd_out_append);
		else if (cmd->last_out == 1)
			ft_putstr_fd(cwd, cmd->fd_out_trunc);
		else
			ft_putstr_fd(cwd, STDOUT_FILENO);
		return (0);
	}
	return (1);
}
