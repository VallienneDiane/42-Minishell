/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:03:59 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/12 15:31:22 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_builtin(char *str)
{
	if (str)
	{
		if (ft_strcmp("echo", str) == 0 || ft_strcmp("pwd", str) == 0
			|| ft_strcmp("env", str) == 0 || ft_strcmp("export", str) == 0)
			return (1);
	}
	return (0);
}

int	ft_exec_builtin(t_cmd *cmd)
{
	if (ft_strcmp("echo", cmd->tab_str[0]) == 0)
		return (ft_echo(cmd));
	if (ft_strcmp("pwd", cmd->tab_str[0]) == 0)
		return (ft_pwd(cmd));
	if (ft_strcmp("env", cmd->tab_str[0]) == 0)
		return (ft_env(cmd));
	if (ft_strcmp("export", cmd->tab_str[0]) == 0)
		return (ft_export(cmd));
	return (1);
}
