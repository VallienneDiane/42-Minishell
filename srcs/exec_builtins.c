/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:03:59 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/07 13:04:30 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_builtin(char *str)
{
	if (str)
	{
		if (ft_strncmp("echo", str, 4) == 0 || ft_strncmp("pwd", str, 3) == 0)
			return (1);
	}
	return (0);
}

int	ft_exec_builtin(t_cmd *cmd)
{
	if (ft_strncmp("echo", cmd->tab_str[0], 4) == 0)
		return (ft_echo(cmd));
	if (ft_strncmp("pwd", cmd->tab_str[0], 3) == 0)
		return (ft_pwd(cmd));
	return (1);
}
