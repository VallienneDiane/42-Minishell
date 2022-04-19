/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:03:59 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/19 15:03:24 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_builtin(char *str)
{
	if (str)
	{
		if (ft_strcmp("echo", str) == 0 || ft_strcmp("pwd", str) == 0
			|| ft_strcmp("env", str) == 0 || ft_strcmp("export", str) == 0
			|| ft_strcmp("cd", str) == 0 || ft_strcmp("exit", str) == 0
			|| ft_strcmp("unset", str) == 0)
			return (1);
	}
	return (0);
}

int	ft_exec_builtin(t_cmd *cmd, char **envp)
{
	if (ft_strcmp("echo", cmd->tab_str[0]) == 0)
		return (ft_echo(cmd));
	if (ft_strcmp("pwd", cmd->tab_str[0]) == 0)
		return (ft_pwd(cmd));
	if (ft_strcmp("env", cmd->tab_str[0]) == 0)
		return (ft_env(cmd));
	if (ft_strcmp("export", cmd->tab_str[0]) == 0)
		return (ft_export(cmd));
	if (ft_strcmp("unset", cmd->tab_str[0]) == 0)
		return (ft_unset(cmd));
	if (ft_strcmp("cd", cmd->tab_str[0]) == 0)
		return (ft_cd(cmd, envp));
	if (ft_strcmp("exit", cmd->tab_str[0]) == 0)
	{
		return (ft_exit(cmd));
	}
	return (1);
}
